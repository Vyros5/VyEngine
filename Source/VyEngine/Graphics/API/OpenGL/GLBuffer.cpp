#include "Graphics/API/OpenGL/GLBuffer.hpp"

#include "Graphics/API/OpenGL/GLEnumType.hpp"

#include <glad/glad.h>

// namespace VyEngine
// {
    // static GLenum BufferTypeToGLenum(VyEngine::GFX::EBufferType type)
    // {
    //     switch (type)
    //     {
    //         case VyEngine::GFX::EBufferType::VERTEX:         return GL_ARRAY_BUFFER;
    //         case VyEngine::GFX::EBufferType::INDEX:          return GL_ELEMENT_ARRAY_BUFFER;
    //         case VyEngine::GFX::EBufferType::UNIFORM:        return GL_UNIFORM_BUFFER;
    //         case VyEngine::GFX::EBufferType::SHADER_STORAGE: return GL_SHADER_STORAGE_BUFFER;
    //         case VyEngine::GFX::EBufferType::UNKNOWN:        return 0;
    //     }

    //     return 0;
    // }

    // static GLenum AccessSpecifierToGLenum(VyEngine::GFX::EAccessSpecifier specifier)
    // {
    //     switch(specifier)
    //     {
    //         case VyEngine::GFX::EAccessSpecifier::STREAM_DRAW:  return GL_STREAM_DRAW;
    //         case VyEngine::GFX::EAccessSpecifier::STREAM_READ:  return GL_STREAM_READ;
    //         case VyEngine::GFX::EAccessSpecifier::STREAM_COPY:  return GL_STREAM_COPY;
    //         case VyEngine::GFX::EAccessSpecifier::STATIC_DRAW:  return GL_STATIC_DRAW;
    //         case VyEngine::GFX::EAccessSpecifier::STATIC_READ:  return GL_STATIC_READ;
    //         case VyEngine::GFX::EAccessSpecifier::STATIC_COPY:  return GL_STATIC_COPY;
    //         case VyEngine::GFX::EAccessSpecifier::DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
    //         case VyEngine::GFX::EAccessSpecifier::DYNAMIC_READ: return GL_DYNAMIC_READ;
    //         case VyEngine::GFX::EAccessSpecifier::DYNAMIC_COPY: return GL_DYNAMIC_COPY;
    //     }

    //     return 0;
    // }


    VyEngine::GFX::API::GLBuffer::TBuffer(VyEngine::GFX::Data::EBufferType type) : m_Buffer{ 
        .type = type 
    }
    {
        glCreateBuffers(1, &m_Buffer.ID);
    }

    VyEngine::GFX::API::GLBuffer::~TBuffer()
    {
        glDeleteBuffers(1, &m_Buffer.ID);
    }

    void VyEngine::GFX::API::GLBuffer::Bind(std::optional<uint32_t> index) const
    {
        VYASSERT(IsValid(), "Cannot bind an invalid buffer");

        if (index.has_value())
        {
            glBindBufferBase(EnumToValue<GLenum>(m_Buffer.type), index.value(), m_Buffer.ID);
        }
        else
        {
            glBindBuffer(EnumToValue<GLenum>(m_Buffer.type), m_Buffer.ID);
        }
    }

    void VyEngine::GFX::API::GLBuffer::Unbind() const
    {
        VYASSERT(IsValid(), "Cannot unbind an invalid buffer");
        glBindBuffer(EnumToValue<GLenum>(m_Buffer.type), 0);
    }

    uint64_t VyEngine::GFX::API::GLBuffer::Allocate(uint64_t size, Data::EAccessSpecifier usage)
    {
        VYASSERT(IsValid(), "Cannot allocate memory for an invalid buffer");
        glNamedBufferData(m_Buffer.ID, size, nullptr, EnumToValue<GLenum>(usage));
        return m_Buffer.allocatedBytes = size;
    }

    void VyEngine::GFX::API::GLBuffer::Upload(const void* data, std::optional<BufferMemoryRange> range)
    {
        VYASSERT(IsValid(),  "Trying to upload data to an invalid buffer");
        VYASSERT(!IsEmpty(), "Trying to upload data to an empty buffer"  );

        glNamedBufferSubData(
            m_Buffer.ID,
            range ? range->offset : 0,
            range ? range->size : m_Buffer.allocatedBytes,
            data
        );
    }

    template <>
    bool VyEngine::GFX::API::GLBuffer::IsValid() const
    {
        return m_Buffer.ID != 0 && m_Buffer.type != Data::EBufferType::UNKNOWN;
    }

    template <>
    bool VyEngine::GFX::API::GLBuffer::IsEmpty() const
    {
        return GetSize() == 0;
    }

    template <>
    uint64_t VyEngine::GFX::API::GLBuffer::GetSize() const
    {
        VYASSERT(IsValid(), "Cannot get size of an invalid buffer");
        return m_Buffer.allocatedBytes;
    }

    template <>
    uint32_t VyEngine::GFX::API::GLBuffer::GetID() const
    {
        VYASSERT(IsValid(), "Cannot get ID of an invalid buffer");
        return m_Buffer.ID;
    }
// }
