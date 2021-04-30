#include "Debug.h"
#include "File.h"
#include "String.h"
#include "Console.h"
#include <ctime>
using namespace std;

namespace MinConsoleNative
{
    void Debug::Output(const std::wstring& msg)
    {
        ::OutputDebugString(msg.c_str());
    }

    void Debug::OutputLine(const std::wstring& msg)
    {
        ::OutputDebugString((msg + L"\n").c_str());
    }

    void Debug::Log(const std::wstring& path, const std::wstring& msg, MessageType msgType)
    {
        FileMode logFileMode = File::Status(path);
        if (logFileMode != FileMode::File)
        {
            bool suc = File::Creat(path, FileMode::File);
            if (!suc)
            {
                OutputLine(L"Create file failed!" + path);
                return;
            }
            OutputLine(L"Create file success:" + path);
        }

        wstring line;

        time_t now = time(0);
        char* str = ctime(&now); //Shit! This str with '\n'.
        wstring time_wstr = String::StringToWstring(str);
        time_wstr = time_wstr.substr(0, time_wstr.size() - 1); //remove '\n' in the end.

        auto lines = File::ReadAllLines(path);
        //If the file is empty.
        if (lines.size() == 0 || (lines.size() == 1 && lines[0].empty()))
        {
            //nothing here
        }
        else
        {
            line += L"\n";
        }

        line += L"\"" + msg + L"\"";

        switch (msgType)
        {
        case MessageType::Message:
            line += L" -message ";
            break;
        case MessageType::Warning:
            line += L" -warning ";
            break;
        case MessageType::Error:
            line += L" -error ";
            break;
        }

        line += L"-";
        line += time_wstr;

        File::WriteAllText(path, line, WriteMode::Append);
    }

    void Debug::LogToConsole(const std::wstring& msg, MessageType msgType)
    {
        HWND consoleWindow = ::GetConsoleWindow();
        HANDLE consoleInput = ::GetStdHandle(STD_INPUT_HANDLE);
        HANDLE consoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);

        HANDLE newConsoleOutput = Console::CreateConsoleScreenBuffer();
        Console::SetConsoleActiveScreenBuffer(newConsoleOutput);

        Console console(consoleWindow, consoleInput, newConsoleOutput);

        ConsoleColor foreColor = ConsoleColor::GRAY;
        switch (msgType)
        {
        case MessageType::Message:
            foreColor = ConsoleColor::WHITE;
            break;
        case MessageType::Warning:
            foreColor = ConsoleColor::YELLOW;
            break;
        case MessageType::Error:
            foreColor = ConsoleColor::RED;
            break;
        }

        console.WriteLine(msg, foreColor);
        console.ReadLine();
        console.Clear();

        Console::SetConsoleActiveScreenBuffer(consoleOutput);
        Console::CloseConsoleScreenBuffer(newConsoleOutput);
    }

    std::wstring Debug::FormatLastErrorMsg()
    {
        //copy from olcConsoleGameEngine.h
        wchar buf[MAX_PATH] = { 0 };
        ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ::GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, LEN(buf), NULL);
        return std::wstring(buf);
    }

    int Debug::LastMinError = 0;
    std::wstring Debug::LastMinErrorMsg = L"";

    int Debug::GetLastMinError()
    {
        return LastMinError;
    }

    void Debug::SetLastMinError(int code)
    {
        LastMinError = code;
    }

    std::wstring Debug::GetLastMinErrorMsg()
    {
        return LastMinErrorMsg;
    }

    void Debug::SetLastMinErrorMsg(std::wstring msg)
    {
        LastMinErrorMsg = msg;
    }
}