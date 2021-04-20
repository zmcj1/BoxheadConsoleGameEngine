#include "Input.h"
#include "Console.h"
#include <stdint.h>

namespace MinConsoleNative
{
    static const int KEY_COUNT = 256;

    static bool pressDownKeys[KEY_COUNT] = { 0 };
    static bool releaseUpKeys[KEY_COUNT] = { 0 };

    static POINT preMousePos = { 0 };
    static POINT curMousePos = { 0 };

    struct KeyState
    {
    public:
        bool pressed;
        bool released;
    };

    static KeyState keys[KEY_COUNT] = { 0 };
    static bool keyOldState[KEY_COUNT] = { 0 };
    static bool keyNewState[KEY_COUNT] = { 0 };

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
        if (console.KeyAvailable()) return console.ReadKey(false);
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

    EXPORT_FUNC_EX(void) MinCheckKeyboardEx()
    {
        for (int i = 0; i < KEY_COUNT; i++)
        {
            keys[i].pressed = false;
            keys[i].released = false;

            keyNewState[i] = MinGetKeyEx(i);

            if (keyNewState[i] != keyOldState[i])
            {
                if (keyNewState[i])
                    keys[i].pressed = true;
                else
                    keys[i].released = true;
            }

            keyOldState[i] = keyNewState[i];
        }
    }

    EXPORT_FUNC_EX(bool) MinGetKeyEx(int virtualKey)
    {
        bool yes;
        MinGetKey(virtualKey, &yes);
        return yes;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyDownEx(int virtualKey)
    {
        bool down;
        MinGetKeyDown(virtualKey, &down);
        if (down)
        {
            return true;
        }
        else if (keys[virtualKey].pressed)
        {
            return true;
        }
        else return false;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyUpEx(int virtualKey)
    {
        bool up;
        MinGetKeyUp(virtualKey, &up);
        if (up)
        {
            return true;
        }
        else if (keys[virtualKey].released)
        {
            return true;
        }
        else return false;
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

    void Input::CheckKeyboardEx()
    {
        MinCheckKeyboardEx();
    }

    bool Input::GetKeyEx(int virtualKey)
    {
        return MinGetKeyEx(virtualKey);
    }

    bool Input::GetKeyDownEx(int virtualKey)
    {
        return MinGetKeyDownEx(virtualKey);
    }

    bool Input::GetKeyUpEx(int virtualKey)
    {
        return MinGetKeyUpEx(virtualKey);
    }
}