#pragma once

#include "Graphics/API/Common/TIndexBuffer.h"
#include "Graphics/API/OpenGL/GLBuffer.hpp"

namespace VyEngine::GFX::API
{
	struct GLIndexBufferContext {};
    
	using GLIndexBuffer = TIndexBuffer<GLIndexBufferContext, GLBufferContext>;
}