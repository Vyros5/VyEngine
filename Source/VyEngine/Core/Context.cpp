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

        // Window::Cfg::DeviceConfig deviceConfig;
        // device = MakeScope<Window::Context::Device>(deviceConfig);
        // window = MakeScope<Window::Window>(*device, windowConfig);

        // window->SetCallbackFunction(std::bind(&Window::Window::OnEvent, std::ref(window), std::placeholders::_1));

        // window->MakeCurrentContext();
    }

    Context::~Context()
    {

    }

    Context* Context::GetInstance()
    {
        return s_ContextInstance;
    }
}