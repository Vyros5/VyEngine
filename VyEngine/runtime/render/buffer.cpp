#include "platform/OpenGL/gl_buffer.hpp"
// #include "buffer.hpp"

namespace VyEngine
{
    SharedPtr<VertexBuffer> VertexBuffer::Create(std::uint32_t size)
    {
        return MakeSharedPtr<OpenGLVertexBuffer>(size);
    }


    SharedPtr<VertexBuffer> VertexBuffer::Create(float* vertices, std::uint32_t size)
    {
        return MakeSharedPtr<OpenGLVertexBuffer>(vertices, size);
    }

    // ==================================================================================

    SharedPtr<IndexBuffer> IndexBuffer::Create(std::uint32_t* indices, std::uint32_t count)
    {
        return MakeSharedPtr<OpenGLIndexBuffer>(indices, count);
    }
}