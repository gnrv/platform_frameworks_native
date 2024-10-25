/**************************************************************************
 *
 * Copyright 2011-2014 Jose Fonseca
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/


#include <assert.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "image.hpp"
#include "state_writer.hpp"
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include "glsize.hpp"
#include "glstate.hpp"
#include "glstate_internal.hpp"


#ifdef __linux__
#include <dlfcn.h>
#endif

#ifdef __APPLE__

#include <Carbon/Carbon.h>

#ifdef __cplusplus
extern "C" {
#endif

OSStatus CGSGetSurfaceBounds(CGSConnectionID, CGWindowID, CGSSurfaceID, CGRect *);

#ifdef __cplusplus
}
#endif

#endif /* __APPLE__ */


namespace retrace {
    extern bool resolveMSAA;
}

namespace glstate {


struct ImageDesc
{
    GLint width;
    GLint height;
    GLint depth;
    GLint samples;
    GLint internalFormat;

    inline
    ImageDesc() :
        width(0),
        height(0),
        depth(0),
        samples(0),
        internalFormat(GL_NONE)
    {}

    inline bool
    operator == (const ImageDesc &other) const {
        return width == other.width &&
               height == other.height &&
               depth == other.depth &&
               samples == other.samples &&
               internalFormat == other.internalFormat;
    }

    inline bool
    valid(void) const {
        return width > 0 && height > 0 && depth > 0;
    }
};


static GLenum
getTextureTarget(Context &context, GLuint texture);


/**
 * OpenGL ES does not support glGetTexLevelParameteriv, but it is possible to
 * probe whether a texture has a given size by crafting a dummy glTexSubImage()
 * call.
 */
static bool
probeTextureLevelSizeOES(GLenum target, GLint level, const GLint size[3],
                         GLenum internalFormat, GLenum type)
{
    flushErrors();

    GLint dummy = 0;

    switch (target) {
    case GL_TEXTURE_2D:
    case GL_TEXTURE_CUBE_MAP:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        glTexSubImage2D(target, level, size[0], size[1], 0, 0, internalFormat, type, &dummy);
        break;
    case GL_TEXTURE_3D_OES:
        glTexSubImage3DOES(target, level, size[0], size[1], size[2], 0, 0, 0, internalFormat, type, &dummy);
        break;
    default:
        assert(0);
        return false;
    }

    GLenum error = glGetError();

    if (error == GL_NO_ERROR) {
        return true;
    }

    flushErrors();

    return false;
}


static bool
probeTextureFormatOES(GLenum target, GLint level,
                      GLenum *internalFormat, GLenum *type)
{
    static const struct {
        GLenum internalFormat;
        GLenum type;
    } info[] = {
        /* internalFormat */        /* type */
        { GL_RGBA,                  GL_UNSIGNED_BYTE },
        { GL_DEPTH_STENCIL,         GL_FLOAT_32_UNSIGNED_INT_24_8_REV },
        { GL_DEPTH_STENCIL,         GL_UNSIGNED_INT_24_8 },
        { GL_DEPTH_COMPONENT,       GL_FLOAT },
        { GL_DEPTH_COMPONENT,       GL_UNSIGNED_SHORT },
        /* others? */
        { 0, 0 },
    };
    static const GLint size[3] = {1, 1, 1};

    for (int i = 0; info[i].internalFormat; i++) {
        if (probeTextureLevelSizeOES(target, level, size,
                                     info[i].internalFormat,
                                     info[i].type)) {
            *internalFormat = info[i].internalFormat;
            *type = info[i].type;
            return true;
        }
    }

    return false;
}


/**
 * Bisect the texture size along an axis.
 *
 * It is assumed that the texture exists.
 */
static GLint
bisectTextureLevelSizeOES(GLenum target, GLint level, GLint axis, GLint max,
                          GLenum internalFormat, GLenum type)
{
    GLint size[3] = {0, 0, 0};

    assert(axis < 3);
    assert(max >= 0);

    GLint min = 0;
    while (true) {
        GLint test = (min + max) / 2;
        if (test == min) {
            return min;
        }

        size[axis] = test;

        if (probeTextureLevelSizeOES(target, level, size, internalFormat, type)) {
            min = test;
        } else {
            max = test;
        }
    }
}


/**
 * Special path to obtain texture size on OpenGL ES, that does not rely on
 * glGetTexLevelParameteriv
 */
static bool
getActiveTextureLevelDescOES(Context &context, GLenum target, GLint level, ImageDesc &desc)
{
    (void)context;
    GLenum internalFormat, type;

    if (!probeTextureFormatOES(target, level, &internalFormat, &type)) {
        return false;
    }

    desc.internalFormat = internalFormat;

    GLint maxSize = 0;
    switch (target) {
    case GL_TEXTURE_2D:
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize);
        desc.width = bisectTextureLevelSizeOES(target, level, 0, maxSize, internalFormat, type);
        desc.height = bisectTextureLevelSizeOES(target, level, 1, maxSize, internalFormat, type);
        desc.depth = 1;
        break;
    case GL_TEXTURE_CUBE_MAP:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        glGetIntegerv(GL_MAX_CUBE_MAP_TEXTURE_SIZE, &maxSize);
        desc.width = bisectTextureLevelSizeOES(target, level, 0, maxSize, internalFormat, type);
        desc.height = desc.width;
        desc.depth = 1;
        break;
    case GL_TEXTURE_3D_OES:
        glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE_OES, &maxSize);
        desc.width = bisectTextureLevelSizeOES(target, level, 0, maxSize, internalFormat, type);
        desc.width = bisectTextureLevelSizeOES(target, level, 1, maxSize, internalFormat, type);
        desc.depth = bisectTextureLevelSizeOES(target, level, 2, maxSize, internalFormat, type);
        break;
    default:
        return false;
    }

    return desc.valid();
}


static inline bool
getActiveTextureLevelDesc(Context &context, GLenum target, GLint level, ImageDesc &desc)
{
    assert(target != GL_TEXTURE_CUBE_MAP);

    return getActiveTextureLevelDescOES(context, target, level, desc);
}


const GLenum
textureTargets[] = {
    GL_TEXTURE_2D,
    GL_TEXTURE_CUBE_MAP,
    GL_TEXTURE_3D,
    GL_TEXTURE_2D_ARRAY
};

const unsigned
numTextureTargets = ARRAYSIZE(textureTargets);


GLenum
getTextureBinding(GLenum target)
{
    switch (target) {
    case GL_TEXTURE_2D:
        return GL_TEXTURE_BINDING_2D;
    case GL_TEXTURE_2D_ARRAY:
        return GL_TEXTURE_BINDING_2D_ARRAY;
    case GL_TEXTURE_CUBE_MAP:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        return GL_TEXTURE_BINDING_CUBE_MAP;
    case GL_TEXTURE_3D:
        return GL_TEXTURE_BINDING_3D;
    default:
        assert(false);
        return GL_NONE;
    }
}


/**
 * OpenGL ES does not support glGetTexImage. Obtain the pixels by attaching the
 * texture to a framebuffer.
 */
static inline void
getTexImageOES(GLenum target, GLint level, GLenum format, GLenum type,
               ImageDesc &desc, GLubyte *pixels)
{
    memset(pixels, 0x80, desc.height * desc.width * 4);

    GLenum texture_binding = getTextureBinding(target);
    if (texture_binding == GL_NONE) {
        return;
    }

    GLint texture = 0;
    glGetIntegerv(texture_binding, &texture);
    if (!texture) {
        return;
    }

    GLint prev_fbo = 0;
    GLuint fbo = 0;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_fbo);
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLenum status;

    switch (target) {
    case GL_TEXTURE_2D:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
    case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
    case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, level);
        status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << __FUNCTION__ << ": " << enumToString(status) << "\n";
        }
        glReadPixels(0, 0, desc.width, desc.height, format, type, pixels);
        break;
    case GL_TEXTURE_3D_OES:
        for (int i = 0; i < desc.depth; i++) {
            glFramebufferTexture3DOES(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texture, level, i);
            glReadPixels(0, 0, desc.width, desc.height, format, type, pixels + 4 * i * desc.width * desc.height);
        }
        break;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, prev_fbo);

    glDeleteFramebuffers(1, &fbo);
}


static inline void
dumpActiveTextureLevel(StateWriter &writer, Context &context,
                       GLenum target, GLint level,
                       const std::string & label,
                       const char *userLabel)
{
    ImageDesc desc;
    if (!getActiveTextureLevelDesc(context, target, level, desc)) {
        return;
    }

    const InternalFormatDesc &formatDesc = getInternalFormatDesc(desc.internalFormat);

    GLenum format;
    GLenum type;
    chooseReadBackFormat(formatDesc, format, type);

    writer.beginMember(label);

    if (format == GL_DEPTH_COMPONENT) {
        format = GL_RED;
    }

    GLuint channels;
    image::ChannelType channelType;
    getImageFormat(format, type, channels, channelType);

    image::Image *image;
    PixelPackState pps(context);

    // Create a simple image single sample size.
    image = new image::Image(desc.width, desc.height * desc.depth, channels, true, channelType);

    getTexImageOES(target, level, format, type, desc, image->pixels);

    if (userLabel) {
        image->label = userLabel;
    }

    StateWriter::ImageDesc imageDesc;
    imageDesc.depth = desc.depth;
    imageDesc.format = formatToString(desc.internalFormat);
    writer.writeImage(image, imageDesc);

    delete image;

    writer.endMember(); // label
}


static inline void
dumpActiveTexture(StateWriter &writer, Context &context, GLenum target, GLuint texture)
{
    (void)texture;
    GLint active_texture = GL_TEXTURE0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);
    assert(active_texture >= GL_TEXTURE0);

    GLenum start_subtarget;
    GLenum stop_subtarget;
    if (target == GL_TEXTURE_CUBE_MAP) {
        start_subtarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
        stop_subtarget = start_subtarget + 6;
    } else {
        start_subtarget = target;
        stop_subtarget = start_subtarget + 1;
    }

    GLboolean allowMipmaps = target != GL_TEXTURE_2D_MULTISAMPLE &&
                             target != GL_TEXTURE_2D_MULTISAMPLE_ARRAY;

    GLint level = 0;
    do {
        ImageDesc desc;

        for (GLenum subtarget = start_subtarget; subtarget < stop_subtarget; ++subtarget) {
            std::stringstream label;
            label << "GL_TEXTURE" << (active_texture - GL_TEXTURE0) << ", "
                  << enumToString(subtarget);
            if (allowMipmaps) {
                label << ", level = " << level;
            }

            if (!getActiveTextureLevelDesc(context, subtarget, level, desc)) {
                goto finished;
            }
            dumpActiveTextureLevel(writer, context, subtarget, level, label.str(), "");
        }

        if (!allowMipmaps) {
            // no mipmaps
            break;
        }

        ++level;
    } while(true);

finished:
    return;
}

void
dumpTextures(StateWriter &writer, Context &context)
{
    writer.beginMember("textures");
    writer.beginObject();

    GLint max_texture_coords = 0;

    GLint max_combined_texture_image_units = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_texture_image_units);

    /*
     * At least the Android software GL implementation doesn't return the
     * proper value for this, but rather returns 0. The GL(ES) specification
     * mandates a minimum value of 2, so use this as a fall-back value.
     */
    max_combined_texture_image_units = std::max(max_combined_texture_image_units, 2);

    GLint max_units = std::max(max_combined_texture_image_units, max_texture_coords);

    GLint active_texture = GL_TEXTURE0;
    glGetIntegerv(GL_ACTIVE_TEXTURE, &active_texture);

    for (GLint unit = 0; unit < max_units; ++unit) {
        GLenum texture = GL_TEXTURE0 + unit;
        glActiveTexture(texture);

        for (auto target : textureTargets) {

            // Whether this fixed-function stage is enabled
            GLboolean enabled = GL_FALSE;
            if (unit < max_texture_coords &&
                (target == GL_TEXTURE_2D ||
                 target == GL_TEXTURE_3D ||
                 target == GL_TEXTURE_CUBE_MAP)) {
                glGetBooleanv(target, &enabled);
            }

            // Whether a texture object is bound
            GLint texture = 0;
            if (unit < max_combined_texture_image_units) {
                GLenum binding = getTextureBinding(target);
                glGetIntegerv(binding, &texture);
            }

            if (enabled || texture) {
                dumpActiveTexture(writer, context, target, texture);
            }
        }
    }

    glActiveTexture(active_texture);

    writer.endObject();
    writer.endMember(); // textures
}


bool
getDrawableBounds(GLint *width, GLint *height) {
#if defined(__linux__)
    if (true) {
        EGLContext currentContext = eglGetCurrentContext();
        if (currentContext != EGL_NO_CONTEXT) {
            EGLSurface currentSurface = eglGetCurrentSurface(EGL_DRAW);
            if (currentSurface == EGL_NO_SURFACE) {
                return false;
            }

            EGLDisplay currentDisplay = eglGetCurrentDisplay();
            if (currentDisplay == EGL_NO_DISPLAY) {
                return false;
            }

            if (!eglQuerySurface(currentDisplay, currentSurface, EGL_WIDTH, width) ||
                !eglQuerySurface(currentDisplay, currentSurface, EGL_HEIGHT, height)) {
                return false;
            }

            return true;
        }
    }
#endif

#if defined(_WIN32)

    HDC hDC = wglGetCurrentDC();
    if (!hDC) {
        return false;
    }

    HWND hWnd = WindowFromDC(hDC);
    RECT rect;

    if (!GetClientRect(hWnd, &rect)) {
       return false;
    }

    *width  = rect.right  - rect.left;
    *height = rect.bottom - rect.top;
    return true;

#elif defined(__APPLE__)

    CGLContextObj ctx = CGLGetCurrentContext();
    if (ctx == NULL) {
        return false;
    }

    CGSConnectionID cid;
    CGSWindowID wid;
    CGSSurfaceID sid;

    if (CGLGetSurface(ctx, &cid, &wid, &sid) != kCGLNoError) {
        return false;
    }

    CGRect rect;

    if (CGSGetSurfaceBounds(cid, wid, sid, &rect) != 0) {
        return false;
    }

    *width = rect.size.width;
    *height = rect.size.height;
    return true;

#elif defined(HAVE_X11)

    Display *display;
    GLXDrawable drawable;

    display = glXGetCurrentDisplay();
    if (!display) {
        return false;
    }

    drawable = glXGetCurrentDrawable();
    if (drawable == None) {
        return false;
    }

    int major = 0, minor = 0;
    if (!glXQueryVersion(display, &major, &minor)) {
        return false;
    }

    // XGetGeometry will fail for PBuffers, whereas glXQueryDrawable should not.
    unsigned w = 0;
    unsigned h = 0;
    if (major > 1 || (major == 1 && minor >= 3)) {
        glXQueryDrawable(display, drawable, GLX_WIDTH, &w);
        glXQueryDrawable(display, drawable, GLX_HEIGHT, &h);
    } else {
        Window root;
        int x, y;
        unsigned bw, depth;
        XGetGeometry(display, drawable,  &root, &x, &y, &w, &h, &bw, &depth);
    }

    *width = w;
    *height = h;
    return true;

#else

    return false;

#endif
}


static GLenum
getTextureTarget(Context &context, GLuint texture)
{
    (void)context;
    if (!glIsTexture(texture)) {
        return GL_NONE;
    }

    /*
     * GL_ARB_direct_state_access's glGetTextureParameteriv(GL_TEXTURE_TARGET)
     * would be perfect, except the fact it's not supported for
     * TEXTURE_BUFFERS...
     */

    GLint result = GL_NONE;

    flushErrors();

    for (auto target : textureTargets) {
        GLenum binding = getTextureBinding(target);

        GLint bound_texture = 0;
        glGetIntegerv(binding, &bound_texture);
        glBindTexture(target, texture);

        bool succeeded = glGetError() == GL_NO_ERROR;

        glBindTexture(target, bound_texture);

        if (succeeded) {
            result = target;
            break;
        }

        flushErrors();
    }

    return result;
}


static bool
getBoundRenderbufferDesc(Context &context, ImageDesc &desc)
{
    (void)context;
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &desc.width);
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &desc.height);
    desc.depth = 1;

    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_SAMPLES, &desc.samples);

    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &desc.internalFormat);

    return desc.valid();
}


static bool
getRenderbufferDesc(Context &context, GLint renderbuffer, ImageDesc &desc)
{
    GLint bound_renderbuffer = 0;
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &bound_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

    getBoundRenderbufferDesc(context, desc);

    glBindRenderbuffer(GL_RENDERBUFFER, bound_renderbuffer);

    return desc.valid();
}


static bool
getFramebufferAttachmentDesc(Context &context, GLenum target, GLenum attachment, ImageDesc &desc)
{
    GLint object_type = GL_NONE;
    glGetFramebufferAttachmentParameteriv(target, attachment,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &object_type);
    if (object_type == GL_NONE) {
        return false;
    }

    GLint object_name = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &object_name);
    if (object_name == 0) {
        return false;
    }

    if (object_type == GL_RENDERBUFFER) {
        return getRenderbufferDesc(context, object_name, desc);
    } else if (object_type == GL_TEXTURE) {
        GLint texture_face = 0;
        glGetFramebufferAttachmentParameteriv(target, attachment,
                                              GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE,
                                              &texture_face);

        GLint texture_level = 0;
        glGetFramebufferAttachmentParameteriv(target, attachment,
                                              GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
                                              &texture_level);

        GLint bound_texture = 0;
        if (texture_face != 0) {
            glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &bound_texture);
            glBindTexture(GL_TEXTURE_CUBE_MAP, object_name);
            getActiveTextureLevelDesc(context, texture_face, texture_level, desc);
            glBindTexture(GL_TEXTURE_CUBE_MAP, bound_texture);
        } else {
            GLenum texture_target = getTextureTarget(context, object_name);
            GLenum texture_binding = getTextureBinding(texture_target);
            glGetIntegerv(texture_binding, &bound_texture);
            glBindTexture(texture_target, object_name);
            getActiveTextureLevelDesc(context, texture_target, texture_level, desc);
            glBindTexture(texture_target, bound_texture);
        }

        return desc.valid();
    } else {
        std::cerr << "warning: unexpected GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = " << enumToString(object_type) << "\n";
        return false;
    }
}


/**
 * Dump the image of the currently bound read buffer.
 */
static inline void
dumpReadBufferImage(StateWriter &writer,
                    Context & context,
                    const char *label,
                    const char *userLabel,
                    GLint width, GLint height,
                    GLenum format, GLenum type,
                    GLenum internalFormat = GL_NONE)
{
    if (internalFormat == GL_NONE) {
        internalFormat = format;
    }

    switch (format) {
    case GL_DEPTH_COMPONENT:
    case GL_DEPTH_STENCIL:
        /* FIXME: NV_read_depth_stencil states that type must match the
            * internal format, whereas we always request GL_FLOAT, as that's
            * what we want.  To fix this we should probe the adequate type
            * here, and then manually convert the pixels to float after
            * glReadPixels */
        break;
    default:
        // Color formats -- GLES glReadPixels only supports the following combinations:
        // - GL_RGBA and GL_UNSIGNED_BYTE
        // - values of IMPLEMENTATION_COLOR_READ_FORMAT and IMPLEMENTATION_COLOR_READ_TYPE
        format = GL_RGBA;
        type = GL_UNSIGNED_BYTE;
        break;
    }

    GLuint channels;
    image::ChannelType channelType;
    getImageFormat(format, type, channels, channelType);

    image::Image *image = new image::Image(width, height, channels, true, channelType);

    flushErrors();

    {
        // TODO: reset imaging state too
        PixelPackState pps(context);

        glReadPixels(0, 0, width, height, format, type, image->pixels);
    }

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        do {
            std::cerr << "warning: " << enumToString(error) << " while reading framebuffer\n";
            error = glGetError();
        } while(error != GL_NO_ERROR);
    } else {
        if (userLabel) {
            image->label = userLabel;
        }

        StateWriter::ImageDesc imageDesc;
        imageDesc.format = formatToString(internalFormat);
        writer.beginMember(label);
        writer.writeImage(image, imageDesc);
        writer.endMember();
    }

    delete image;
}



/**
 * Dump the specified framebuffer attachment.
 *
 * In the case of a color attachment, it assumes it is already bound for read.
 */
static void
dumpFramebufferAttachment(StateWriter &writer, Context &context, GLenum target, GLenum attachment)
{
    ImageDesc desc;
    if (!getFramebufferAttachmentDesc(context, target, attachment, desc)) {
        return;
    }

    assert(desc.samples == 0);

    GLenum format;
    GLenum type;
    switch (attachment) {
    case GL_DEPTH_ATTACHMENT:
        format = GL_DEPTH_COMPONENT;
        type = GL_FLOAT;
        break;
    case GL_STENCIL_ATTACHMENT:
        type = GL_UNSIGNED_BYTE;
        return;
    default:
        assert(desc.internalFormat != GL_NONE);
        const InternalFormatDesc &formatDesc = getInternalFormatDesc(desc.internalFormat);
        chooseReadBackFormat(formatDesc, format, type);
    }

    GLint object_type = GL_NONE;
    glGetFramebufferAttachmentParameteriv(target, attachment,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
                                          &object_type);
    GLint object_name = 0;
    glGetFramebufferAttachmentParameteriv(target, attachment,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &object_name);
    const char *label = enumToString(attachment);

    dumpReadBufferImage(writer, context,
                        label, "",
                        desc.width, desc.height,
                        format, type, desc.internalFormat);
}


static void
dumpFramebufferAttachments(StateWriter &writer, Context &context, GLenum target)
{
    GLenum status = glCheckFramebufferStatus(target);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr
            << "warning: incomplete " << enumToString(target)
            << " (" << enumToString(status) << ")\n";
        return;
    }

    GLint read_framebuffer = 0;
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &read_framebuffer);

    GLint read_buffer = GL_NONE;
    glGetIntegerv(GL_READ_BUFFER, &read_buffer);

    GLint max_draw_buffers = 1;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &max_draw_buffers);
    GLint max_color_attachments = 0;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &max_color_attachments);

    for (GLint i = 0; i < max_draw_buffers; ++i) {
        GLint draw_buffer = GL_NONE;
        glGetIntegerv(GL_DRAW_BUFFER0 + i, &draw_buffer);
        if (draw_buffer != GL_NONE) {
            glReadBuffer(draw_buffer);
            GLint attachment;
            if (draw_buffer >= GL_COLOR_ATTACHMENT0 && draw_buffer < GL_COLOR_ATTACHMENT0 + max_color_attachments) {
                attachment = draw_buffer;
            } else {
                std::cerr << "warning: unexpected GL_DRAW_BUFFER" << i << " = " << draw_buffer << "\n";
                attachment = GL_COLOR_ATTACHMENT0;
            }
            dumpFramebufferAttachment(writer, context, target, attachment);
        }
    }

    glReadBuffer(read_buffer);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, read_framebuffer);
}


void
dumpFramebuffer(StateWriter &writer, Context &context)
{
    writer.beginMember("framebuffer");
    writer.beginObject();

    GLint boundDrawFbo = 0, boundReadFbo = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &boundDrawFbo);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &boundReadFbo);
    if (!boundDrawFbo) {
        //dumpDrawableImages(writer, context);
    } else {
        dumpFramebufferAttachments(writer, context, GL_FRAMEBUFFER);
    }

    writer.endObject();
    writer.endMember(); // framebuffer
}


} /* namespace glstate */
