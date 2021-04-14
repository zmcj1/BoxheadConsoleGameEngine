#include "VTConverter.h"
#include <sstream>
#include <cstdio>

using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC MinVTResetStyle(wchar* str, int strLen)
    {
        //ESC [ <n> m
        //<n> : 0
        int r = swprintf_s(str, strLen, L"%ls[0m", _T(ESC));
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTForeColor(wchar* str, int strLen, Color24 foreColor)
    {
        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTBackColor(wchar* str, int strLen, Color24 backColor)
    {
        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[48;2;%d;%d;%dm", _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTColor(wchar* str, int strLen, Color24 foreColor, Color24 backColor)
    {
        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm%ls[48;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b, _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTUnderline(wchar* str, int strLen, bool underLine)
    {
        //ESC [ <n> m
        //<n> : 4	    Underline
        //<n> : 24      No underline
        int r = 0;
        if (underLine)
        {
            r = swprintf_s(str, strLen, L"%ls[4m", _T(ESC));
        }
        else
        {
            r = swprintf_s(str, strLen, L"%ls[24m", _T(ESC));
        }

        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTWindowTitle(wchar* str, int strLen, const wchar* title)
    {
        //ESC ] 2 ; <string> BEL
        int r = swprintf_s(str, strLen, L"%ls]2;%ls%ls", _T(ESC), title, _T(BELL));
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTCursorPos(wchar* str, int strLen, COORD pos)
    {
        //ESC [ <y> ; <x> H
        int r = swprintf_s(str, strLen, L"%ls[%d;%dH", _T(ESC), pos.Y + 1, pos.X + 1);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTCursorVisible(wchar* str, int strLen, bool visible)
    {
        //ESC [ ? 25 h  Show the cursor
        //ESC [ ? 25 l  Hide the cursor
        int r = 0;
        if (visible)
        {
            r = swprintf_s(str, strLen, L"%ls[?25h", _T(ESC));
        }
        else
        {
            r = swprintf_s(str, strLen, L"%ls[?25l", _T(ESC));
        }

        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    //foreColor(30 - 37 90 - 97) backColor(40 - 47 100 - 107)
    EXPORT_FUNC MinVTTerminalColor(wchar* str, int strLen, int color)
    {
        //ESC [ <n> m
        int r = swprintf_s(str, strLen, L"%ls[%dm", _T(ESC), color);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTTerminalForeColor(wchar* str, int strLen, TerminalColor tcolor)
    {
        //Console color => VT100 color
        int fcolor = (int)tcolor;
        if (fcolor < 8)
        {
            fcolor += 30;
        }
        else
        {
            fcolor += 82;
        }
        return MinVTTerminalColor(str, strLen, fcolor);
    }

    EXPORT_FUNC MinVTTerminalBackColor(wchar* str, int strLen, TerminalColor tcolor)
    {
        //Console color => VT100 color
        int bcolor = (int)tcolor;
        if (bcolor < 8)
        {
            bcolor += 40;
        }
        else
        {
            bcolor += 92;
        }
        return MinVTTerminalColor(str, strLen, bcolor);
    }

    EXPORT_FUNC MinVTTerminalSize(wchar* str, int strLen, COORD size)
    {
        //?
        int r = swprintf_s(str, strLen, L"%ls[8;%d;%dt", _T(ESC), size.Y, size.X);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTPaletteColor(wchar* str, int strLen, int index, byte r, byte g, byte b)
    {
        //ESC ] 4 ; <i> ; rgb : <r> / <g> / <b> ESC
        //NOTICE : <r> / <g> / <b> here are hexes, so we need to convert them from int to hex str.
        wstringstream rr;
        rr << std::hex << r;
        wstringstream gg;
        gg << std::hex << g;
        wstringstream bb;
        bb << std::hex << b;

        int result = swprintf_s(str, strLen, L"%ls]4;%d;rgb:%ls/%ls/%ls%ls", _T(ESC), index,
            rr.str().c_str(), gg.str().c_str(), bb.str().c_str(), _T(ESC));
        if (result == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTSupport(bool* yes)
    {
        //Set _ENABLE_VIRTUAL_TERMINAL_PROCESSING true
        ConsoleMode cm = Console::Global.GetInstance().GetConsoleMode();
        cm.outputMode._ENABLE_VIRTUAL_TERMINAL_PROCESSING = true;
        Console::Global.GetInstance().SetConsoleMode(cm);
        //Check if _ENABLE_VIRTUAL_TERMINAL_PROCESSING is true
        cm = Console::Global.GetInstance().GetConsoleMode();
        *yes = cm.outputMode._ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        return true;
    }

    EXPORT_FUNC_EX(void) MinVTEnableMouseInput()
    {
        ConsoleMode consoleMode = Console::Global.GetInstance().GetConsoleMode();
        //enable this, this is very important!
        consoleMode.inputMode._ENABLE_VIRTUAL_TERMINAL_INPUT = true;
        Console::Global.GetInstance().SetConsoleMode(consoleMode);
        Console::Global.GetInstance().Write(VT_ENABLE_MOUSE_INPUT);
    }

    EXPORT_FUNC_EX(void) MinVTDisableMouseInput()
    {
        Console::Global.GetInstance().Write(VT_DISABLE_MOUSE_INPUT);
    }

    std::wstring VTConverter::ResetStyle()
    {
        wchar buf[VT_STR_LEN];
        MinVTResetStyle(buf, VT_STR_LEN);
        return std::wstring(buf);
    }

    std::wstring VTConverter::ForeColor(Color24 foreColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTForeColor(buf, VT_STR_LEN, foreColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::BackColor(Color24 backColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTBackColor(buf, VT_STR_LEN, backColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::Color(Color24 foreColor, Color24 backColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTColor(buf, VT_STR_LEN, foreColor, backColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::Underline(bool underLine)
    {
        wchar buf[VT_STR_LEN];
        MinVTUnderline(buf, VT_STR_LEN, underLine);
        return std::wstring(buf);
    }

    std::wstring VTConverter::WindowTitle(std::wstring title)
    {
        wchar buf[VT_STR_LEN];
        MinVTWindowTitle(buf, VT_STR_LEN, title.c_str());
        return std::wstring(buf);
    }

    std::wstring VTConverter::CursorPos(COORD pos)
    {
        wchar buf[VT_STR_LEN];
        MinVTCursorPos(buf, VT_STR_LEN, pos);
        return std::wstring(buf);
    }

    std::wstring VTConverter::CursorVisible(bool visible)
    {
        wchar buf[VT_STR_LEN];
        MinVTCursorVisible(buf, VT_STR_LEN, visible);
        return std::wstring(buf);
    }

    std::wstring VTConverter::TerminalColor(int color)
    {
        wchar buf[VT_STR_LEN];
        MinVTTerminalColor(buf, VT_STR_LEN, color);
        return std::wstring(buf);
    }

    std::wstring VTConverter::TerminalForeColor(MinConsoleNative::TerminalColor tcolor)
    {
        wchar buf[VT_STR_LEN];
        MinVTTerminalForeColor(buf, VT_STR_LEN, tcolor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::TerminalBackColor(MinConsoleNative::TerminalColor tcolor)
    {
        wchar buf[VT_STR_LEN];
        MinVTTerminalBackColor(buf, VT_STR_LEN, tcolor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::TerminalSize(COORD size)
    {
        wchar buf[VT_STR_LEN];
        MinVTTerminalSize(buf, VT_STR_LEN, size);
        return std::wstring(buf);
    }

    std::wstring VTConverter::PaletteColor(int index, byte r, byte g, byte b)
    {
        wchar buf[VT_STR_LEN];
        MinVTPaletteColor(buf, VT_STR_LEN, index, r, g, b);
        return std::wstring(buf);
    }

    bool VTConverter::VTSupport()
    {
        bool yes = false;
        MinVTSupport(&yes);
        return yes;
    }

    void VTConverter::VTEnableMouseInput()
    {
        MinVTEnableMouseInput();
    }

    void VTConverter::VTDisableMouseInput()
    {
        MinVTDisableMouseInput();
    }
}