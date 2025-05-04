#pragma once

#include "Graphics/Data/EShader.h"
#include "Graphics/Data/ShaderResults.h"

namespace VyEngine::GFX::API
{
    /**
     *  Represents a part of a Shader Program that is responsible for a specific stage (Vertex, Fragment, Geometry, etc...)
     */
    template<class Context>
    class TShaderStage final
    {
    public:
        
        /// @brief Creates a shader stage of the given type.
        /// @param type VERTEX, FRAGMENT, GEOMETRY
        TShaderStage(Data::EShaderType type);

        /// @brief Destroys the shader stage.
        ~TShaderStage();

        /// @brief Uploads the shader source to the graphics backend memory.
        /// @param source 
        void Upload(const std::string& source) const;

        /// @brief Compiles the uploaded shader source.
        /// @return 
        Data::ShaderCompilationResult Compile() const;

        /// @brief Returns the ID of the shader stage.
        uint32_t GetID() const;

    private:
        Context m_Context;
    };
}