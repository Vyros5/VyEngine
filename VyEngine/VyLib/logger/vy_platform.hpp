#pragma once

#include <ostream>

namespace VyLib
{
    enum class ConsoleColor : uint8_t
    {
        BLACK,
        DARK_BLUE,
        DARK_GREEN,
        DARK_CYAN,
        DARK_RED,
        DARK_MAGENTA,
        DARK_YELLOW,
        DARK_GRAY,
        GRAY,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        YELLOW,
        WHITE,
    };

    void SetConsoleColor(ConsoleColor color);
    void PrintStackTrace(std::ostream& out);
    std::string GetCurrentTime();
    void AbortApplication();
}