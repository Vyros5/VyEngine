#include "Utils/Time/Clock.h"


float VyEngine::Time::Clock::GetFrameRate()
{
    return 1.0f / (__DELTA_TIME);
}

float VyEngine::Time::Clock::GetDeltaTime()
{
    return __DELTA_TIME * __TIME_SCALE;
}

float VyEngine::Time::Clock::GetDeltaTimeUnscaled()
{
    return __DELTA_TIME;
}

float VyEngine::Time::Clock::GetTimeSinceStart()
{
    return __TIME_SINCE_START;
}

float VyEngine::Time::Clock::GetTimeScale()
{
    return __TIME_SCALE;
}

void VyEngine::Time::Clock::Scale(float coeff)
{
    __TIME_SCALE *= coeff;
}

void VyEngine::Time::Clock::SetTimeScale(float timeScale)
{
    __TIME_SCALE = timeScale;
}

void VyEngine::Time::Clock::Init()
{
    __DELTA_TIME = 0.0f;

    __START_TIME = std::chrono::steady_clock::now();
    __CURRENT_TIME = __START_TIME;
    __LAST_TIME = __START_TIME;

    __INITIALIZED = true;
}

void VyEngine::Time::Clock::Update()
{
    __LAST_TIME = __CURRENT_TIME;
    __CURRENT_TIME = std::chrono::steady_clock::now();
    __ELAPSED = __CURRENT_TIME - __LAST_TIME;

    if (__INITIALIZED)
    {
        __DELTA_TIME = __ELAPSED.count() > 0.1 ? 0.1f : static_cast<float>(__ELAPSED.count());
        __TIME_SINCE_START += __DELTA_TIME * __TIME_SCALE;
    }
    else
    {
        Init();
    }
}
