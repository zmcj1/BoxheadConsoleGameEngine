#include "Input.h"
#include <stdint.h>

namespace MinConsoleNative
{
    EXPORT_FUNC MinGetKey(int virtualKey, bool* yes)
    {
        *yes = (::GetAsyncKeyState(virtualKey) & 0x8000) != 0;
        return true;
    }

    EXPORT_FUNC MinGetKeyPressed(int virtualKey, bool* yes)
    {
        *yes = ::GetAsyncKeyState(virtualKey) == -INT16_MAX;
        return true;
    }

    EXPORT_FUNC MinCheckKeyState(int virtualKey, bool* yes)
    {
        *yes = (::GetKeyState(virtualKey) & 1) == 1;
        return true;
    }

    bool Input::GetKey(int virtualKey)
    {
        bool yes = false;
        MinGetKey(virtualKey, &yes);
        return yes;
    }

    bool Input::GetKeyPressed(int virtualKey)
    {
        bool yes = false;
        MinGetKeyPressed(virtualKey, &yes);
        return yes;
    }

    bool Input::CheckKeyState(int virtualKey)
    {
        bool yes = false;
        MinCheckKeyState(virtualKey, &yes);
        return yes;
    }
}