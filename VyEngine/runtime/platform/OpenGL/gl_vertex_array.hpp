#pragma once

#include "render/vertex_array.hpp"
#include "render/buffer.hpp"

namespace VyEngine
{
    class OpenGLVertexArray : public VertexArray
    {
    private:
        std::uint32_t mID = 0;
        std::uint32_t mVertexBufferIndex = 0;
        SharedPtr<IndexBuffer> mIndexBuffer;
        std::vector<SharedPtr<VertexBuffer>> mVertexBuffers;

    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;

        void AddVertexBuffer(const SharedPtr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const SharedPtr<IndexBuffer>& indexBuffer) override;

        void Bind() const override;

        std::uint32_t GetID() const override { return mID; }
        std::uint32_t GetIndexCount() const override { return mIndexBuffer ? mIndexBuffer->GetCount() : 0; }
    };
}