#pragma once

#include "MinDefines.hpp"
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
    private:
        Debug()
        {
        }

    public:
        //Output to IDE
        static void Output(const std::wstring& msg);

        //Output to IDE with newline.
        static void OutputLine(const std::wstring& msg);

        //Log to file, if the file is not exsits I will create it.
        static void Log(const std::wstring& path, const std::wstring& msg, MessageType msgType = MessageType::Message);

        //Log to current active console.
        static void LogToConsole(const std::wstring& msg, MessageType msgType = MessageType::Message);

        static std::wstring FormatLastErrorMsg();

    public:
        static int LastMinError;

        static std::wstring LastMinErrorMsg;

        static int GetLastMinError();

        static void SetLastMinError(int code);

        static std::wstring GetLastMinErrorMsg();

        static void SetLastMinErrorMsg(std::wstring msg);
    };
}