#include "Support/Logger/Logger.h"

#include "Support/Logger/LogDef.h"

#include <filesystem>
#include <spdlog/async.h>
#include <spdlog/fmt/bundled/base.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>


namespace VyEngine::Support
{
    Ref<spdlog::logger> Logger::s_CoreLogger;
    Ref<spdlog::logger> Logger::s_ClientLogger;

    void Logger::Init(const LogConfig& config, std::string srcDir)
    {
        const auto logDirectory = fmt::format("{0}/{1}", srcDir, config.OutputDirectory);
        auto logDirPath = std::filesystem::path(logDirectory);

        if (!std::filesystem::exists(logDirPath))
        {
            bool dirCreated = std::filesystem::create_directory(logDirPath);
            if (!dirCreated)
            {
                VYCRITICAL("Failed to create log directory at: {}", logDirPath.string())
                exit(EXIT_FAILURE);
            }
        }

        std::vector<spdlog::sink_ptr> logSinks;

        std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v";
        logSinks.emplace_back(MakeRef<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(
            MakeRef<spdlog::sinks::basic_file_sink_mt>(fmt::format("{0}/{1}", config.OutputDirectory, config.LogFilename), true)
        );

        logSinks[0]->set_pattern(pattern);
        logSinks[1]->set_pattern(pattern);

        s_CoreLogger = MakeRef<spdlog::logger>(config.EngineLoggerName, begin(logSinks), end(logSinks));
        spdlog::register_logger(s_CoreLogger);
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_ClientLogger = MakeRef<spdlog::logger>(config.ClientLoggerName, begin(logSinks), end(logSinks));
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
    }
}