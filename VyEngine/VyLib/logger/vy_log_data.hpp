#pragma once

#include "vy_log_settings.hpp"
#include "vy_platform.hpp"

#include <fstream>

namespace VyLib
{
    struct LoggerData
    {
        std::ofstream logFile;

        LogLevel level = LogLevel::ALL;

        bool abortOnFatal      = true;
        bool stackTraceOnError = true;
        bool logToConsole      = true;
        bool logToFile         = false;

        ConsoleColor colors[5] =
        {
            ConsoleColor::DARK_GRAY,  // debug
            ConsoleColor::WHITE,      // info
            ConsoleColor::YELLOW,     // warning
            ConsoleColor::RED,        // error
            ConsoleColor::DARK_RED,   // fatal
        };
    };
}