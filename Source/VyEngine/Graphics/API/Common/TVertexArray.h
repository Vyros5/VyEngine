#pragma once

#include <cstdint>

#include "Graphics/API/Common/TVertexBuffer.h"
#include "Graphics/API/Common/TIndexBuffer.h"
#include "Graphics/Data/VertexAttrib.h"
#include "Graphics/Data/EData.h"

namespace VyEngine::GFX::API
{
    /**
     *  Represets a Vertex Array. Used to describe the vertex layout to the graphics backend.
     */
    template<class VertexArrayContext, class VertexBufferContext, class IndexBufferContext, class BufferContext>
    class TVertexArray final
    {
    public:
        using VertexBuffer = TVertexBuffer<VertexBufferContext, BufferContext>;
        using IndexBuffer  = TIndexBuffer<IndexBufferContext, BufferContext>;

        /// @brief Creates the vertex array.
        TVertexArray();

        /// @brief Destroys the vertex array.
        ~TVertexArray();

        /// @brief Sets the vertex attribute layout.
        /// @param attributes 
        /// @param vertexBuffer 
        /// @param indexBuffer 
        void SetLayout(
            Data::VertexAttribLayout attributes,
            VertexBuffer& vertexBuffer,
            IndexBuffer& indexBuffer
        );
        
        /// @brief Resets the vertex attribute layout.
        void ResetLayout();
        
        /// @brief Binds the vertex array.
        void Bind() const;

        /// @brief Unbinds the vertex array.
        void Unbind() const;

        /// @brief Returns true if the vertex array is valid (Non-Empty Layout).
        bool IsValid() const;

        /// @brief Returns the vertex array ID.
        uint32_t GetID() const;

    private:
        VertexArrayContext m_Context;
    };
}