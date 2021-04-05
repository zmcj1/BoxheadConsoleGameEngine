#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    extern uint counter;

    //random range[minimum(inclusive), maximum(inclusive)]
    EXPORT_FUNC MinGetRandomValue(uint minimum, uint maximum, uint* value);

    class Random
    {
    public:
        static uint Range(uint minimum, uint maximum);
    };
}