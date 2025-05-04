#pragma once

#include <span>

#include "Graphics/Data/EData.h"

namespace VyEngine::GFX::Data
{
	/**
	*   Structure that holds information about a uniform.
	*/
    struct VertexAttribute
    {
        EDataType type  = EDataType::FLOAT;
        uint8_t count   = 4;
        bool normalized = false;
    };

    using VertexAttribLayout = std::span<const VertexAttribute>;
}