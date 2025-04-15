#pragma once

#include "VyLib/vy_core.hpp"
#include <cstdint>

namespace VyEngine
{
    class VertexBuffer;
    class IndexBuffer;

    class VertexArray
    {
    public:

        virtual ~VertexArray() = default;

        virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& VBO) = 0;
        virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& IBO) = 0;

        virtual void Bind() const = 0;

        virtual std::uint32_t GetID() const = 0;
        virtual std::uint32_t GetIndexCount() const = 0;

        static SharedPtr<VertexArray> Create();
    };
}