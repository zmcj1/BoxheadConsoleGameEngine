#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    //random range[minimum(inclusive), maximum(inclusive)]
    EXPORT_FUNC_EX(uint) MinGetRandomValue(uint minimum, uint maximum);

    class Random
    {
    private:
        Random()
        {
        }

    public:
        //random range[minimum(inclusive), maximum(inclusive)]
        static uint Range(uint minimum, uint maximum);
    };
}