#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    extern const wchar* Kernel32Dll;

    bool GetFuncFromDll(const wchar* dllName, const char* funcName, FARPROC* funcPtr);

    bool SetConsoleIcon(HICON hIcon);
}