#pragma once

#include <iostream>
#include <cstdarg>

// #define SPDLOG_FMT_EXTERNAL
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "vy_core.hpp"
#include "vy_log_settings.hpp"
#include "vy_platform.hpp"


namespace VyLib
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
#define VY_CORE_TRACE(...) VyLib::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define VY_CORE_INFO(...) VyLib::Log::GetCoreLogger()->info(__VA_ARGS__);
#define VY_CORE_WARN(...) VyLib::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define VY_CORE_ERROR(...) VyLib::Log::GetCoreLogger()->error(__VA_ARGS__);
#define VY_CORE_CRITICAL(...) VyLib::Log::GetCoreLogger()->critical(__VA_ARGS__);

// Client logging
#define VY_TRACE(...) VyLib::Log::GetClientLogger()->trace(__VA_ARGS__);
#define VY_INFO(...) VyLib::Log::GetClientLogger()->info(__VA_ARGS__);
#define VY_WARN(...) VyLib::Log::GetClientLogger()->warn(__VA_ARGS__);
#define VY_ERROR(...) VyLib::Log::GetClientLogger()->error(__VA_ARGS__);
#define VY_CRITICAL(...) VyLib::Log::GetClientLogger()->critical(__VA_ARGS__);



// static void VyLogInfo(const char* pText, ...);
// static void VyLogError(const char* pText, ...);
// static void VyLogWarning(const char* pText, ...);

// static void VyLog(const std::string& text, const LogType type);
// static void VyLogInfo(const std::string text, ...);
// static void VyLogError(const std::string text, ...);
// static void VyLogWarning(const std::string text, ...);

// #define VY_LOG_INFO(text, ...)    { VyLib::Log::VyLogInfo(std::string(__FUNCTION__)    + ": " + std::string(text), ## __VA_ARGS__); }
// #define VY_LOG_ERROR(text, ...)   { VyLib::Log::VyLogError(std::string(__FUNCTION__)   + ": " + std::string(text), ## __VA_ARGS__); }
// #define VY_LOG_WARNING(text, ...) { VyLib::Log::VyLogWarning(std::string(__FUNCTION__) + ": " + std::string(text), ## __VA_ARGS__); }
