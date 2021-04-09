﻿#pragma once

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
        std::map<wchar, CharWidth> charWidthCacheDict;
        std::map<wchar, CharWidth> charWidthUserDefineDict;

        TextLayout(Console console);

        CharWidth GetWcharWidth(wchar c);

        int GetWstringWidth(const std::wstring& str);

        std::vector<std::wstring> WstringToGrids(const std::wstring wstr);

        //width:the width of LineWidth(cell)
        //NOTICE:if width is 1, will return single char as line. width can't < 1!
        std::vector<std::wstring> WstringToLines(const std::wstring wstr, int width, bool fillAll = true);
    };
}