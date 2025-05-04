#include "Graphics/API/OpenGL/GLShaderStage.hpp"

#include "Graphics/API/OpenGL/GLEnumType.hpp"
#include <glad/glad.h>

#include "Support/Logger/LogDef.h"

template<>
VyEngine::GFX::API::GLShaderStage::TShaderStage(Data::EShaderType type) : m_Context{
    .ID = static_cast<uint32_t>(glCreateShader(EnumToValue<GLenum>(type))),
    .type = type
}
{}

template<>
VyEngine::GFX::API::GLShaderStage::~TShaderStage()
{
    glDeleteShader(m_Context.ID);
}

template<>
void VyEngine::GFX::API::GLShaderStage::Upload(const std::string& source) const
{
    const char* src = source.c_str();
    glShaderSource(m_Context.ID, 1, &src, nullptr);
}

template<>
VyEngine::GFX::Data::ShaderCompilationResult VyEngine::GFX::API::GLShaderStage::Compile() const
{
    glCompileShader(m_Context.ID);

    GLint status;
    glGetShaderiv(m_Context.ID, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        GLint maxLen;
        glGetShaderiv(m_Context.ID, GL_INFO_LOG_LENGTH, &maxLen);

        std::string errLog(maxLen, ' ');
        glGetShaderInfoLog(m_Context.ID, maxLen, &maxLen, errLog.data());

        VYERROR("Failed to compile shader! ErrorLog: {0}", errLog);

		return {
			.success = false,
			.message = errLog
		};
    }

	return {
		.success = true
	};
}

template<>
uint32_t VyEngine::GFX::API::GLShaderStage::GetID() const
{
    return m_Context.ID;
}