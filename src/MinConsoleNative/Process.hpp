#pragma once

#include "MinDefines.hpp"
#include <string>

namespace MinConsoleNative
{
    class Process
    {
    private:
        Process()
        {
        }

    public:
        //Parameters : chrome.exe https://www.youtube.com/
        static HINSTANCE Execute(const std::wstring& file, const std::wstring& param = L"", const std::wstring& directory = L"");
    };
}