#include "UnusualMethods.h"

namespace MinConsoleNative
{
    const wchar* Kernel32Dll = L"kernel32.dll";

    EXPORT_FUNC MinGetFuncFromDll(const wchar* dllName, const char* funcName, FARPROC* funcPtr)
    {
        HMODULE hModule = ::LoadLibrary(dllName);
        if (hModule == nullptr) return false;

        FARPROC proc = ::GetProcAddress(hModule, funcName);
        if (proc == nullptr)
        {
            ::FreeLibrary(hModule);
            return false;
        }

        *funcPtr = proc;
        ::FreeLibrary(hModule);

        return true;
    }

    EXPORT_FUNC MinSetConsoleIcon(HICON hIcon)
    {
        FARPROC func;
        bool suc = MinGetFuncFromDll(Kernel32Dll, "SetConsoleIcon", &func);
        if (!suc) return false;

        typedef BOOL(_stdcall* SetConsoleIconFunc)(HICON);
        return ((SetConsoleIconFunc)func)(hIcon);
    }
}