#pragma once

#include "VyLib/vy_core.hpp"

namespace VyEngine
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static UniquePtr<GraphicsContext> Create(void* window);
    };
}