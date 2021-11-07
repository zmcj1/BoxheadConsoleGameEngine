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

    EXPORT_FUNC_EX(bool) MinGetKey(int virtualKey)
    {
        return (::GetAsyncKeyState(virtualKey) & 0x8000) != 0;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyDown(int virtualKey)
    {
        bool state = MinGetKeyState(virtualKey);
        if (pressDownKeys[virtualKey] != state)
        {
            pressDownKeys[virtualKey] = state;
            return true;
        }
        return false;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyUp(int virtualKey)
    {
        bool state = MinGetKeyState(virtualKey);
        if (releaseUpKeys[virtualKey] != state && !Input::GetKey(virtualKey))
        {
            releaseUpKeys[virtualKey] = state;
            return true;
        }
        return false;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyPressed(int virtualKey)
    {
        return ::GetAsyncKeyState(virtualKey) == -INT16_MAX;
    }

    EXPORT_FUNC_EX(bool) MinGetKeyState(int virtualKey)
    {
        return (::GetKeyState(virtualKey) & 1) == 1;
    }

    EXPORT_FUNC_EX(int) MinGetHitKey()
    {
        if (console.KeyAvailable()) return console.ReadKey(false).VirtualKey;
        else return 0;
    }

    EXPORT_FUNC_EX(bool) MinCheckMouseAxis()
    {
        preMousePos = curMousePos;
        return ::GetCursorPos(&curMousePos);
    }

    EXPORT_FUNC_EX(bool) MinResetMouseAxis()
    {
        bool suc = ::GetCursorPos(&curMousePos);
        if (suc)
        {
            preMousePos = curMousePos;
            return true;
        }
        return false;
    }

    EXPORT_FUNC_EX(int) MinGetMouseAxis(MouseAxis axis)
    {
        int diff = 0;
        switch (axis)
        {
        case MouseAxis::MOUSE_X:
            diff = curMousePos.x - preMousePos.x;
            break;
        case MouseAxis::MOUSE_Y:
            diff = curMousePos.y - preMousePos.y;
            break;
        }
        return diff;
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
        return MinGetKey(virtualKey);
    }

    EXPORT_FUNC_EX(bool) MinGetKeyDownEx(int virtualKey)
    {
        if (MinGetKeyDown(virtualKey))
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
        if (MinGetKeyUp(virtualKey))
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
        return MinGetKey(virtualKey);
    }

    bool Input::GetKeyDown(int virtualKey)
    {
        return MinGetKeyDown(virtualKey);
    }

    bool Input::GetKeyUp(int virtualKey)
    {
        return MinGetKeyUp(virtualKey);
    }

    bool Input::GetKeyPressed(int virtualKey)
    {
        return MinGetKeyPressed(virtualKey);
    }

    bool Input::GetKeyState(int virtualKey)
    {
        return MinGetKeyState(virtualKey);
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
        return MinGetMouseAxis(axis);
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