#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    extern const wchar* Kernel32Dll;

    EXPORT_FUNC GetFuncFromDll(const wchar* dllName, const char* funcName, FARPROC* funcPtr);

    EXPORT_FUNC SetConsoleIcon(HICON hIcon);
}