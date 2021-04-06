#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    enum class MessageType
    {
        Message = 1,
        Warning = 2,
        Error = 3,
    };

    class Debug
    {
    public:
        //Output to IDE
        static void Output(const std::wstring& msg);

        //Output to IDE
        static void OutputLine(const std::wstring& msg);

        //Log to file, if the file is not exsits I will create it.
        static void Log(const std::wstring& path, const std::wstring& msg, MessageType msgType = MessageType::Message);
    };
}