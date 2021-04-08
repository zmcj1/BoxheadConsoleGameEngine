#pragma once

#include "MinDefines.h"

//Support Virtual Terminal Sequences

#ifndef ESC
#define ESC "\033"   //00011011 = 033 = 27 = 0x1B
#endif

#ifndef CSI
#define CSI "\033["
#endif

#ifndef BELL
#define BELL "\x07"
#endif

namespace MinConsoleNative
{
    enum class TerminalColor
    {
        Black = 0,
        DarkBlue = 4,
        DarkGreen = 2,
        DarkCyan = 6,
        DarkRed = 1,
        DarkMagenta = 5,
        DarkYellow = 3,
        Gray = 7,
        DarkGray = 8,
        Blue = 12,
        Green = 10,
        Cyan = 14,
        Red = 9,
        Magenta = 13,
        Yellow = 11,
        White = 15,
    };
}