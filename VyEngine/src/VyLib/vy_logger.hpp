#pragma once

#include <iostream>
#include <cstdarg>

#define FMT_UNICODE 0
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

#include "vy_core.hpp"


namespace VyEngine
{
    class Log
    {
    public:

        static void Initialize();
        static void Delete();

        inline static SharedPtr<spdlog::logger>& GetCoreLogger() { return sCoreLogger; }
        inline static SharedPtr<spdlog::logger>& GetClientLogger() { return sClientLogger; }
        inline static SharedPtr<std::ostringstream>& GetOString() { return sOString; }

        inline static void Trace(const std::string &log) { GetClientLogger()->trace(log); }
        inline static void CoreTrace(const std::string &log) { GetCoreLogger()->trace(log); }

        inline static void Info(const std::string &log) { GetClientLogger()->info(log); }
        inline static void CoreInfo(const std::string &log) { GetCoreLogger()->info(log); }

        inline static void Warn(const std::string &log) { GetClientLogger()->warn(log); }
        inline static void CoreWarn(const std::string &log) { GetCoreLogger()->warn(log); }

        inline static void Error(const std::string &log) { GetClientLogger()->error(log); }
        inline static void CoreError(const std::string &log) { GetCoreLogger()->error(log); }

        inline static void Critical(const std::string &log) { GetClientLogger()->critical(log); }
        inline static void CoreCritical(const std::string &log) { GetCoreLogger()->critical(log); }

    private:
    
        static SharedPtr<spdlog::logger> sCoreLogger;
        static SharedPtr<spdlog::logger> sClientLogger;

        static SharedPtr<std::ostringstream> sOString;
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
