#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <string>
#include <vector>
#include <map>

namespace MinConsoleNative
{
    class TextLayout
    {
    public:
        static std::wstring CombineWchar(wchar a1, wchar a2);

    public:
        Console console;

        TextLayout(Console console);

        std::vector<std::wstring> WstringToGrids(const std::wstring wstr);
    };
}