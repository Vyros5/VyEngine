#pragma once

#include <span>

#include <optional>
#include <glm/glm.hpp>
#include "Graphics/Data/UniformInfo.h"
#include "Graphics/Data/ShaderResults.h"
#include "Graphics/API/Common/TShaderStage.h"

namespace VyEngine::GFX::API
{
    template<typename T>
    concept SupportedUniformType =
        std::same_as<T, float>     ||
        std::same_as<T, int>       ||
        std::same_as<T, glm::vec2> ||
        std::same_as<T, glm::vec3> ||
        std::same_as<T, glm::vec4> ||
        std::same_as<T, glm::mat4> ;

    /**
     *  Represents a Shader Program. Used to link Shader Stages together.
     */
    template<class ProgramContext, class StageContext>
    class TShaderProgram final
    {
    public:
        
        /// @brief Creates a shader program.
        TShaderProgram();

        /// @brief Destroys a shader program.
        ~TShaderProgram();

        /// @brief Attaches a shader stage to the program.
        /// @param shader 
        void Attach(const TShaderStage<StageContext>& shader);
    
        /// @brief Detaches a shader stage from the program.
        /// @param shader 
        void Detach(const TShaderStage<StageContext>& shader);
    
        /// @brief Detaches all shader stages from the program.
        void DetachAll();

        /// @brief Links the shader stages together.
        /// @return 
        Data::ShaderLinkingResult Link();

        /// @brief Binds the program.
        void Bind() const;

        /// @brief Unbinds the program.
        void Unbind() const;

        /// @brief Returns the program ID.
        uint32_t GetID() const;

        /// @brief Sends a uniform value associated with the given name to the GPU.
        /// @tparam T 
        /// @param name 
        /// @param value 
        template<SupportedUniformType T>
        void SetUniform(std::string_view name, const T& value);

        /// @brief Queries the uniforms from the program and caches them in memory.
        void QueryUniforms();

        /// @brief Returns the value of a uniform associated with the given name.
        /// @tparam T 
        /// @param name 
        template<SupportedUniformType T>
        T GetUniform(std::string_view name);

        /// @brief Returns information about the uniform identified by the given name.
        /// @param name 
        std::optional<const Data::UniformInfo> GetUniformInfo(std::string_view name) const;

        /// @brief Returns the uniforms associated with this program.
        std::span<const Data::UniformInfo> GetUniforms() const;

    private:
        ProgramContext m_Context;
    };
}