#include "Window.h"

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(HWND) MinGetForegroundWindow()
    {
        return ::GetForegroundWindow();
    }

    EXPORT_FUNC_EX(HWND) MinGetConsoleWindow()
    {
        return ::GetConsoleWindow();
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

    EXPORT_FUNC_EX(bool) MinIsMinimized(HWND windowHandle)
    {
        return IsIconic(windowHandle);
    }

    EXPORT_FUNC_EX(HINSTANCE) MinGetExeInstance()
    {
        return ::GetModuleHandle(nullptr);
    }

    EXPORT_FUNC_EX(bool) MinDeleteMenu(HWND windowHandle, bool allowResizing, bool allowClose, bool allowMaximize, bool allowMinimize)
    {
        HMENU menu = ::GetSystemMenu(windowHandle, false);
        if (!allowResizing)
        {
            ::DeleteMenu(menu, SC_SIZE, MF_BYCOMMAND);
        }
        if (!allowClose)
        {
            ::DeleteMenu(menu, SC_CLOSE, MF_BYCOMMAND);
        }
        if (!allowMaximize)
        {
            ::DeleteMenu(menu, SC_MAXIMIZE, MF_BYCOMMAND);
        }
        if (!allowMinimize)
        {
            ::DeleteMenu(menu, SC_MINIMIZE, MF_BYCOMMAND);
        }
        return true;
    }

    Window::Window()
    {
        this->windowHandle = ::GetForegroundWindow();
    }

    Window::Window(HWND windowHandle)
    {
        this->windowHandle = windowHandle;
    }

    HWND Window::GetForegroundWindow()
    {
        return MinGetForegroundWindow();
    }

    HWND Window::GetConsoleWindow()
    {
        return MinGetConsoleWindow();
    }

    POINT Window::GetWindowPos()
    {
        POINT pos;
        MinGetWindowPos(this->windowHandle, &pos);
        return pos;
    }

    void Window::SetWindowPos(POINT pos)
    {
        MinSetWindowPos(this->windowHandle, pos);
    }

    POINT Window::GetWindowSize()
    {
        POINT size;
        MinGetWindowSize(this->windowHandle, &size);
        return size;
    }

    void Window::SetWindowSize(POINT size)
    {
        MinSetWindowSize(this->windowHandle, size);
    }

    POINT Window::GetDesktopSize()
    {
        POINT size;
        MinGetDesktopSize(&size);
        return size;
    }

    POINT Window::GetClientSize()
    {
        POINT size;
        MinGetClientSize(this->windowHandle, &size);
        return size;
    }

    POINT Window::GetMousePos()
    {
        POINT pos;
        MinGetMousePos(&pos);
        return pos;
    }

    POINT Window::GetMappedMousePos()
    {
        POINT pos;
        MinGetMappedMousePos(this->windowHandle, &pos);
        return pos;
    }

    bool Window::GetMouseInClient()
    {
        bool yes;
        MinGetMouseInClient(this->windowHandle, &yes);
        return yes;
    }

    bool Window::GetWindowInFocus()
    {
        bool yes;
        MinGetWindowInFocus(this->windowHandle, &yes);
        return yes;
    }

    POINT Window::GetCenterPosOfWindowInDesktop()
    {
        POINT pos;
        MinGetCenterPosOfWindowInDesktop(this->windowHandle, &pos);
        return pos;
    }

    POINT Window::GetCenterPosOfWindow()
    {
        POINT pos;
        MinGetCenterPosOfWindow(this->windowHandle, &pos);
        return pos;
    }

    void Window::SetWindowMenuVisibility(bool visible)
    {
        MinSetWindowMenuVisibility(this->windowHandle, visible);
    }

    void Window::MaximizeWindow(bool maximize)
    {
        MinMaximizeWindow(this->windowHandle, maximize);
    }

    byte Window::GetWindowAlpha()
    {
        byte alpha;
        MinGetWindowAlpha(this->windowHandle, &alpha);
        return alpha;
    }

    void Window::SetWindowAlpha(byte alpha)
    {
        MinSetWindowAlpha(this->windowHandle, alpha);
    }

    bool Window::IsMinimized()
    {
        return MinIsMinimized(this->windowHandle);
    }

    HINSTANCE Window::GetExeInstance()
    {
        return MinGetExeInstance();
    }

    bool Window::DeleteMenu(bool allowResizing, bool allowClose, bool allowMaximize, bool allowMinimize)
    {
        return MinDeleteMenu(this->windowHandle, allowResizing, allowClose, allowMaximize, allowMinimize);
    }

    Window& window = Window::Global.GetInstance();
}