#pragma once

#include <any>
#include <string>

#include "Graphics/Data/EShader.h"

namespace VyEngine::GFX::Data
{
    struct UniformInfo
    {
        EUniformType type;
        std::string  name;
        uint32_t     location;
        std::any     defaultValue;
    };
}