#pragma once

#include <vector>
#include <unordered_map>

#include "Graphics/API/Common/TShaderProgram.h"
#include "Graphics/API/OpenGL/GLShaderStage.hpp"

namespace VyEngine::GFX::API
{
    struct GLShaderProgramContext
    {
        const uint32_t ID;
        std::vector<Data::UniformInfo> uniforms;
        std::vector<std::reference_wrapper<const GLShaderStage>> attachedShaders;
        std::unordered_map<std::string, int> uniformLocationCache;

        uint32_t GetUniformLocation(std::string_view name);
    };

    using GLShaderProgram = TShaderProgram<GLShaderProgramContext, GLShaderStageContext>;
}