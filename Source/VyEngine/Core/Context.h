#pragma once

// #include <EASTL/unique_ptr.h>

// #include "Containers/Pointers.h"
#include "Window/Window.h"
#include "Render/Device/Device.h"
#include "Core/Base.h"

namespace VyEngine
{
    class Context // : public RefCounted
    {
        // friend class Object;

    public:
        
        Context();

        ~Context();
    
        /// @brief Return global instance of Context Object.
        /// @note Only one Context may exist within the application.
        /// @return Context
        static Context* GetInstance();


        // Object* GetSubSystem() const;
    // public:
    //     Scope<Window::Context::Device> device;
    //     Scope<Window::Window>     window;
    //     Window::Cfg::WindowConfig windowConfig;
    };
}