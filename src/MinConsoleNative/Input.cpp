#include "Input.h"
#include <conio.h> //Windows only
#include <stdint.h>

namespace MinConsoleNative
{
    static const int KEY_COUNT = 256;

    static bool pressDownKeys[KEY_COUNT] = { 0 };
    static bool releaseUpKeys[KEY_COUNT] = { 0 };

    static POINT preMousePos = { 0 };
    static POINT curMousePos = { 0 };

    EXPORT_FUNC MinGetKey(int virtualKey, bool* yes)
    {
        *yes = (::GetAsyncKeyState(virtualKey) & 0x8000) != 0;
        return true;
    }

    EXPORT_FUNC MinGetKeyDown(int virtualKey, bool* yes)
    {
        bool state = false;
        MinGetKeyState(virtualKey, &state);

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
        MinGetKeyState(virtualKey, &state);

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

    EXPORT_FUNC MinGetKeyState(int virtualKey, bool* yes)
    {
        *yes = (::GetKeyState(virtualKey) & 1) == 1;
        return true;
    }

    EXPORT_FUNC_EX(int) MinGetHitKey()
    {
        if (::_kbhit()) return ::_getch();
        else return 0;
    }

    EXPORT_FUNC MinCheckMouseAxis()
    {
        preMousePos = curMousePos;
        return ::GetCursorPos(&curMousePos);
    }

    EXPORT_FUNC MinResetMouseAxis()
    {
        ::GetCursorPos(&curMousePos);
        preMousePos = curMousePos;
        return true;
    }

    EXPORT_FUNC MinGetMouseAxis(MouseAxis axis, int* diff)
    {
        switch (axis)
        {
        case MouseAxis::MOUSE_X:
            *diff = curMousePos.x - preMousePos.x;
            break;
        case MouseAxis::MOUSE_Y:
            *diff = curMousePos.y - preMousePos.y;
            break;
        }
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

    bool Input::GetKeyState(int virtualKey)
    {
        bool yes = false;
        MinGetKeyState(virtualKey, &yes);
        return yes;
    }

    int Input::GetHitKey()
    {
        return MinGetHitKey();
    }

    void Input::CheckMouseAxis()
    {
        MinCheckMouseAxis();
    }

    void Input::ResetMouseAxis()
    {
        MinResetMouseAxis();
    }

    int Input::GetMouseAxis(MouseAxis axis)
    {
        int diff = 0;
        MinGetMouseAxis(axis, &diff);
        return diff;
    }
}