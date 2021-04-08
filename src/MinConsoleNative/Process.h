#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    class Process
    {
    public:
        //Parameters : chrome.exe https://www.youtube.com/
        static HINSTANCE Execute(const std::wstring& file, const std::wstring& param);
    };
}