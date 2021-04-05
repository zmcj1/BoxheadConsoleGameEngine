#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    EXPORT_FUNC MinReadFromClipboard(wchar** data);

    EXPORT_FUNC MinFreeClipboardData(wchar* data);

    EXPORT_FUNC MinWriteToClipboard(const wchar* data, int charCount);

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