#include "Window.hpp"

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(HWND) MinGetForegroundWindow()
    {
        return ::GetForegroundWindow();
    }

    EXPORT_FUNC_EX(POINT) MinGetWindowPos(HWND windowHandle)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        POINT pos;
        pos.x = rect.left;
        pos.y = rect.top;
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinSetWindowPos(HWND windowHandle, POINT pos)
    {
        return ::SetWindowPos(windowHandle, HWND_NOTOPMOST, pos.x, pos.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
    }

    EXPORT_FUNC_EX(POINT) MinGetWindowSize(HWND windowHandle)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        POINT size;
        size.x = rect.right - rect.left;
        size.y = rect.bottom - rect.top;
        return size;
    }

    EXPORT_FUNC_EX(bool) MinSetWindowSize(HWND windowHandle, POINT size)
    {
        return ::SetWindowPos(windowHandle, HWND_NOTOPMOST, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_SHOWWINDOW);
    }

    EXPORT_FUNC_EX(POINT) MinGetDesktopSize()
    {
        HWND hDesktopWindow = ::GetDesktopWindow();
        RECT rect;
        ::GetWindowRect(hDesktopWindow, &rect);
        POINT size;
        size.x = rect.right;
        size.y = rect.bottom;
        return size;
    }

    EXPORT_FUNC_EX(POINT) MinGetClientSize(HWND windowHandle)
    {
        RECT rect;
        ::GetClientRect(windowHandle, &rect);
        POINT size;
        size.x = rect.right - rect.left;
        size.y = rect.bottom - rect.top;
        return size;
    }

    EXPORT_FUNC_EX(POINT) MinGetMousePos()
    {
        POINT pos;
        ::GetCursorPos(&pos);
        return pos;
    }

    EXPORT_FUNC_EX(POINT) MinGetMappedMousePos(HWND windowHandle)
    {
        POINT pos;
        ::GetCursorPos(&pos);
        ::ScreenToClient(windowHandle, &pos);
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinGetMouseInClient(HWND windowHandle)
    {
        POINT mappedPos = MinGetMappedMousePos(windowHandle);
        POINT clientSize = MinGetClientSize(windowHandle);

        if (mappedPos.x >= 0 && mappedPos.x < clientSize.x &&
            mappedPos.y >= 0 && mappedPos.y < clientSize.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    EXPORT_FUNC_EX(bool) MinGetWindowInFocus(HWND windowHandle)
    {
        if (windowHandle == nullptr) return false;

        HWND hForeground = ::GetForegroundWindow();

        if (hForeground == nullptr) return false;

        return hForeground == windowHandle;
    }

    EXPORT_FUNC_EX(POINT) MinGetCenterPosOfWindowInDesktop(HWND windowHandle)
    {
        LONG desktopWidth = 0, desktopHeight = 0, windowWidth = 0, windowHeight = 0;

        POINT desktopSize = MinGetDesktopSize();
        POINT windowSize = MinGetWindowSize(windowHandle);

        desktopWidth = desktopSize.x;
        desktopHeight = desktopSize.y;
        windowWidth = windowSize.x;
        windowHeight = windowSize.y;

        POINT pos;
        pos.x = (desktopWidth / 2) - (windowWidth / 2);
        pos.y = (desktopHeight / 2) - (windowHeight / 2);
        return pos;
    }

    EXPORT_FUNC_EX(POINT) MinGetCenterPosOfWindow(HWND windowHandle)
    {
        RECT rect;
        ::GetWindowRect(windowHandle, &rect);
        POINT pos;
        pos.x = rect.left + (rect.right - rect.left) / 2;
        pos.y = rect.top + (rect.bottom - rect.top) / 2;
        return pos;
    }

    EXPORT_FUNC_EX(bool) MinSetWindowMenuVisibility(HWND windowHandle, bool visible)
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

    EXPORT_FUNC_EX(bool) MinMaximizeWindow(HWND windowHandle, bool maximize)
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

    EXPORT_FUNC_EX(byte) MinGetWindowAlpha(HWND windowHandle)
    {
        COLORREF color = 0;
        byte alpha = 0;
        DWORD flag = 0;

        bool suc = ::GetLayeredWindowAttributes(windowHandle, &color, &alpha, &flag);
        return alpha;
    }

    EXPORT_FUNC_EX(bool) MinSetWindowAlpha(HWND windowHandle, byte alpha)
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

    EXPORT_FUNC_EX(bool) MinDisableCursor()
    {
        while (::ShowCursor(false) >= 0);
        return true;
    }

    EXPORT_FUNC_EX(bool) MinHideWindow(HWND windowHandle, bool hide)
    {
        int cmd;
        if (hide)
        {
            cmd = SW_HIDE;
        }
        else
        {
            cmd = SW_RESTORE;
        }
        return ::ShowWindow(windowHandle, cmd);
    }

    HWND Window::GetForegroundWindow()
    {
        return MinGetForegroundWindow();
    }

    POINT Window::GetDesktopSize()
    {
        return MinGetDesktopSize();
    }

    POINT Window::GetMousePos()
    {
        return MinGetMousePos();
    }

    HINSTANCE Window::GetExeInstance()
    {
        return MinGetExeInstance();
    }

    bool Window::DisableCursor()
    {
        return MinDisableCursor();
    }

    Window::Window()
    {
        this->windowHandle = ::GetForegroundWindow();
    }

    Window::Window(HWND windowHandle)
    {
        this->windowHandle = windowHandle;
    }

    POINT Window::GetWindowPos()
    {
        return MinGetWindowPos(this->windowHandle);
    }

    void Window::SetWindowPos(POINT pos)
    {
        MinSetWindowPos(this->windowHandle, pos);
    }

    POINT Window::GetWindowSize()
    {
        return MinGetWindowSize(this->windowHandle);
    }

    void Window::SetWindowSize(POINT size)
    {
        MinSetWindowSize(this->windowHandle, size);
    }

    POINT Window::GetClientSize()
    {
        return MinGetClientSize(this->windowHandle);
    }

    POINT Window::GetMappedMousePos()
    {
        return MinGetMappedMousePos(this->windowHandle);
    }

    bool Window::GetMouseInClient()
    {
        return MinGetMouseInClient(this->windowHandle);
    }

    bool Window::GetWindowInFocus()
    {
        return MinGetWindowInFocus(this->windowHandle);
    }

    POINT Window::GetCenterPosOfWindowInDesktop()
    {
        return MinGetCenterPosOfWindowInDesktop(this->windowHandle);
    }

    POINT Window::GetCenterPosOfWindow()
    {
        return MinGetCenterPosOfWindow(this->windowHandle);
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
        return MinGetWindowAlpha(this->windowHandle);
    }

    void Window::SetWindowAlpha(byte alpha)
    {
        MinSetWindowAlpha(this->windowHandle, alpha);
    }

    bool Window::IsMinimized()
    {
        return MinIsMinimized(this->windowHandle);
    }

    bool Window::DeleteMenu(bool allowResizing, bool allowClose, bool allowMaximize, bool allowMinimize)
    {
        return MinDeleteMenu(this->windowHandle, allowResizing, allowClose, allowMaximize, allowMinimize);
    }

    bool Window::HideWindow(bool hide)
    {
        return MinHideWindow(this->windowHandle, hide);
    }

    Window& window = Window::Global.GetInstance();
}