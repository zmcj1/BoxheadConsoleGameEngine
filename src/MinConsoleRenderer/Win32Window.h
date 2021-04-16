#pragma once

#include <Windows.h>
#include <string>

LRESULT __stdcall WindowProcedure(
    _In_ HWND hWnd,
    _In_ UINT Msg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam);

class Win32Window
{
public:
    HINSTANCE instance;

    Win32Window(HINSTANCE instance);

    ~Win32Window();

    void ProcessMessage();

private:
    std::wstring className = L"using_static";

};