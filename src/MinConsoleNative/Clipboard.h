#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    EXPORT_FUNC ReadFromClipboard(wchar** data);

    EXPORT_FUNC FreeClipboardData(wchar* data);

    EXPORT_FUNC WriteToClipboard(const wchar* data, int charCount);

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