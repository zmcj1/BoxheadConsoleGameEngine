#include "UnusualMethods.h"

namespace MinConsoleNative
{
    bool UnusualMethods::GetFuncFromDll(const wchar* dllName, const char* funcName, FARPROC* funcPtr)
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

    bool UnusualMethods::SetConsoleIcon(HICON hIcon)
    {
        FARPROC func;
        bool suc = GetFuncFromDll(UnusualMethods::Kernel32DLL, "SetConsoleIcon", &func);
        if (!suc) return false;

        typedef BOOL(_stdcall* SetConsoleIconFunc)(HICON);
        return ((SetConsoleIconFunc)func)(hIcon);
    }
}