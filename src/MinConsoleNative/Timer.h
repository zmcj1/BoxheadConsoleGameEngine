#pragma once

#include "MinDefines.h"

//From:https://stackoverflow.com/questions/9789474/how-to-get-ticks-from-queryperformancecounter-in-c

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

    EXPORT_FUNC MinInitTimer(MinTimer* timer);

    EXPORT_FUNC MinStartTimer(MinTimer* timer);

    EXPORT_FUNC MinStopTimer(MinTimer* timer);

    //To return the value in milliseconds, please set iterations to 1000
    EXPORT_FUNC MinTimeTimer(const MinTimer* timer, double* deltaTime, int iterations);

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