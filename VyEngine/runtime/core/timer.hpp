#pragma once

#include <chrono>

namespace VyEngine
{
    class Timer
    {
    private:
        using clock = std::chrono::high_resolution_clock; // QueryPerformanceCounter
        using seconds = std::chrono::duration<float, std::ratio<1>>;
        using milliseconds = std::chrono::duration<float, std::milli>;

        std::chrono::time_point<clock> mStart;

    public:
        Timer() : mStart(clock::now()) { };

        // Restart timer to current time.
        void Restart() { mStart = clock::now(); }

        // Get Delta Time as seconds.
        float Elapsed() const { return std::chrono::duration_cast<seconds>(clock::now() - mStart).count(); }
        float ElapsedMs() const { return std::chrono::duration_cast<milliseconds>(clock::now() - mStart).count(); }
    };


    inline long long GetTimeNow() { return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); }
}