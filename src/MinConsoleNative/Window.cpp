#include "Window.h"

namespace MinConsoleNative
{
    EXPORT_FUNC MinGetForegroundWindow(HWND* windowHandle)
    {
        *windowHandle = ::GetForegroundWindow();
        return true;
    }

    EXPORT_FUNC MinGetConsoleWindow(HWND* windowHandle)
    {
        *windowHandle = ::GetConsoleWindow();
        return true;
    }

    EXPORT_FUNC MinGetWindowPos(HWND windowHandle, POINT* pos)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        pos->x = rect.left;
        pos->y = rect.top;
        return true;
    }

    EXPORT_FUNC MinSetWindowPos(HWND windowHandle, POINT pos)
    {
        return ::SetWindowPos(windowHandle, HWND_NOTOPMOST, pos.x, pos.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
    }

    EXPORT_FUNC MinGetWindowSize(HWND windowHandle, POINT* size)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        size->x = rect.right - rect.left;
        size->y = rect.bottom - rect.top;
        return true;
    }

    EXPORT_FUNC MinSetWindowSize(HWND windowHandle, POINT size)
    {
        return ::SetWindowPos(windowHandle, HWND_NOTOPMOST, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_SHOWWINDOW);
    }

    EXPORT_FUNC MinGetDesktopSize(POINT* size)
    {
        HWND hDesktopWindow = ::GetDesktopWindow();
        RECT rect;
        ::GetWindowRect(hDesktopWindow, &rect);
        size->x = rect.right;
        size->y = rect.bottom;
        return true;
    }

    EXPORT_FUNC MinGetClientSize(HWND windowHandle, POINT* size)
    {
        RECT rect;
        ::GetClientRect(windowHandle, &rect);
        size->x = rect.right - rect.left;
        size->y = rect.bottom - rect.top;
        return true;
    }

    EXPORT_FUNC MinGetMousePos(POINT* pos)
    {
        return ::GetCursorPos(pos);
    }

    EXPORT_FUNC MinGetMappedMousePos(HWND windowHandle, POINT* pos)
    {
        ::GetCursorPos(pos);
        return ::ScreenToClient(windowHandle, pos);
    }

    EXPORT_FUNC MinGetMouseInClient(HWND windowHandle, bool* yes)
    {
        POINT mappedPos;
        MinGetMappedMousePos(windowHandle, &mappedPos);

        POINT clientSize;
        MinGetClientSize(windowHandle, &clientSize);

        if (mappedPos.x >= 0 && mappedPos.x < clientSize.x &&
            mappedPos.y >= 0 && mappedPos.y < clientSize.y)
        {
            *yes = true;
        }
        else
        {
            *yes = false;
        }
        return true;
    }

    EXPORT_FUNC MinGetWindowInFocus(HWND windowHandle, bool* yes)
    {
        if (windowHandle == nullptr) return false;

        HWND hForeground = ::GetForegroundWindow();
        if (hForeground == nullptr) return false;

        *yes = hForeground == windowHandle;
        return true;
    }

    EXPORT_FUNC MinGetCenterPosOfWindowInDesktop(HWND windowHandle, POINT* pos)
    {
        LONG desktopWidth = 0, desktopHeight = 0, windowWidth = 0, windowHeight = 0;

        POINT desktopSize;
        MinGetDesktopSize(&desktopSize);
        POINT windowSize;
        MinGetWindowSize(windowHandle, &windowSize);

        desktopWidth = desktopSize.x;
        desktopHeight = desktopSize.y;
        windowWidth = windowSize.x;
        windowHeight = windowSize.y;

        pos->x = (desktopWidth / 2) - (windowWidth / 2);
        pos->y = (desktopHeight / 2) - (windowHeight / 2);
        return true;
    }

    EXPORT_FUNC MinGetCenterPosOfWindow(HWND windowHandle, POINT* pos)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        pos->x = rect.left + (rect.right - rect.left) / 2;
        pos->y = rect.top + (rect.bottom - rect.top) / 2;
        return true;
    }

    EXPORT_FUNC MinSetWindowMenuVisibility(HWND windowHandle, bool visible)
    {
        LONG value = 0;
        if (visible)
        {
            value = WS_CAPTION;
        }
        else
        {
            value = WS_SYSMENU;
        }
        ::SetWindowLongPtr(windowHandle, GWL_STYLE, value);

        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        ::SetWindowPos(windowHandle, HWND_NOTOPMOST, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
        return true;
    }

    EXPORT_FUNC MinMaximizeWindow(HWND windowHandle, bool maximize)
    {
        int cmd = 0;
        if (maximize)
        {
            cmd = SW_MAXIMIZE;
        }
        else
        {
            cmd = SW_RESTORE;
        }
        return ::ShowWindow(windowHandle, cmd);
    }

    EXPORT_FUNC MinGetWindowAlpha(HWND windowHandle, byte* alpha)
    {
        COLORREF color = 0;
        DWORD flag = 0;
        return ::GetLayeredWindowAttributes(windowHandle, &color, alpha, &flag);
    }

    EXPORT_FUNC MinSetWindowAlpha(HWND windowHandle, byte alpha)
    {
        LONG_PTR style = ::GetWindowLongPtr(windowHandle, GWL_EXSTYLE);
        ::SetWindowLongPtr(windowHandle, GWL_EXSTYLE, style | WS_EX_LAYERED);
        return ::SetLayeredWindowAttributes(windowHandle, 0, alpha, LWA_ALPHA);
    }
}