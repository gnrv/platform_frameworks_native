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

    void (*filter_init)(const char *) = nullptr;
    void (*filter_gl_context_lost)() = nullptr;
    void (*filter_gl_context_restored)() = nullptr;
    void (*filter_draw)(int tex) = nullptr;

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
