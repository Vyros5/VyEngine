#pragma once

#include "Graphics/API/Common/TBuffer.h"

namespace VyEngine::GFX::API
{
    /**
     *  Represets a Vertex Buffer. Used to store vertex data for the graphics backend to use.
     */
    template<class VertexBufferContext, class BufferContext>
    class TVertexBuffer final : public TBuffer<BufferContext>
    {
    public:

        /// @brief Creates a vertex buffer.
        TVertexBuffer();
        
    private:
        VertexBufferContext m_Context;    
    };
}