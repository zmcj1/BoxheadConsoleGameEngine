#pragma once

#include "MinDefines.h"

//See VirtualKeys:https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace MinConsoleNative
{
    EXPORT_FUNC MinGetKey(int virtualKey, bool* yes);

    EXPORT_FUNC MinGetKeyPressed(int virtualKey, bool* yes);

    EXPORT_FUNC MinCheckKeyState(int virtualKey, bool* yes);

    class Input
    {
    public:
        static bool GetKey(int virtualKey);

        static bool GetKeyPressed(int virtualKey);

        static bool CheckKeyState(int virtualKey);
    };
}