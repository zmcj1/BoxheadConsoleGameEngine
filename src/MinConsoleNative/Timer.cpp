#include "Timer.h"

namespace MinConsoleNative
{
    const double TimerMultiplier = 1.0e6;

    EXPORT_FUNC MinInitTimer(MinTimer* timer)
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceFrequency(&large_int);

        timer->start = 0;
        timer->stop = 0;
        timer->frequency = large_int.QuadPart;
        return true;
    }

    EXPORT_FUNC MinStartTimer(MinTimer* timer)
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);

        timer->start = large_int.QuadPart;
        return true;
    }

    EXPORT_FUNC MinStopTimer(MinTimer* timer)
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);

        timer->stop = large_int.QuadPart;
        return true;
    }

    EXPORT_FUNC MinTimeTimer(const MinTimer* timer, double* deltaTime, int iterations)
    {
        *deltaTime = (timer->stop - timer->start) * TimerMultiplier / timer->frequency / iterations;
        return true;
    }

    EXPORT_FUNC_EX(float) MinMilliToMinute(int milliSecond)
    {
        return milliSecond / 60.0f / 1000;
    }

    EXPORT_FUNC_EX(int) MinMinuteToMilli(float minute)
    {
        return (int)(minute * 60.0f * 1000);
    }

    Timer::Timer()
    {
        timer = MinTimer();
        MinInitTimer(&timer);
    }

    void Timer::Start()
    {
        MinStartTimer(&timer);
    }

    void Timer::Stop()
    {
        MinStopTimer(&timer);
    }

    double Timer::Time(int iterations)
    {
        double deltaTime = 0;
        MinTimeTimer(&timer, &deltaTime, iterations);
        return deltaTime;
    }
}