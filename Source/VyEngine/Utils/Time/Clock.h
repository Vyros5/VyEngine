#pragma once

#include <chrono>
#include <string>

namespace VyEngine::Time
{
    class Clock
    {
    public:

        /// @brief Update the clock.
        void Update();

        /// @brief Return the actual framerate (Depends on the Delta Time)
        float GetFrameRate();

        /// @brief Return the actual Delta Time (Scale applied)
        float GetDeltaTime();

        /// @brief Return the actual Delta Time (Scale not applied)
        float GetDeltaTimeUnscaled();

        /// @brief Return the time elapsed since the clock was created.
        float GetTimeSinceStart();

        /// @brief Return the current timescale
        float GetTimeScale();

        /// @brief Multiply the timescale by the given coefficient
        /// @param coefficient 
        void Scale(float coeff);

        /// @brief Define a timescale
        /// @param timeScale 
        void SetTimeScale(float timeScale);

    private:
        void Init();

        std::chrono::steady_clock::time_point __START_TIME;
        std::chrono::steady_clock::time_point __LAST_TIME;
        std::chrono::steady_clock::time_point __CURRENT_TIME;
        std::chrono::duration<double>         __ELAPSED;

        bool __INITIALIZED       { false };
        float __TIME_SCALE       { 1.0f };
        float __DELTA_TIME       { 0.0f };
        float __TIME_SINCE_START { 0.0f };
    };
}