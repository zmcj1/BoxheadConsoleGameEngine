#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    class Debug
    {
    public:
        static void Output(const std::wstring& msg);

        static void OutputLine(const std::wstring& msg);
    };
}