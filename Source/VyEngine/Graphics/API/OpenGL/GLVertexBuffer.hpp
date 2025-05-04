#pragma once

#include "Graphics/API/Common/TVertexBuffer.h"
#include "Graphics/API/OpenGL/GLBuffer.hpp"
#include "Graphics/Data/EData.h"

namespace VyEngine::GFX::API
{
    struct GLVertexBufferContext {};

    using GLVertexBuffer = TVertexBuffer<GLVertexBufferContext, GLBufferContext>;
}