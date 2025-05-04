#pragma once

#include "Graphics/API/Common/TBuffer.h"

namespace VyEngine::GFX::API
{
    /**
     *  Represets a Index Buffer. Used to store index data for the graphics backend to use.
     */
    template<class IndexBufferContext, class BufferContext>
    class TIndexBuffer final : public TBuffer<BufferContext>
    {
    public:

        /// @brief Creates an index buffer.
        TIndexBuffer();
        
    private:
        IndexBufferContext m_Context;    
    };
}