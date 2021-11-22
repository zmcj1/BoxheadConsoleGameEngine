#pragma once

#include "MinDefines.hpp"

namespace MinConsoleNative
{
    class Math
    {
    private:
        Math()
        {
        }

    public:
        //Prime numbers with increments close to 2
        static const int PrimeNumbers[29];

        static const float PI;

        //弧度转角度
        static const float Rad2Deg;

        //角度转弧度
        static const float Deg2Rad;
    };
}