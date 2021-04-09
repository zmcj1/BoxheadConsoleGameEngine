#pragma once

#include "MinDefines.h"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/dataxchg/clipboard

namespace MinConsoleNative
{
    EXPORT_FUNC MinReadFromClipboard(_OUT_ wchar** data);

    EXPORT_FUNC MinFreeClipboardData(_IN_ wchar* data);

    EXPORT_FUNC MinWriteToClipboard(_IN_ const wchar* data, _IN_ int charCount);

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