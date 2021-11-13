#pragma once

#include "MinDefines.h"

//These macros as VirtualKey
#define LEFT_BUTTON     1
#define RIGHT_BUTTON    2
#define MIDDLE_BUTTON   4

//See VirtualKeys:https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace MinConsoleNative
{
    EXPORT_ENUM_CLASS MouseAxis
    {
        MOUSE_X = 1,
        MOUSE_Y = 2,
    };

    EXPORT_FUNC_EX(bool) MinGetKey(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyDown(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyUp(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyPressed(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyState(int virtualKey);

    //return 0 if no buttons are pressed.
    EXPORT_FUNC_EX(int) MinGetHitKey();

    //call this function in Update, and before invoke MinGetMouseAxis
    EXPORT_FUNC_EX(bool) MinCheckMouseAxis();

    EXPORT_FUNC_EX(bool) MinResetMouseAxis();

    EXPORT_FUNC_EX(int) MinGetMouseAxis(MouseAxis axis);

    //call this function in Update, and before invoke MinGetKeyDownEx/MinGetKeyUpEx
    EXPORT_FUNC_EX(void) MinCheckKeyboardEx();

    EXPORT_FUNC_EX(bool) MinGetKeyEx(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyDownEx(int virtualKey);

    EXPORT_FUNC_EX(bool) MinGetKeyUpEx(int virtualKey);

    class Input
    {
    private:
        Input()
        {
        }

    public:
        static bool GetKey(int virtualKey);

        static bool GetKeyDown(int virtualKey);

        static bool GetKeyUp(int virtualKey);

        static bool GetKeyPressed(int virtualKey);

        static bool GetKeyState(int virtualKey);

        static int GetHitKey();

        //call this function in Update, and before invoke GetMouseAxis
        static void CheckMouseAxis();

        static void ResetMouseAxis();

        static int GetMouseAxis(MouseAxis axis);

        //call this function in Update, and before invoke MinGetKeyDownEx/MinGetKeyUpEx
        static void CheckKeyboardEx();

        static bool GetKeyEx(int virtualKey);

        static bool GetKeyDownEx(int virtualKey);

        static bool GetKeyUpEx(int virtualKey);
    };
}