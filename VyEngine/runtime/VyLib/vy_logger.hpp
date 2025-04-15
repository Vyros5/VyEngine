#pragma once

#include <iostream>
#include <cstdarg>

// #define SPDLOG_FMT_EXTERNAL
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "vy_core.hpp"


namespace VyEngine
{
    class Log
    {
    public:

        static void Init();

        const static SharedPtr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
        const static SharedPtr<spdlog::logger>& GetClientLogger() { return sClientLogger; }

    private:
    
        static SharedPtr<spdlog::logger> sCoreLogger;
        static SharedPtr<spdlog::logger> sClientLogger;
    };
}

// Engine logging
#define VY_CORE_TRACE(...) VyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define VY_CORE_INFO(...) VyEngine::Log::GetCoreLogger()->info(__VA_ARGS__);
#define VY_CORE_WARN(...) VyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define VY_CORE_ERROR(...) VyEngine::Log::GetCoreLogger()->error(__VA_ARGS__);
#define VY_CORE_CRITICAL(...) VyEngine::Log::GetCoreLogger()->critical(__VA_ARGS__);

// Client logging
#define VY_TRACE(...) VyEngine::Log::GetClientLogger()->trace(__VA_ARGS__);
#define VY_INFO(...) VyEngine::Log::GetClientLogger()->info(__VA_ARGS__);
#define VY_WARN(...) VyEngine::Log::GetClientLogger()->warn(__VA_ARGS__);
#define VY_ERROR(...) VyEngine::Log::GetClientLogger()->error(__VA_ARGS__);
#define VY_CRITICAL(...) VyEngine::Log::GetClientLogger()->critical(__VA_ARGS__);
