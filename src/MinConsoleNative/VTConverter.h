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

    //注意:从C++返回wchar*到C#:https://stackoverflow.com/questions/393509/usage-of-cotaskmemalloc
    //实例:https://social.msdn.microsoft.com/Forums/vstudio/en-US/ccdc1c5c-8324-4ac8-9273-564205181a66/return-char-arrays-from-c-to-c?forum=clr
    //CoTaskMemAlloc函数:https://docs.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-cotaskmemalloc

    EXPORT_FUNC_EX(wchar*) MinVTResetStyle();

    EXPORT_FUNC_EX(wchar*) MinVTForeColor(Color24 foreColor);

    EXPORT_FUNC_EX(wchar*) MinVTBackColor(Color24 backColor);

    EXPORT_FUNC_EX(wchar*) MinVTColor(Color24 foreColor, Color24 backColor);

    EXPORT_FUNC_EX(wchar*) MinVTUnderline(bool underLine);

    EXPORT_FUNC_EX(wchar*) MinVTWindowTitle(const wchar* title);

    EXPORT_FUNC_EX(wchar*) MinVTCursorPos(COORD pos);

    EXPORT_FUNC_EX(wchar*) MinVTCursorVisible(bool visible);

    EXPORT_FUNC_EX(wchar*) MinVTTerminalColor(int color);

    EXPORT_FUNC_EX(wchar*) MinVTTerminalForeColor(TerminalColor tcolor);

    EXPORT_FUNC_EX(wchar*) MinVTTerminalBackColor(TerminalColor tcolor);

    //WARNING:This function is invalid for Windows Terminal, but works in Windows Console.
    EXPORT_FUNC_EX(wchar*) MinVTTerminalSize(COORD size);

    //WARNING:Not recommended use this function, it's unstable.
    //FROM:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#screen-colors
    EXPORT_FUNC_EX(wchar*) MinVTPaletteColor(int index, byte r, byte g, byte b);

    //Check if the current console supports VT sequence.
    //灵感来源:https://github.com/microsoft/DbgShell/blob/master/DbgShell/ConsoleControl.cs
    //CheckVirtualTerminalSupported
    EXPORT_FUNC_EX(bool) MinVTSupport();

    //These two APIs are specifically designed to be compatible with Windows Terminal.
    EXPORT_FUNC_EX(void) MinVTEnableMouseInput();

    EXPORT_FUNC_EX(void) MinVTDisableMouseInput();

    //This API internally shows how to use the VT sequence.
    EXPORT_FUNC_EX(COORD) MinVTGetCursorPos();

    //有关此API返回值详见:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#query-state
    EXPORT_FUNC_EX(wchar*) MinVTGetDeviceAttributes();

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