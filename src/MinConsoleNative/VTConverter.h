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

    EXPORT_FUNC MinVTTerminalColor(wchar* str, int strLen, int color);

    EXPORT_FUNC MinVTTerminalForeColor(wchar* str, int strLen, TerminalColor tcolor);

    EXPORT_FUNC MinVTTerminalBackColor(wchar* str, int strLen, TerminalColor tcolor);

    EXPORT_FUNC MinVTTerminalSize(wchar* str, int strLen, COORD size);

    //IMPORTANT:This API failed the test in the Windows Console
    EXPORT_FUNC MinVTPaletteColor(wchar* str, int strLen, int index, byte r, byte g, byte b);

    EXPORT_FUNC MinVTSupport(bool* yes);

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

        static std::wstring TerminalColor(int color);

        static std::wstring TerminalForeColor(MinConsoleNative::TerminalColor tcolor);

        static std::wstring TerminalBackColor(MinConsoleNative::TerminalColor tcolor);

        static std::wstring TerminalSize(COORD size);

        static std::wstring PaletteColor(int index, byte r, byte g, byte b);

        static bool VTSupport();
    };
}