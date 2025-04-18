#pragma once

#include "core/application.hpp"
#include "core/entry_point.hpp"
#include "core/settings_config.hpp"
#include "core/timer.hpp"

#include "VyLib/vy_core.hpp"

#ifdef ENGINE_USE_ENTRYPOINT
namespace VyEngine
{
    extern UniquePtr<Application> CreateApplication();
}

int main()
{
    auto app = VyEngine::CreateApplication();
    app->Run();

    return 0;
}
#endif