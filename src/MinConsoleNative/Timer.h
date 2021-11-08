#pragma once

#include "MinDefines.h"

//来源:https://stackoverflow.com/questions/9789474/how-to-get-ticks-from-queryperformancecounter-in-c

//类似的计时器:https://github.com/GiovanniDicanio/StopwatchWin32/blob/master/Stopwatch/Stopwatch.h

namespace MinConsoleNative
{
    EXPORT_STRUCT MinTimer
    {
    public:
        EXPORT_STRUCT_MEMBER LONGLONG start;
        EXPORT_STRUCT_MEMBER LONGLONG stop;
        EXPORT_STRUCT_MEMBER LONGLONG frequency;

        MinTimer()
        {
            this->start = 0;
            this->stop = 0;
            this->frequency = 0;
        }
    };

    extern const double TimerMultiplier;

    EXPORT_FUNC_EX(MinTimer) MinInitTimer();

    EXPORT_FUNC_EX(bool) MinStartTimer(_REF_ MinTimer* timer);

    EXPORT_FUNC_EX(bool) MinStopTimer(_REF_ MinTimer* timer);

    //To return the value in milliseconds, please set iterations to 1000
    EXPORT_FUNC_EX(double) MinTimeTimer(_IN_ const MinTimer* timer, int iterations);

    EXPORT_FUNC_EX(float) MinMilliToMinute(int milliSecond);

    EXPORT_FUNC_EX(int) MinMinuteToMilli(float minute);

    class Timer
    {
    public:
        MinTimer timer;

    public:
        Timer();

        void Start();

        void Stop();

        double Time(int iterations = 1000);
    };
}