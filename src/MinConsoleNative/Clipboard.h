#pragma once

#include "MinDefines.h"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/dataxchg/clipboard
//相似的库:https://github.com/Arian8j2/ClipboardXX/blob/master/include/ClipboardXX.hpp
//微软的示例:https://docs.microsoft.com/en-us/windows/win32/dataxchg/using-the-clipboard#copying-information-to-the-clipboard

namespace MinConsoleNative
{
    //如果失败则会返回nullptr
    //参考:https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
    EXPORT_FUNC_EX(wchar*) MinReadFromClipboard();

    //参考:https://docs.microsoft.com/zh-cn/windows/win32/dataxchg/using-the-clipboard?redirectedfrom=MSDN#copying-information-to-the-clipboard
    EXPORT_FUNC_EX(bool) MinWriteToClipboard(_IN_ const wchar* data);

    class Clipboard
    {
    private:
        Clipboard()
        {
        }

    public:
        static std::wstring Read();

        static bool Write(const std::wstring& data);
    };
}