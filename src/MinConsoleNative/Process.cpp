#include "Process.h"
#include <shellapi.h>

namespace MinConsoleNative
{
    HINSTANCE Process::Execute(const std::wstring& file, const std::wstring& param, const std::wstring& directory)
    {
        return ::ShellExecute(nullptr, _T("open"), file.c_str(), param.c_str(), directory.c_str(), SW_SHOW);
    }
}