#include "Graphics/API/OpenGL/GLShaderProgram.hpp"

#include <glad/glad.h>
#include <array>

#include "Support/Logger/LogDef.h"

#include "Graphics/API/OpenGL/GLEnumType.hpp"

namespace
{
	constexpr bool IsEngineUBOMember(std::string_view name)
	{
		return name.starts_with("ubo_");
	}
}

template<>
VyEngine::GFX::API::GLShaderProgram::TShaderProgram() : m_Context{ .ID = glCreateProgram() } {}

template<>
VyEngine::GFX::API::GLShaderProgram::~TShaderProgram()
{
    glDeleteProgram(m_Context.ID);
}

template<>
void VyEngine::GFX::API::GLShaderProgram::Attach(const GLShaderStage& p_shader)
{
	glAttachShader(m_Context.ID, p_shader.GetID());
	m_Context.attachedShaders.push_back(std::ref(p_shader));
}

template<>
void VyEngine::GFX::API::GLShaderProgram::Detach(const GLShaderStage& p_shader)
{
	glDetachShader(m_Context.ID, p_shader.GetID());
    
	m_Context.attachedShaders.erase(
        std::remove_if(
		    m_Context.attachedShaders.begin(),
		    m_Context.attachedShaders.end(),
		    [&p_shader](const std::reference_wrapper<const GLShaderStage> shader) {
			    return shader.get().GetID() == p_shader.GetID();
		    }
	    )
    );
}

template<>
void VyEngine::GFX::API::GLShaderProgram::DetachAll()
{
	for (auto& shader : m_Context.attachedShaders)
	{
		glDetachShader(m_Context.ID, shader.get().GetID());
	}

	m_Context.attachedShaders.clear();
}

template<>
VyEngine::GFX::Data::ShaderLinkingResult VyEngine::GFX::API::GLShaderProgram::Link()
{
    glLinkProgram(m_Context.ID);
    
    GLint linkStatus;
	glGetProgramiv(m_Context.ID, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE)
    {
        GLint maxLen;
        glGetProgramiv(m_Context.ID, GL_INFO_LOG_LENGTH, &maxLen);

        std::string errLog(maxLen, ' ');
		glGetProgramInfoLog(m_Context.ID, maxLen, &maxLen, errLog.data());

        VYERROR("Failed to link shader program: {0}", errLog);
		
        return {
			.success = false,
			.message = errLog
		};
    }

    QueryUniforms();

	return {
		.success = true
	};
}

template<>
void VyEngine::GFX::API::GLShaderProgram::Bind() const
{
    glUseProgram(m_Context.ID);
}

template<>
void VyEngine::GFX::API::GLShaderProgram::Unbind() const
{
    glUseProgram(0);
}

template<>
uint32_t VyEngine::GFX::API::GLShaderProgram::GetID() const
{
    return m_Context.ID;
}

// ================================================================================================

#define DECLARE_GET_UNIFORM_FN(type, glType, func)                                                        \
template<>                                                                                                \
template<>                                                                                                \
type VyEngine::GFX::API::GLShaderProgram::GetUniform<type>(std::string_view name)                    \
{                                                                                                         \
    type result;                                                                                          \
    if (const uint32_t loc = m_Context.GetUniformLocation(name); loc != -1)                               \
    {                                                                                                     \
        func(m_Context.ID, loc, reinterpret_cast<glType*>(&result));                                      \
    }                                                                                                     \
    return result;                                                                                        \
}

// DECLARE_GET_UNIFORM_FN(int,       GLint,   glGetUniformiv)
// DECLARE_GET_UNIFORM_FN(float,     GLfloat, glGetUniformfv)
DECLARE_GET_UNIFORM_FN(glm::vec2, GLfloat, glGetUniformfv)
DECLARE_GET_UNIFORM_FN(glm::vec3, GLfloat, glGetUniformfv)
DECLARE_GET_UNIFORM_FN(glm::vec4, GLfloat, glGetUniformfv)
DECLARE_GET_UNIFORM_FN(glm::mat4, GLfloat, glGetUniformfv)

// ================================================================================================

#define DECLARE_SET_UNIFORM_FN(type, func, ...)                                                           \
template<>                                                                                                \
template<>                                                                                                \
void VyEngine::GFX::API::GLShaderProgram::SetUniform<type>(std::string_view name, const type& value) \
{                                                                                                         \
    if (const uint32_t loc = m_Context.GetUniformLocation(name); loc != -1)                               \
    {                                                                                                     \
        func(loc, __VA_ARGS__);                                                                           \
    }                                                                                                     \
}

DECLARE_SET_UNIFORM_FN(int,   glUniform1i, value)
DECLARE_SET_UNIFORM_FN(float, glUniform1f, value)
DECLARE_SET_UNIFORM_FN(glm::vec2, glUniform2f, value.x, value.y)
DECLARE_SET_UNIFORM_FN(glm::vec3, glUniform3f, value.x, value.y, value.z)
DECLARE_SET_UNIFORM_FN(glm::vec4, glUniform4f, value.x, value.y, value.z, value.w)
DECLARE_SET_UNIFORM_FN(glm::mat4, glUniformMatrix4fv, 1, GL_TRUE, &value[0][0])

// ================================================================================================

uint32_t VyEngine::GFX::API::GLShaderProgramContext::GetUniformLocation(std::string_view name)
{
    if (uniformLocationCache.find(name.data()) != uniformLocationCache.end())
    {
        return uniformLocationCache.at(name.data());
    }
    
    const GLint loc = glGetUniformLocation(ID, name.data());

    if (loc == -1)
    {
        VYWARN("Uniform [{0}] does not exist!", std::string{ name });
    }

    uniformLocationCache[name.data()] = loc;

    return loc;
}

// ================================================================================================

template<>
std::optional<const VyEngine::GFX::Data::UniformInfo> VyEngine::GFX::API::GLShaderProgram::GetUniformInfo(std::string_view name) const
{
    if (const auto found = std::ranges::find_if(m_Context.uniforms, [name](const auto& e){
        return name.compare(e.name) == 0;
    }); found != m_Context.uniforms.end())
    {
        return *found;
    }

    return std::nullopt;
}

template<>
std::span<const VyEngine::GFX::Data::UniformInfo> VyEngine::GFX::API::GLShaderProgram::GetUniforms() const
{
    return m_Context.uniforms;
}

template<>
void VyEngine::GFX::API::GLShaderProgram::QueryUniforms()
{
    m_Context.uniforms.clear();

    std::array<GLchar, 256> nameBuffer;

    GLint activeUniformCount = 0;
    glGetProgramiv(m_Context.ID, GL_ACTIVE_UNIFORMS, &activeUniformCount);

    for (GLint i = 0; i < activeUniformCount; ++i)
    {
        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLen = 0;

        glGetActiveUniform(m_Context.ID, i, static_cast<GLsizei>(nameBuffer.size()), &actualLen, &arraySize, &type, nameBuffer.data());

        const auto name = std::string{ nameBuffer.data(), static_cast<size_t>(actualLen) };
        const auto uniformType = ValueToEnum<Data::EUniformType>(type);

        if (!IsEngineUBOMember(name))
        {
            const std::any uniformValue = [&]()->std::any{
                switch(uniformType)
                {
                    using enum Data::EUniformType;
					case BOOL:       return GetUniform<int>(name);
					case INT:        return GetUniform<int>(name);
					case FLOAT:      return GetUniform<float>(name);
					case FLOAT_VEC2: return GetUniform<glm::vec2>(name);
					case FLOAT_VEC3: return GetUniform<glm::vec3>(name);
					case FLOAT_VEC4: return GetUniform<glm::vec4>(name);
					case FLOAT_MAT4: return GetUniform<glm::mat4>(name);
					// case EUniformType::SAMPLER_2D: return std::make_any<Resources::Texture*>(nullptr);
					default: return std::nullopt;
                }
            }();
            
            // Only add the uniform if it has a value (unsupported uniform types will be ignored)
            if (uniformValue.has_value())
            {
                m_Context.uniforms.push_back(Data::UniformInfo{
                    .type = uniformType,
                    .name = name,
                    .location = m_Context.GetUniformLocation(name),
                    .defaultValue = uniformValue
                });
            }
        }
    }
}
