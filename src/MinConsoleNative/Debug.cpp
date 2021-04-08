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
}