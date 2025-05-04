#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

#include "Core/Base.h"

namespace VyEngine::Support
{
    struct LogConfig
    {
        std::string EngineLoggerName = "ENGINE";
        std::string ClientLoggerName = "CLIENT";
        std::string OutputDirectory  = "Logs";
        std::string LogFilename      = "engine.log";
    };

    class Logger
    {
    public:
        /// @brief Initialize the logger with the desired configuration.
        /// @param config 
        static void Init(const LogConfig& config, std::string srcDir);

        static Ref<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}