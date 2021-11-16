#pragma once

#include "MinDefines.hpp"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox

namespace MinConsoleNative
{
    EXPORT_ENUM_CLASS MessageBoxButtons
    {
        OK = 1,
        OKCANCEL,
        YESNO,
        YESNOCANCEL,
    };

    EXPORT_ENUM_CLASS MessageBoxDefaultButton
    {
        First = 1,
        Second,
        Third,
    };

    EXPORT_ENUM_CLASS MessageBoxIcon
    {
        Warning = 1,
        Information,
        Error,
    };

    EXPORT_ENUM_CLASS MessageBoxResult
    {
        OK = 1,
        YES,
        NO,
        CANCEL,
    };

    EXPORT_FUNC_EX(MessageBoxResult) MinShowMessageBox(_IN_ const wchar* text, _IN_ const wchar* title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType);

    class WMessageBox
    {
    private:
        WMessageBox()
        {
        }

    public:
        static MessageBoxResult Show(const std::wstring& text, const std::wstring& title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType);
    };
}