#pragma once

#include <cstdint>

namespace VyLib
{
    enum class LogType : uint8_t
    {
        DEBUG   = 0,
        INFO    = 1,
        WARNING = 2,
        ERROR   = 3,
        FATAL   = 4
    };

    enum class LogLevel : uint8_t
    {
        ALL         = 0,
        NO_DEBUG    = 1,
        NO_INFO     = 2,
        ONLY_ERROR  = 3,
        ONLY_FATAL  = 4
    };
}