#include "vy_logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace VyEngine
{
    SharedPtr<spdlog::logger> Log::sCoreLogger;
    SharedPtr<spdlog::logger> Log::sClientLogger;

    void Log::Init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks[0]->set_level(spdlog::level::trace);
        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
    
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/VyEngine.log", true));
        logSinks[1]->set_level(spdlog::level::trace);
        logSinks[1]->set_pattern("%^[%T] %n: %v%$");
    
        sCoreLogger = MakeSharedPtr<spdlog::logger>("ENGINE", logSinks.begin(), logSinks.end());
        sCoreLogger->set_level(spdlog::level::trace);
    
        sClientLogger = MakeSharedPtr<spdlog::logger>("APP", logSinks.begin(), logSinks.end());
        sClientLogger->set_level(spdlog::level::trace);
    }
}