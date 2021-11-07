#pragma once

#include "MinDefines.h"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/dataxchg/clipboard

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinReadFromClipboard(_OUT_ wchar** data);

    EXPORT_FUNC_EX(bool) MinWriteToClipboard(_IN_ const wchar* data, int charCount);

    class Clipboard
    {
    private:
        Clipboard()
        {
        }

    public:
        static std::wstring Read();

        static bool Write(const std::wstring& data);
    };
}