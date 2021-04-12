#include "Win32Window.h"

LRESULT __stdcall WindowProcedure(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

Win32Window::Win32Window(HINSTANCE instance)
{
    this->instance = instance;
    this->className = className;

    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra;
    wc.cbWndExtra;
    wc.hInstance = instance;
    wc.hIcon;
    wc.hCursor;
    wc.hbrBackground;
    wc.lpszMenuName;
    wc.lpszClassName = className.c_str();
    wc.hIconSm;

    ATOM rr = RegisterClassEx(&wc);
    if (rr == 0)
    {
        //failed
    }

    HWND windowHandle = CreateWindowEx(
        0, className.c_str(), L"application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, instance, nullptr
    );

    if (windowHandle == nullptr)
    {
        //failed
    }

    ShowWindow(windowHandle, SW_SHOWDEFAULT); //show the window
    UpdateWindow(windowHandle); //sends a WM_PAINT message directly to the window
}

Win32Window::~Win32Window()
{
    UnregisterClass(this->className.c_str(), this->instance);
    //DestroyWindow();
}

void Win32Window::ProcessMessage()
{

}