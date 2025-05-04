#include "Graphics/API/OpenGL/GLVertexArray.hpp"

#include "Graphics/API/OpenGL/GLEnumType.hpp"

#include <glad/glad.h>

namespace
{
    GLenum DataTypeToGLenum(VyEngine::GFX::Data::EDataType type)
    {
        switch(type)
        {
            using namespace VyEngine::GFX::Data;
            case EDataType::BYTE:           return GL_BYTE;
            case EDataType::UNSIGNED_BYTE:  return GL_UNSIGNED_BYTE;
            case EDataType::SHORT:          return GL_SHORT;
            case EDataType::UNSIGNED_SHORT: return GL_UNSIGNED_SHORT;
            case EDataType::INT:            return GL_INT;
            case EDataType::UNSIGNED_INT:   return GL_UNSIGNED_INT;
            case EDataType::FLOAT:          return GL_FLOAT;
            case EDataType::DOUBLE:         return GL_DOUBLE;
            default:                                            return 0;
        }
    }   

    uint32_t GetDataTypeInBytes(VyEngine::GFX::Data::EDataType type)
    {
        switch(type)
        {
            using namespace VyEngine::GFX::Data;
            case EDataType::BYTE:           return sizeof(GLbyte);
            case EDataType::UNSIGNED_BYTE:  return sizeof(GLubyte);
            case EDataType::SHORT:          return sizeof(GLshort);
            case EDataType::UNSIGNED_SHORT: return sizeof(GLushort);
            case EDataType::INT:            return sizeof(GLint);
            case EDataType::UNSIGNED_INT:   return sizeof(GLuint);
            case EDataType::FLOAT:          return sizeof(GLfloat);
            case EDataType::DOUBLE:         return sizeof(GLdouble);
            default:                                            return 0;
        }
    }    

    uint32_t GetTotalVertexSize(std::span<const VyEngine::GFX::Data::VertexAttribute> attributes)
    {
        uint32_t result = 0;

        for (const auto& attrib : attributes)
        {
            result += GetDataTypeInBytes(attrib.type) * attrib.count;
        }

        return result;
    }
}


template<>
VyEngine::GFX::API::GLVertexArray::TVertexArray()
{
    glCreateVertexArrays(1, &m_Context.ID);
}

template<>
VyEngine::GFX::API::GLVertexArray::~TVertexArray()
{
    glDeleteVertexArrays(1, &m_Context.ID);
}

template<>
void VyEngine::GFX::API::GLVertexArray::SetLayout(Data::VertexAttribLayout attributes, VertexBuffer& vertexBuffer, IndexBuffer& indexBuffer)
{
    VYASSERT(!IsValid(), "Vertex array layout already set");

    Bind();
    indexBuffer.Bind();
    vertexBuffer.Bind();

    uint32_t attribIndex = 0;

    const uint32_t totalSize = GetTotalVertexSize(attributes);
    intptr_t currentOffset = 0;

    for (const auto& attrib : attributes)
    {
        VYASSERT(attrib.count >= 1 && attrib.count <= 4, "Attribute count must be between 1 and 4");

        glEnableVertexAttribArray(attribIndex);

        glVertexAttribPointer(
            static_cast<GLuint>(attribIndex),
            static_cast<GLint>(attrib.count),
            EnumToValue<GLenum>(attrib.type),
            static_cast<GLboolean>(attrib.normalized),
            static_cast<GLsizei>(totalSize),
            reinterpret_cast<GLvoid*>(currentOffset)
        );

        const uint64_t typeSize = GetDataTypeInBytes(attrib.type);
        const uint64_t attribSize = typeSize * attrib.count;
        currentOffset += attribSize;
        ++attribIndex;
        ++m_Context.attribCount;
    }

    Unbind();
    indexBuffer.Unbind();
    vertexBuffer.Unbind();
}

template<>
void VyEngine::GFX::API::GLVertexArray::ResetLayout()
{
    VYASSERT(IsValid(), "Vertex array layout not already set");

    Bind();
    for (uint32_t i = 0; i < m_Context.attribCount; ++i)
    {
        glDisableVertexAttribArray(i);
    }

    m_Context.attribCount = 0;
    Unbind();
}

template<>
void VyEngine::GFX::API::GLVertexArray::Bind() const
{
    glBindVertexArray(m_Context.ID);
}

template<>
void VyEngine::GFX::API::GLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

template<>
bool VyEngine::GFX::API::GLVertexArray::IsValid() const
{
    return m_Context.attribCount > 0;
}

template<>
uint32_t VyEngine::GFX::API::GLVertexArray::GetID() const
{
    return m_Context.ID;
}
