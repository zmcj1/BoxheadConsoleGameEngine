#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <string>

//Support Virtual Terminal Sequences

//ANSI Escape Sequence(Virtual Terminal Sequences) API here

//See:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#output-sequences

//See more:https://invisible-island.net/xterm/ctlseqs/ctlseqs.html

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

    //for supporting get mouse position in Windows Terminal.
    constexpr const wchar* VT_ENABLE_MOUSE_INPUT = L"\x1b[?1003;1006h";
    constexpr const wchar* VT_DISABLE_MOUSE_INPUT = L"\x1b[?1003;1006l";

    constexpr const wchar* VT_GET_CURSOR_POS = L"\x1b[6n";
    constexpr const wchar* VT_GET_DEVICE_ATTRIBUTES = L"\x1b[0c";

    EXPORT_ENUM_CLASS TerminalColor
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

    //WARNING:This function is invalid for Windows Terminal, but works in Windows Console.
    EXPORT_FUNC MinVTTerminalSize(wchar* str, int strLen, COORD size);

    //WARNING:Not recommended use this function, it's unstable.
    //FROM:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#screen-colors
    EXPORT_FUNC MinVTPaletteColor(wchar* str, int strLen, int index, byte r, byte g, byte b);

    //Check if the current console supports VT sequence.
    EXPORT_FUNC MinVTSupport(_OUT_ bool* yes);

    //These two APIs are specifically designed to be compatible with Windows Terminal.
    EXPORT_FUNC_EX(void) MinVTEnableMouseInput();

    EXPORT_FUNC_EX(void) MinVTDisableMouseInput();

    //This API internally shows how to use the VT sequence.
    EXPORT_FUNC_EX(COORD) MinVTGetCursorPos();

    EXPORT_FUNC_EX(void) MinVTGetDeviceAttributes(wchar* str, int strLen);

    //Determine whether an input is issued by the VT sequence.
    bool IsVTInput(const INPUT_RECORD* record);

    class VTConverter
    {
    private:
        VTConverter()
        {
        }

    public:
        static std::wstring VTResetStyle();

        static std::wstring VTForeColor(Color24 foreColor);

        static std::wstring VTBackColor(Color24 backColor);

        static std::wstring VTColor(Color24 foreColor, Color24 backColor);

        static std::wstring VTUnderline(bool underLine);

        static std::wstring VTWindowTitle(std::wstring title);

        static std::wstring VTCursorPos(COORD pos);

        static std::wstring VTCursorVisible(bool visible);

        static std::wstring VTTerminalColor(int color);

        static std::wstring VTTerminalForeColor(MinConsoleNative::TerminalColor tcolor);

        static std::wstring VTTerminalBackColor(MinConsoleNative::TerminalColor tcolor);

        static std::wstring VTTerminalSize(COORD size);

        static std::wstring VTPaletteColor(int index, byte r, byte g, byte b);

        static bool VTSupport();

        //These two APIs are specifically designed to be compatible with Windows Terminal.
        static void VTEnableMouseInput();

        static void VTDisableMouseInput();

        //This API internally shows how to use the VT sequence.
        static COORD VTGetCursorPos();

        static std::wstring VTGetDeviceAttributes();
    };
}