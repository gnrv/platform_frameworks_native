/**************************************************************************
 *
 * Copyright 2011 Jose Fonseca
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


#include <string.h>

#include <algorithm>
#include <iostream>

#include "image.hpp"
#include "state_writer.hpp"

#include <GLES3/gl3.h>

#include "glsize.hpp"
#include "glstate.hpp"
#include "glstate_internal.hpp"


namespace glstate {


PixelPackState::PixelPackState(const Context &context)
{
    (void)context;
    pixel_buffer_object = true;
    // Start with default state
    pack_alignment = 4;
    pack_image_height = 0;
    pack_lsb_first = GL_FALSE;
    pack_row_length = 0;
    pack_skip_images = 0;
    pack_skip_pixels = 0;
    pack_skip_rows = 0;
    pack_swap_bytes = GL_FALSE;
    pixel_pack_buffer_binding = 0;

    // Get current state
    glGetIntegerv(GL_PACK_ALIGNMENT, &pack_alignment);
    if (pixel_buffer_object) {
        glGetIntegerv(GL_PIXEL_PACK_BUFFER_BINDING, &pixel_pack_buffer_binding);
    }

    // Reset state for compact images
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    if (pixel_buffer_object) {
        glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    }
}

PixelPackState::~PixelPackState() {
    glPixelStorei(GL_PACK_ALIGNMENT, pack_alignment);
    if (pixel_buffer_object) {
        glBindBuffer(GL_PIXEL_PACK_BUFFER, pixel_pack_buffer_binding);
    }
}

TempId::TempId(GLenum _target) :
    target(_target),
    id(0)
{
    switch (target){
    case GL_ARRAY_BUFFER:
        glGenBuffers(1, &id);
        break;
    case GL_FRAMEBUFFER:
        glGenFramebuffers(1, &id);
        break;
    case GL_PROGRAM:
        id = glCreateProgram();
        break;
    case GL_RENDERBUFFER:
        glGenRenderbuffers(1, &id);
        break;
    case GL_TEXTURE:
        glGenTextures(1, &id);
        break;
    case GL_VERTEX_ARRAY:
        glGenVertexArrays(1, &id);
        break;
    default:
        assert(false);
        id = 0;
        return;
    }
}

TempId::~TempId()
{
    switch (target){
    case GL_ARRAY_BUFFER:
        glDeleteBuffers(1, &id);
        break;
    case GL_FRAMEBUFFER:
        glDeleteFramebuffers(1, &id);
        break;
    case GL_PROGRAM:
        glDeleteProgram(id);
        break;
    case GL_RENDERBUFFER:
        glGenRenderbuffers(1, &id);
        break;
    case GL_TEXTURE:
        glDeleteTextures(1, &id);
        break;
    case GL_VERTEX_ARRAY:
        glGenVertexArrays(1, &id);
        break;
    default:
        assert(false);
        id = 0;
        return;
    }
}

TextureBinding::TextureBinding(GLenum _target, GLuint _id) :
    target(_target),
    id(_id),
    prev_id(0)
{
    GLenum binding = getTextureBinding(target);
    glGetIntegerv(binding, (GLint *) &prev_id);
    if (prev_id != id) {
        glBindTexture(target, id);
    }
}

TextureBinding::~TextureBinding() {
    if (prev_id != id) {
        glBindTexture(target, prev_id);
    }
}

static GLenum
getBufferBinding(GLenum target) {
    switch (target) {
    case GL_ARRAY_BUFFER:
        return GL_ARRAY_BUFFER_BINDING;
    case GL_COPY_READ_BUFFER:
        return GL_COPY_READ_BUFFER_BINDING;
    case GL_COPY_WRITE_BUFFER:
        return GL_COPY_WRITE_BUFFER_BINDING;
    case GL_FRAMEBUFFER:
        return GL_FRAMEBUFFER_BINDING;
    case GL_ELEMENT_ARRAY_BUFFER:
        return GL_ELEMENT_ARRAY_BUFFER_BINDING;
    case GL_PIXEL_PACK_BUFFER:
        return GL_PIXEL_PACK_BUFFER_BINDING;
    case GL_PIXEL_UNPACK_BUFFER:
        return GL_PIXEL_UNPACK_BUFFER_BINDING;
    case GL_READ_BUFFER:
        return GL_READ_BUFFER;
    case GL_RENDERBUFFER:
        return GL_RENDERBUFFER_BINDING;
    case GL_TRANSFORM_FEEDBACK_BUFFER:
        return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
    case GL_UNIFORM_BUFFER:
        return GL_UNIFORM_BUFFER_BINDING;
    default:
        assert(false);
        return GL_NONE;
    }
}


BufferBinding::BufferBinding(GLenum _target, GLuint _buffer) :
    target(_target),
    buffer(_buffer),
    prevBuffer(0)
{
    GLenum binding = getBufferBinding(target);
    glGetIntegerv(binding, (GLint *) &prevBuffer);

    if (prevBuffer != buffer) {
        switch(target)
        {
        case GL_READ_BUFFER:
            glReadBuffer(buffer);
            break;
        case GL_FRAMEBUFFER:
            glBindFramebuffer(target, buffer);
            break;
        case GL_RENDERBUFFER:
            glBindRenderbuffer(target, buffer);
            break;
        default:
            glBindBuffer(target, buffer);
            break;
        }
    }
}

BufferBinding::~BufferBinding() {
    if (prevBuffer != buffer) {
        switch(target)
        {
        case GL_READ_BUFFER:
            glReadBuffer(prevBuffer);
            break;
        case GL_FRAMEBUFFER:
            glBindFramebuffer(target, prevBuffer);
            break;
        case GL_RENDERBUFFER:
            glBindRenderbuffer(target, prevBuffer);
            break;
        default:
            glBindBuffer(target, prevBuffer);
            break;
        }
    }
}


BufferMapping::BufferMapping() :
    target(GL_NONE),
    buffer(0),
    map_pointer(NULL),
    unmap(false)
{
}

GLvoid *
BufferMapping::map(GLenum _target, GLuint _buffer)
{
    if (target == _target && buffer == _buffer) {
        return map_pointer;
    }

    target = _target;
    buffer = _buffer;
    map_pointer = NULL;
    unmap = false;

    BufferBinding bb(target, buffer);

    // Recursive mappings of the same buffer are not allowed.  And with the
    // pursuit of persistent mappings for performance this will become more
    // and more common.
    GLint mapped = GL_FALSE;
    glGetBufferParameteriv(target, GL_BUFFER_MAPPED, &mapped);
    if (mapped) {
        glGetBufferPointerv(target, GL_BUFFER_MAP_POINTER, &map_pointer);
        assert(map_pointer != NULL);

        GLint map_offset = 0;
        glGetBufferParameteriv(target, GL_BUFFER_MAP_OFFSET, &map_offset);
        if (map_offset != 0) {
            std::cerr << "warning: " << enumToString(target) << " buffer " << buffer << " is already mapped with offset " << map_offset << "\n";
            // FIXME: This most likely won't work.  We should remap the
            // buffer with the full range, then re-map when done.  This
            // should never happen in practice with persistent mappings
            // though.
            map_pointer = (GLubyte *)map_pointer - map_offset;
        }
    }

    return map_pointer;
}

BufferMapping::~BufferMapping() {
    if (unmap) {
        BufferBinding bb(target, buffer);

        GLenum ret = glUnmapBuffer(target);
        assert(ret == GL_TRUE);
        (void)ret;
    }
}


void
dumpBoolean(StateWriter &writer, GLboolean value)
{
    switch (value) {
    case GL_FALSE:
        writer.writeString("GL_FALSE");
        break;
    case GL_TRUE:
        writer.writeString("GL_TRUE");
        break;
    default:
        writer.writeInt(static_cast<GLint>(value));
        break;
    }
}


void
dumpEnum(StateWriter &writer, GLenum pname)
{
    const char *s = enumToString(pname);
    if (s) {
        writer.writeString(s);
    } else {
        writer.writeInt(pname);
    }
}










void dumpCurrentContext(StateWriter &writer)
{

    Context context;

    dumpParameters(writer, context);

    //dumpShadersUniforms(writer, context);
    dumpTextures(writer, context);
    //dumpFramebuffer(writer, context);
}


} /* namespace glstate */
