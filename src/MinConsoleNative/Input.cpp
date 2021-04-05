#include "Input.h"
#include <stdint.h>

namespace MinConsoleNative
{
    static const int KEY_COUNT = 256;

    static bool pressDownKeys[KEY_COUNT] = { 0 };
    static bool releaseUpKeys[KEY_COUNT] = { 0 };

    EXPORT_FUNC MinGetKey(int virtualKey, bool* yes)
    {
        *yes = (::GetAsyncKeyState(virtualKey) & 0x8000) != 0;
        return true;
    }

    EXPORT_FUNC MinGetKeyDown(int virtualKey, bool* yes)
    {
        bool state = false;
        MinCheckKeyState(virtualKey, &state);

        if (pressDownKeys[virtualKey] != state)
        {
            pressDownKeys[virtualKey] = state;
            *yes = true;
            return true;
        }
        *yes = false;
        return true;
    }

    EXPORT_FUNC MinGetKeyUp(int virtualKey, bool* yes)
    {
        bool state = false;
        MinCheckKeyState(virtualKey, &state);

        if (releaseUpKeys[virtualKey] != state && !Input::GetKey(virtualKey))
        {
            releaseUpKeys[virtualKey] = state;
            *yes = true;
            return true;
        }
        *yes = false;
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

    bool Input::GetKeyDown(int virtualKey)
    {
        bool yes = false;
        MinGetKeyDown(virtualKey, &yes);
        return yes;
    }

    bool Input::GetKeyUp(int virtualKey)
    {
        bool yes = false;
        MinGetKeyUp(virtualKey, &yes);
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