#pragma once

#include "MinDefines.h"

//In order to prevent naming conflicts with Microsoft, all export methods in this file are prefixed with Min
namespace MinConsoleNative
{
    EXPORT_FUNC MinGetForegroundWindow(HWND* windowHandle);

    EXPORT_FUNC MinGetConsoleWindow(HWND* windowHandle);

    EXPORT_FUNC MinGetWindowPos(HWND windowHandle, POINT* pos);

    EXPORT_FUNC MinSetWindowPos(HWND windowHandle, POINT pos);

    EXPORT_FUNC MinGetWindowSize(HWND windowHandle, POINT* size);

    EXPORT_FUNC MinSetWindowSize(HWND windowHandle, POINT size);

    EXPORT_FUNC MinGetDesktopSize(POINT* size);

    EXPORT_FUNC MinGetClientSize(HWND windowHandle, POINT* size);

    EXPORT_FUNC MinGetMousePos(POINT* pos);

    EXPORT_FUNC MinGetMappedMousePos(HWND windowHandle, POINT* pos);

    EXPORT_FUNC MinGetMouseInClient(HWND windowHandle, bool* yes);

    EXPORT_FUNC MinGetWindowInFocus(HWND windowHandle, bool* yes);

    EXPORT_FUNC MinGetCenterPosOfWindowInDesktop(HWND windowHandle, POINT* pos);

    EXPORT_FUNC MinGetCenterPosOfWindow(HWND windowHandle, POINT* pos);

    //ex:

    EXPORT_FUNC MinSetWindowMenuVisibility(HWND windowHandle, bool visible);

    //If the window has been maximized and parameter maximize is false, the window size will be restored
    EXPORT_FUNC MinMaximizeWindow(HWND windowHandle, bool maximize);

    EXPORT_FUNC MinGetWindowAlpha(HWND windowHandle, byte* alpha);

    EXPORT_FUNC MinSetWindowAlpha(HWND windowHandle, byte alpha);
}