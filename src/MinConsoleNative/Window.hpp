#pragma once

#include "MinDefines.hpp"
#include "Singleton.hpp"

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(HWND) MinGetForegroundWindow();

    EXPORT_FUNC_EX(POINT) MinGetWindowPos(HWND windowHandle);

    EXPORT_FUNC_EX(bool) MinSetWindowPos(HWND windowHandle, POINT pos);

    EXPORT_FUNC_EX(POINT) MinGetWindowSize(HWND windowHandle);

    EXPORT_FUNC_EX(bool) MinSetWindowSize(HWND windowHandle, POINT size);

    EXPORT_FUNC_EX(POINT) MinGetDesktopSize();

    EXPORT_FUNC_EX(POINT) MinGetClientSize(HWND windowHandle);

    EXPORT_FUNC_EX(POINT) MinGetMousePos();

    EXPORT_FUNC_EX(POINT) MinGetMappedMousePos(HWND windowHandle);

    EXPORT_FUNC_EX(bool) MinGetMouseInClient(HWND windowHandle);

    EXPORT_FUNC_EX(bool) MinGetWindowInFocus(HWND windowHandle);

    EXPORT_FUNC_EX(POINT) MinGetCenterPosOfWindowInDesktop(HWND windowHandle);

    EXPORT_FUNC_EX(POINT) MinGetCenterPosOfWindow(HWND windowHandle);

    //ex:

    EXPORT_FUNC_EX(bool) MinSetWindowMenuVisibility(HWND windowHandle, bool visible);

    //If the window has been maximized and parameter maximize is false, the window size will be restored
    EXPORT_FUNC_EX(bool) MinMaximizeWindow(HWND windowHandle, bool maximize);

    EXPORT_FUNC_EX(byte) MinGetWindowAlpha(HWND windowHandle);

    EXPORT_FUNC_EX(bool) MinSetWindowAlpha(HWND windowHandle, byte alpha);

    //Determines whether the specified window is minimized (iconic).
    EXPORT_FUNC_EX(bool) MinIsMinimized(HWND windowHandle);

    EXPORT_FUNC_EX(HINSTANCE) MinGetExeInstance();

    EXPORT_FUNC_EX(bool) MinDeleteMenu(HWND windowHandle, bool allowResizing, bool allowClose, bool allowMaximize, bool allowMinimize);

    //This API don't work in Windows Console.
    EXPORT_FUNC_EX(bool) MinDisableCursor();

    class Window
    {
    public:
        static Singleton<Window> Global;

        static HWND GetForegroundWindow();

        static POINT GetDesktopSize();

        static POINT GetMousePos();

        static HINSTANCE GetExeInstance();

        //This API don't work in Console.
        static bool DisableCursor();

    public:
        HWND windowHandle;

        Window();

        Window(HWND windowHandle);

        POINT GetWindowPos();

        void SetWindowPos(POINT pos);

        POINT GetWindowSize();

        void SetWindowSize(POINT size);

        POINT GetClientSize();

        POINT GetMappedMousePos();

        bool GetMouseInClient();

        bool GetWindowInFocus();

        POINT GetCenterPosOfWindowInDesktop();

        POINT GetCenterPosOfWindow();

        //ex:

        void SetWindowMenuVisibility(bool visible);

        //If the window has been maximized and parameter maximize is false, the window size will be restored
        void MaximizeWindow(bool maximize);

        byte GetWindowAlpha();

        void SetWindowAlpha(byte alpha);

        //Determines whether the specified window is minimized (iconic).
        bool IsMinimized();

        bool DeleteMenu(bool allowResizing, bool allowClose, bool allowMaximize, bool allowMinimize);
    };

    extern Window& window;
}