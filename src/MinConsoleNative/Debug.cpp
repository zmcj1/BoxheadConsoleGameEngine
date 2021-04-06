#include "Debug.h"
#include "File.h"
#include "String.h"
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
            OutputLine(L"Create file:" + path);
            File::Creat(path, FileMode::File);
        }

        wstring line;

        time_t now = time(0);
        char* str = ctime(&now); //Shit! This str with '\n'.
        wstring time_wstr = String::StringToWstring(str);

        switch (msgType)
        {
        case MessageType::Message:
            line = _T("\"") + msg + _T("\" -message ") + _T("----") + time_wstr;
            break;
        case MessageType::Warning:
            line = _T("\"") + msg + _T("\" -warning ") + _T("----") + time_wstr;
            break;
        case MessageType::Error:
            line = _T("\"") + msg + _T("\" -error ") + _T("----") + time_wstr;
            break;
        }

        File::WriteAllText(path, line, WriteMode::Append);
    }
}