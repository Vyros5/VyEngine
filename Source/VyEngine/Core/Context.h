#pragma once


#include "Core/Base.h"
#include "Window/Window.h"
#include "Render/Device/Device.h"
#include "Graphics/Driver/Driver.h"

namespace VyEngine
{
    class Context
    {
    public:
        
        Context();

        ~Context();
    
        /// @brief Return global instance of Context Object.
        /// @note Only one Context may exist within the application.
        /// @return Context
        static Context* GetInstance();

    public:
        Scope<Window::Window>     window;
        Scope<Display::Device>    displayDevice;
        Scope<GFX::Driver>        gfxDriver;

        Window::Cfg::WindowConfig windowConfig;
        
    };
}