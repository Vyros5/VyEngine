#pragma once

#include <cstdint>

#include "Graphics/API/Common/TShaderStage.h"

namespace VyEngine::GFX::API
{
    struct GLShaderStageContext
    {
        uint32_t ID = 0;
        Data::EShaderType type = Data::EShaderType::VERTEX;
    };

    using GLShaderStage = TShaderStage<GLShaderStageContext>;
}