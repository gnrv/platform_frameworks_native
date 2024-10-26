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

#pragma once

#include <ui/GraphicTypes.h>
#include "../GLESRenderEngine.h"
#include "../GLFramebuffer.h"
#include "../GLVertexBuffer.h"
#include "GenericProgram.h"

#include <renderengine/Plugin.h>

using namespace std;

struct gl_functions {
    unsigned int (*CreateProgram)();
    unsigned int (*CreateShader)(unsigned int type);
    void (*ShaderSource)(unsigned int shader, int count, const char *const*string, const int *length);
    void (*CompileShader)(unsigned int shader);
    void (*AttachShader)(unsigned int program, unsigned int shader);
    void (*LinkProgram)(unsigned int program);
    void (*GetShaderiv)(unsigned int shader, unsigned int pname, int *params);
    void (*GetProgramiv)(unsigned int program, unsigned int pname, int *params);
    void (*GetShaderInfoLog)(unsigned int shader, int bufSize, int *length, char *infoLog);
    void (*GetProgramInfoLog)(unsigned int program, int bufSize, int *length, char *infoLog);
    int (*GetUniformLocation)(unsigned int program, const char *name);
    int (*GetAttribLocation)(unsigned int program, const char *name);
    void (*DeleteShader)(unsigned int shader);
    void (*DeleteProgram)(unsigned int program);
    void (*UseProgram)(unsigned int program);
    void (*GenBuffers)(int n, unsigned int *buffers);
    void (*DeleteBuffers)(int n, const unsigned int *buffers);
    void (*BindBuffer)(unsigned int target, unsigned int buffer);
    void (*BufferData)(unsigned int target, long size, const void *data, unsigned int usage);
    unsigned int (*GetError)();
    void (*Uniform1fv)(int location, int count, const float *value);
    void (*Uniform1f)(int location, float v0);
    void (*Uniform1i)(int location, int v0);
    void (*GetIntegerv)(unsigned int pname, int *params);
    void (*Viewport)(int x, int y, int width, int height);
    void (*ClearColor)(float red, float green, float blue, float alpha);
    void (*Clear)(unsigned int mask);
    void (*BindFramebuffer)(unsigned int target, unsigned int framebuffer);
    void (*GenFramebuffers)(int n, unsigned int *framebuffers);
    void (*GenTextures)(int n, unsigned int *textures);
    void (*BindTexture)(unsigned int target, unsigned int texture);
    void (*ActiveTexture)(unsigned int texture);
    void (*VertexAttribPointer)(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void *pointer);
    void (*EnableVertexAttribArray)(unsigned int index);
    void (*DrawArrays)(unsigned int mode, int first, int count);
    void (*DisableVertexAttribArray)(unsigned int index);
    void (*TexImage2D)(unsigned int target, int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels);
    void (*TexParameteri)(unsigned int target, unsigned int pname, int param);
    void (*FramebufferTexture2D)(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level);
    unsigned int (*CheckFramebufferStatus)(unsigned int target);
    void (*DeleteFramebuffers)(int n, const unsigned int *framebuffers);
    void (*DeleteTextures)(int n, const unsigned int *textures);
};

namespace android {
namespace renderengine {
namespace gl {

class CrtFilter {
public:
    explicit CrtFilter(GLESRenderEngine& engine);
    virtual ~CrtFilter();

    // Set up render targets, redirecting output to offscreen texture.
    status_t setAsDrawTarget(const DisplaySettings&);
    // Render CRT effect to the bound framebuffer (screen).
    status_t render();

    void dump(std::string& result);

private:
    void drawMesh(GLuint uv, GLuint position);

    GLESRenderEngine& mEngine;

    uint32_t mDisplayWidth = 0;
    uint32_t mDisplayHeight = 0;
    uint32_t mDisplayX = 0;
    uint32_t mDisplayY = 0;
    // Frame buffer holding the composited background.
    GLFramebuffer mCompositionFbo;

    void (*filter_init)(const char *, struct gl_functions *) = nullptr;
    void (*filter_gl_context_lost)() = nullptr;
    void (*filter_gl_context_restored)() = nullptr;
    void (*filter_draw)(int tex, int width, int height) = nullptr;

    // VBO containing vertex and uv data of a fullscreen triangle.
    GLVertexBuffer mMeshBuffer;
    GenericProgram mProgram;
    GLuint mBPosLoc;
    GLuint mBUvLoc;
    GLuint mBTextureLoc;

    string getVertexShader() const;
    string getFragmentShader() const;

    bool mContextLost;
    sp<Plugin> mPlugin;
};

} // namespace gl
} // namespace renderengine
} // namespace android
