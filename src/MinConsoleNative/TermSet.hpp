#pragma once

#include "MinDefines.hpp"
#include <string>

//Windows Terminal setting.json file:
//https://docs.microsoft.com/en-us/windows/terminal/install#settings-json-file
//C++ - How to get the user folder:
//https://stackoverflow.com/questions/21428407/c-how-to-get-the-user-folder
//Should I free/delete char* returned by getenv():
//https://stackoverflow.com/questions/4237812/should-i-free-delete-char-returned-by-getenv

namespace MinConsoleNative
{
    class TermSet
    {
    public:
        //if fail:return L""
        static std::wstring GetWTSettingFilePath();
    };
}