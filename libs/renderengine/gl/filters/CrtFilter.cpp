/*
 * Copyright 2024 Arvid Nilsson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define ATRACE_TAG ATRACE_TAG_GRAPHICS

#include "CrtFilter.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <ui/GraphicTypes.h>
#include <cstdint>

#include <android-base/stringprintf.h>
#include <utils/Trace.h>

#include <dlfcn.h>

#include "state_writer.hpp"
#include "glstate.hpp"

#include <fstream>

namespace android {

using base::StringAppendF;

namespace renderengine {
namespace gl {

static bool sInitialized = false;

CrtFilter::CrtFilter(GLESRenderEngine& engine)
      : mEngine(engine),
        mCompositionFbo(engine),
        mProgram(engine),
        mContextLost(sInitialized),
        mPlugin(Plugin::createPlugin("libcrtfilter.so")) {
    filter_init = (void (*)(const char *, struct gl_functions*))mPlugin->symbol("filter_init");
    filter_gl_context_lost = (void (*)())mPlugin->symbol("filter_gl_context_lost");
    filter_gl_context_restored = (void (*)())mPlugin->symbol("filter_gl_context_restored");
    filter_draw = (void (*)(int, int, int))mPlugin->symbol("filter_draw");

    mProgram.compile(getVertexShader(), getFragmentShader());
    mBPosLoc = mProgram.getAttributeLocation("aPosition");
    mBUvLoc = mProgram.getAttributeLocation("aUV");
    mBTextureLoc = mProgram.getUniformLocation("uTexture");

    static constexpr auto size = 2.0f;
    static constexpr auto translation = 1.0f;
    const GLfloat vboData[] = {
        // Vertex data
        translation - size, -translation - size,
        translation - size, -translation + size,
        translation + size, -translation + size,
        // UV data
        0.0f, 0.0f - translation,
        0.0f, size - translation,
        size, size - translation
    };
    mMeshBuffer.allocateBuffers(vboData, 12 /* size */);
}

CrtFilter::~CrtFilter() {
    if (filter_gl_context_lost) {
        filter_gl_context_lost();
    }
}

status_t CrtFilter::setAsDrawTarget(const DisplaySettings& display) {
    ATRACE_NAME("CrtFilter::setAsDrawTarget");
    mDisplayX = display.physicalDisplay.left;
    mDisplayY = display.physicalDisplay.top;

    if (mDisplayWidth < display.physicalDisplay.width() ||
        mDisplayHeight < display.physicalDisplay.height()) {
        ATRACE_NAME("CrtFilter::allocatingTextures");

        mDisplayWidth = display.physicalDisplay.width();
        mDisplayHeight = display.physicalDisplay.height();
        mCompositionFbo.allocateBuffersWithAlpha(mDisplayWidth, mDisplayHeight);

        if (mCompositionFbo.getStatus() != GL_FRAMEBUFFER_COMPLETE) {
            ALOGE("Invalid composition buffer");
            return mCompositionFbo.getStatus();
        }
    }

    mCompositionFbo.bind();
    glViewport(0, 0, mCompositionFbo.getBufferWidth(), mCompositionFbo.getBufferHeight());
    return NO_ERROR;
}

void dumpState()
{
    static int fileIndex = 0;
    std::ostringstream filePath;
    filePath << "/data/local/tmp/glstate" << fileIndex++ << ".json";
    std::ofstream outFile(filePath.str());
    if (outFile.is_open()) {
        StateWriter *writer = createJSONStateWriter(outFile);
        glstate::dumpCurrentContext(*writer);
        delete writer;
    } else {
        ALOGE("Failed to open file: %s", filePath.str().c_str());
    }
}

status_t CrtFilter::render() {
    if (!sInitialized) {
        if (filter_init) {
            static gl_functions gl = {
    glCreateProgram,
    glCreateShader,
    glShaderSource,
    glCompileShader,
    glAttachShader,
    glLinkProgram,
    glGetShaderiv,
    glGetProgramiv,
    glGetShaderInfoLog,
    glGetProgramInfoLog,
    glGetUniformLocation,
    glGetAttribLocation,
    glDeleteShader,
    glDeleteProgram,
    glUseProgram,
    glGenBuffers,
    glDeleteBuffers,
    glBindBuffer,
    glBufferData,
    glGetError,
    glUniform1fv,
    glUniform1f,
    glUniform1i,
    glGetIntegerv,
    glViewport,
    glClearColor,
    glClear,
    glBindFramebuffer,
    glGenFramebuffers,
    glGenTextures,
    glBindTexture,
    glActiveTexture,
    glVertexAttribPointer,
    glEnableVertexAttribArray,
    glDrawArrays,
    glDisableVertexAttribArray,
    glTexImage2D,
    glTexParameteri,
    glFramebufferTexture2D,
    glCheckFramebufferStatus,
    glDeleteFramebuffers,
    glDeleteTextures
            };
            ALOGI("Initializing CRT filter");
            filter_init(nullptr/*"/data/local/tmp/crtfilter.log"*/, &gl);
            ALOGI("Initialized CRT filter");
        }
        mEngine.checkErrors("Initializing CRT filter");
        sInitialized = true;
    }

    if (mContextLost) {
        if (filter_gl_context_restored)
            filter_gl_context_restored();
        mContextLost = false;
    }

    ATRACE_NAME("CrtFilter::render");
    glDisable(GL_BLEND);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisableVertexAttribArray(0);
    glUseProgram(0);
    filter_draw(mCompositionFbo.getTextureName(), mDisplayWidth, mDisplayHeight);
    // Use RenderEngine objects to blit
    // mProgram.useProgram();
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(mBTextureLoc, 0);
    // glBindTexture(GL_TEXTURE_2D, mCompositionFbo.getTextureName());
    // drawMesh(mBUvLoc, mBPosLoc);
    //dumpState();

    mEngine.checkErrors("Drawing crt mesh");
    // get the green test to pass
    // glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT);
    return NO_ERROR;
}

void CrtFilter::dump(std::string& result) {
    StringAppendF(&result, "Loaded symbols init: %p, draw: %p\n", filter_init, filter_draw);
}

void CrtFilter::drawMesh(GLuint uv, GLuint position) {

    glEnableVertexAttribArray(uv);
    glEnableVertexAttribArray(position);
    mMeshBuffer.bind();
    glVertexAttribPointer(position, 2 /* size */, GL_FLOAT, GL_FALSE,
                          2 * sizeof(GLfloat) /* stride */, 0 /* offset */);
    glVertexAttribPointer(uv, 2 /* size */, GL_FLOAT, GL_FALSE, 0 /* stride */,
                          (GLvoid*)(6 * sizeof(GLfloat)) /* offset */);
    mMeshBuffer.unbind();

    // draw mesh
    glDrawArrays(GL_TRIANGLES, 0 /* first */, 3 /* count */);
}

string CrtFilter::getVertexShader() const {
    return R"SHADER(#version 100
        precision mediump float;

        attribute vec2 aPosition;
        attribute highp vec2 aUV;
        varying highp vec2 vUV;

        void main() {
            vUV = aUV;
            gl_Position = vec4(aPosition, 0.0, 1.0);
        }
    )SHADER";
}

string CrtFilter::getFragmentShader() const {
    return R"SHADER(#version 100
        precision mediump float;

        uniform sampler2D uTexture;

        varying highp vec2 vUV;

        void main() {
            gl_FragColor  = texture2D(uTexture, vUV, 0.0);
        }
    )SHADER";
}

} // namespace gl
} // namespace renderengine
} // namespace android
