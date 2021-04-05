﻿#pragma once

#include "MinDefines.h"

//These macros as VirtualKey
#define LEFT_BUTTON     1
#define RIGHT_BUTTON    2
#define MIDDLE_BUTTON   4

//See VirtualKeys:https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace MinConsoleNative
{
    enum class MouseAxis
    {
        MOUSE_X = 1,
        MOUSE_Y = 2,
    };

    EXPORT_FUNC MinGetKey(int virtualKey, bool* yes);

    EXPORT_FUNC MinGetKeyDown(int virtualKey, bool* yes);

    EXPORT_FUNC MinGetKeyUp(int virtualKey, bool* yes);

    EXPORT_FUNC MinGetKeyPressed(int virtualKey, bool* yes);

    EXPORT_FUNC MinGetKeyState(int virtualKey, bool* yes);

    //call this before invoke MinGetMouseAxis
    EXPORT_FUNC MinCheckMouseAxis();

    EXPORT_FUNC MinResetMouseAxis();

    EXPORT_FUNC MinGetMouseAxis(MouseAxis axis, int* diff);

    class Input
    {
    public:
        static bool GetKey(int virtualKey);

        static bool GetKeyDown(int virtualKey);

        static bool GetKeyUp(int virtualKey);

        static bool GetKeyPressed(int virtualKey);

        static bool GetKeyState(int virtualKey);

        static void CheckMouseAxis();

        static void ResetMouseAxis();

        static int GetMouseAxis(MouseAxis axis);
    };
}