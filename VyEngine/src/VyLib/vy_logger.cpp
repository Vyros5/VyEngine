#include "vy_logger.hpp"

#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace VyEngine
{
    SharedPtr<spdlog::logger> Log::sCoreLogger;
    SharedPtr<spdlog::logger> Log::sClientLogger;

    SharedPtr<std::ostringstream> Log::sOString;

    void Log::Initialize()
    {
        sOString = std::make_shared<std::ostringstream>();

        auto sink1 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto sink2 = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("Logs/log.txt", 1024 * 1024 * 5, 3);
        auto sink3 = std::make_shared<spdlog::sinks::ostream_sink_mt>(*sOString);

        std::vector<spdlog::sink_ptr> sinks = { sink1, sink2, sink3 };

        std::string pattern = "[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v";
        spdlog::init_thread_pool(8192, 1);

        sCoreLogger = std::make_shared<spdlog::async_logger>(
            "Engine", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block
        );
        sCoreLogger->set_pattern(pattern);
        sCoreLogger->set_level(spdlog::level::trace);

        sClientLogger = std::make_shared<spdlog::async_logger>(
            "Client", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block
        );
        sCoreLogger->set_pattern(pattern);
        sCoreLogger->set_level(spdlog::level::trace);
    }

    void Log::Delete()
    {
        sCoreLogger->flush();
        sClientLogger->flush();
        spdlog::drop_all();
    }
}


// sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
// sinks[0]->set_level(spdlog::level::trace);
// sinks[0]->set_pattern("%^[%T] %n: %v%$");

// sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/VyEngine.log", true));
// sinks[1]->set_level(spdlog::level::trace);
// sinks[1]->set_pattern("%^[%T] %n: %v%$");

// sCoreLogger = MakeSharedPtr<spdlog::logger>("ENGINE", sinks.begin(), sinks.end());
// sCoreLogger->set_level(spdlog::level::trace);

// sClientLogger = MakeSharedPtr<spdlog::logger>("APP", sinks.begin(), sinks.end());
// sClientLogger->set_level(spdlog::level::trace);