#include "Process.h"
#include <shellapi.h>

namespace MinConsoleNative
{
    HINSTANCE Process::Execute(const std::wstring& file, const std::wstring& param)
    {
        return ::ShellExecute(nullptr, _T("open"), file.c_str(), param.c_str(), nullptr, SW_SHOW);
    }
}