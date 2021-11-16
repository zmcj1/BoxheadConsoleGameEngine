#include "Timer.hpp"

namespace MinConsoleNative
{
    const double TimerMultiplier = 1.0e6;

    EXPORT_FUNC_EX(MinTimer) MinInitTimer()
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceFrequency(&large_int);

        MinTimer timer;
        timer.start = 0;
        timer.stop = 0;
        timer.frequency = large_int.QuadPart;
        return timer;
    }

    EXPORT_FUNC_EX(bool) MinStartTimer(MinTimer* timer)
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);

        timer->start = large_int.QuadPart;
        return true;
    }

    EXPORT_FUNC_EX(bool) MinStopTimer(MinTimer* timer)
    {
        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);

        timer->stop = large_int.QuadPart;
        return true;
    }

    EXPORT_FUNC_EX(double) MinTimeTimer(const MinTimer* timer, int iterations)
    {
        double deltaTime = (timer->stop - timer->start) * TimerMultiplier / timer->frequency / iterations;
        return deltaTime;
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
        this->timer = MinInitTimer();
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
        return MinTimeTimer(&timer, iterations);
    }
}