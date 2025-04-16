#include "gl_buffer.hpp"

#include <glad/glad.h>

namespace VyEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(std::uint32_t size)
    {
        glCreateBuffers(1, &mID);
        glNamedBufferStorage(mID, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, std::uint32_t size)
    {
        glCreateBuffers(1, &mID);
        glNamedBufferStorage(mID, size, data, GL_DYNAMIC_STORAGE_BIT);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }

    void OpenGLVertexBuffer::SetData(const void* data, std::uint32_t size)
    {
        glNamedBufferSubData(mID, 0, size, data);
    }

    // ==================================================================================

    OpenGLIndexBuffer::OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count) :
        mCount(count)
    {
        glCreateBuffers(1, &mID);
        glNamedBufferStorage(mID, count * sizeof(std::uint32_t), indices, GL_DYNAMIC_STORAGE_BIT);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &mID);
    }
}