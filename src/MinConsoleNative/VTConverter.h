#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <string>

//Support Virtual Terminal Sequences

//ANSI Escape Sequence(Virtual Terminal Sequences) API here

//See:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#output-sequences

#ifndef ESC
#define ESC "\033"   //00011011 = 033 = 27 = 0x1B
#endif

#ifndef CSI
#define CSI "\033["
#endif

#ifndef BELL
#define BELL "\x07"
#endif

namespace MinConsoleNative
{
    constexpr int VT_STR_LEN = 64;

    enum class TerminalColor
    {
        Black = 0,
        DarkBlue = 4,
        DarkGreen = 2,
        DarkCyan = 6,
        DarkRed = 1,
        DarkMagenta = 5,
        DarkYellow = 3,
        Gray = 7,
        DarkGray = 8,
        Blue = 12,
        Green = 10,
        Cyan = 14,
        Red = 9,
        Magenta = 13,
        Yellow = 11,
        White = 15,
    };

    EXPORT_FUNC MinVTResetStyle(wchar* str, int strLen);

    EXPORT_FUNC MinVTForeColor(wchar* str, int strLen, Color24 foreColor);

    EXPORT_FUNC MinVTBackColor(wchar* str, int strLen, Color24 backColor);

    EXPORT_FUNC MinVTColor(wchar* str, int strLen, Color24 foreColor, Color24 backColor);

    EXPORT_FUNC MinVTUnderline(wchar* str, int strLen, bool underLine);

    EXPORT_FUNC MinVTWindowTitle(wchar* str, int strLen, const wchar* title);

    EXPORT_FUNC MinVTCursorPos(wchar* str, int strLen, COORD pos);

    EXPORT_FUNC MinVTCursorVisible(wchar* str, int strLen, bool visible);

    class VTConverter
    {
    private:
        VTConverter()
        {
        }

    public:
        static std::wstring ResetStyle();

        static std::wstring ForeColor(Color24 foreColor);

        static std::wstring BackColor(Color24 backColor);

        static std::wstring Color(Color24 foreColor, Color24 backColor);

        static std::wstring Underline(bool underLine);

        static std::wstring WindowTitle(std::wstring title);

        static std::wstring CursorPos(COORD pos);

        static std::wstring CursorVisible(bool visible);
    };
}