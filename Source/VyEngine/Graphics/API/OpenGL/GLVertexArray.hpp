#pragma once

#include <cstdint>

#include "Graphics/API/Common/TVertexArray.h"
#include "Graphics/API/OpenGL/GLVertexBuffer.hpp"
#include "Graphics/API/OpenGL/GLIndexBuffer.hpp"
#include "Graphics/Data/EData.h"

namespace VyEngine::GFX::API
{
    struct GLVertexArrayContext
    {
        uint32_t ID = 0;
        uint32_t attribCount = 0;
    };

    using GLVertexArray = TVertexArray<GLVertexArrayContext, GLVertexBufferContext, GLIndexBufferContext, GLBufferContext>;
}
