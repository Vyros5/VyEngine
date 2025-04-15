#pragma once

#include "buffer.hpp"

namespace VyEngine
{
    class OpenGLVertexBuffer : VertexBuffer
    {
    private:
        std::uint32_t mID = 0;
        VertexBufferLayout mLayout;

    public:
        OpenGLVertexBuffer(std::uint32_t size);
        OpenGLVertexBuffer(float* data, std::uint32_t size);

        ~OpenGLVertexBuffer() override;

        void SetData(const void* data, std::uint32_t size) override;
        void SetLayout(const VertexBufferLayout& layout) override { mLayout = layout; }

        const std::uint32_t GetID() const override { return mID; }
        const VertexBufferLayout GetLayout() const override { return mLayout; }
    };

    ///////////////////////////////////////////////////////////////////////////////////////////////

    class OpenGLIndexBuffer : IndexBuffer
    {
    private:
        std::uint32_t mID = 0;
        std::uint32_t mCount = 0;

    public:
        OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count);
        
        ~OpenGLIndexBuffer() override;

        const std::uint32_t GetID() const override { return mID; }
        std::uint32_t GetCount() const override { return mCount; }
    };
}