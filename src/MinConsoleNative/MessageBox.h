﻿#pragma once

#include "MinDefines.h"
#include <string>

//SEE:https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox

namespace MinConsoleNative
{
    enum class MessageBoxButtons
    {
        OK = 1,
        OKCANCEL,
        YESNO,
        YESNOCANCEL,
    };

    enum class MessageBoxDefaultButton
    {
        First = 1,
        Second,
        Third,
    };

    enum class MessageBoxIcon
    {
        Warning = 1,
        Information,
        Error,
    };

    enum class MessageBoxResult
    {
        OK = 1,
        YES,
        NO,
        CANCEL,
    };

    EXPORT_FUNC_EX(MessageBoxResult) MinShowMessageBox(const wchar* text, const wchar* title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType);

    class WMessageBox
    {
    public:
        static MessageBoxResult Show(const std::wstring& text, const std::wstring& title, MessageBoxButtons buttons, MessageBoxDefaultButton defButton, MessageBoxIcon iconType);
    };
}