#include "Debug.h"

namespace MinConsoleNative
{
    void Debug::Output(const std::wstring& msg)
    {
        OutputDebugString(msg.c_str());
    }

    void Debug::OutputLine(const std::wstring& msg)
    {
        OutputDebugString((msg + L"\n").c_str());
    }
}