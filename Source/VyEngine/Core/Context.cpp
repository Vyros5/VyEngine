#include "Core/Context.h"

#include <cassert>

namespace VyEngine
{
    /// @brief Global Context Instance.
    static Context* s_ContextInstance = nullptr;


    Context::Context()
    {
        assert(s_ContextInstance == nullptr);
        s_ContextInstance = this;
        
        VYTRACE("Context Created")

        /* Device & Window Creation */
        Display::DeviceConfig deviceConfig;
        displayDevice = MakeScope<Display::Device>(deviceConfig);
        window        = MakeScope<Window::Window>(*displayDevice, windowConfig);

        window->MakeCurrentContext();

        /* Graphics Context Creation */
        gfxDriver = MakeScope<GFX::Driver>(GFX::DriverConfig{ true });
        
    }

    Context::~Context()
    {
        VYTRACE("Context Destroyed")
    }

    Context* Context::GetInstance()
    {
        return s_ContextInstance;
    }
}