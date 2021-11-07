#include "VTConverter.h"
#include "String.h"
#include <sstream>
#include <cstdio>
#include <combaseapi.h> //CoTaskMemAlloc

using namespace std;

namespace MinConsoleNative
{
    bool IsVTInput(const INPUT_RECORD* record)
    {
        return
            record->EventType == KEY_EVENT &&
            record->Event.KeyEvent.bKeyDown &&
            record->Event.KeyEvent.wVirtualKeyCode == 0 &&
            record->Event.KeyEvent.wVirtualScanCode == 0;
    }

    EXPORT_FUNC_EX(wchar*) MinVTResetStyle()
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        //<n> : 0
        int r = ::swprintf_s(str, strLen, L"%ls[0m", _T(ESC));
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTForeColor(Color24 foreColor)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        int r = ::swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTBackColor(Color24 backColor)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = ::swprintf_s(str, strLen, L"%ls[48;2;%d;%d;%dm", _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTColor(Color24 foreColor, Color24 backColor)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = ::swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm%ls[48;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b, _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTUnderline(bool underLine)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        //<n> : 4	    Underline
        //<n> : 24      No underline
        int r = 0;
        if (underLine)
        {
            r = ::swprintf_s(str, strLen, L"%ls[4m", _T(ESC));
        }
        else
        {
            r = ::swprintf_s(str, strLen, L"%ls[24m", _T(ESC));
        }

        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTWindowTitle(_IN_ const wchar* title)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC ] 2 ; <string> BEL
        int r = ::swprintf_s(str, strLen, L"%ls]2;%ls%ls", _T(ESC), title, _T(BELL));
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTCursorPos(COORD pos)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <y> ; <x> H
        int r = ::swprintf_s(str, strLen, L"%ls[%d;%dH", _T(ESC), pos.Y + 1, pos.X + 1);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTCursorVisible(bool visible)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ ? 25 h  Show the cursor
        //ESC [ ? 25 l  Hide the cursor
        int r = 0;
        if (visible)
        {
            r = ::swprintf_s(str, strLen, L"%ls[?25h", _T(ESC));
        }
        else
        {
            r = ::swprintf_s(str, strLen, L"%ls[?25l", _T(ESC));
        }

        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    //foreColor(30 - 37 90 - 97) backColor(40 - 47 100 - 107)
    EXPORT_FUNC_EX(wchar*) MinVTTerminalColor(int color)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC [ <n> m
        int r = ::swprintf_s(str, strLen, L"%ls[%dm", _T(ESC), color);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTTerminalForeColor(TerminalColor tcolor)
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
        return MinVTTerminalColor(fcolor);
    }

    EXPORT_FUNC_EX(wchar*) MinVTTerminalBackColor(TerminalColor tcolor)
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
        return MinVTTerminalColor(bcolor);
    }

    EXPORT_FUNC_EX(wchar*) MinVTTerminalSize(COORD size)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //?
        int r = ::swprintf_s(str, strLen, L"%ls[8;%d;%dt", _T(ESC), size.Y, size.X);
        if (r == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(wchar*) MinVTPaletteColor(int index, byte r, byte g, byte b)
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        //ESC ] 4 ; <i> ; rgb : <r> / <g> / <b> ESC
        //NOTICE : <r> / <g> / <b> here are hexes, so we need to convert them from int to hex str.
        wstringstream rr;
        rr << std::hex << r;
        wstringstream gg;
        gg << std::hex << g;
        wstringstream bb;
        bb << std::hex << b;

        int result = ::swprintf_s(str, strLen, L"%ls]4;%d;rgb:%ls/%ls/%ls%ls", _T(ESC), index,
            rr.str().c_str(), gg.str().c_str(), bb.str().c_str(), _T(ESC));
        if (result == -1)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    EXPORT_FUNC_EX(bool) MinVTSupport()
    {
        //Set _ENABLE_VIRTUAL_TERMINAL_PROCESSING true
        // We only know if vt100 is supported if the previous call actually set the new flag, older systems ignore the setting.
        ConsoleOutputMode com = console.GetConsoleOutputMode();
        com._ENABLE_VIRTUAL_TERMINAL_PROCESSING = true;
        console.SetConsoleOutputMode(com);
        //Check if _ENABLE_VIRTUAL_TERMINAL_PROCESSING is true
        return console.GetConsoleOutputMode()._ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    }

    EXPORT_FUNC_EX(void) MinVTEnableMouseInput()
    {
        ConsoleMode consoleMode = Console::Global.GetInstance().GetConsoleMode();
        //enable this, for use ReadConsoleOutput function.
        consoleMode.inputMode._ENABLE_WINDOW_INPUT = true;
        //enable this
        consoleMode.inputMode._ENABLE_QUICK_EDIT_MODE = true;
        //enable this, this is very important!
        consoleMode.inputMode._ENABLE_VIRTUAL_TERMINAL_INPUT = true;
        Console::Global.GetInstance().SetConsoleMode(consoleMode);
        Console::Global.GetInstance().Write(VT_ENABLE_MOUSE_INPUT);
    }

    EXPORT_FUNC_EX(void) MinVTDisableMouseInput()
    {
        Console::Global.GetInstance().Write(VT_DISABLE_MOUSE_INPUT);
    }

    EXPORT_FUNC_EX(COORD) MinVTGetCursorPos()
    {
        COORD pos;
        Console::Global.GetInstance().Write(VT_GET_CURSOR_POS);

        INPUT_RECORD buffer[32];
        DWORD readCount;
        ReadConsoleInput(Console::Global.GetInstance().cons.consoleInput, buffer, LEN(buffer), &readCount);

        wstring str;
        for (size_t i = 0; i < readCount; i++)
        {
            if (IsVTInput(&buffer[i]))
            {
                str += buffer[i].Event.KeyEvent.uChar.UnicodeChar;
            }
        }
        wstring _str = str.substr(2, str.size() - 3);
        auto xy = String::Split(_str, L";");

        pos.X = stoi(xy[0]) - 1;
        pos.Y = stoi(xy[1]) - 1;
        return pos;
    }

    EXPORT_FUNC_EX(wchar*) MinVTGetDeviceAttributes()
    {
        //使用CoTaskMemAlloc后需要使用CoTaskMemFree进行回收(.Net会自动调用该函数进行回收)
        wchar* str = (wchar*)::CoTaskMemAlloc(VT_STR_LEN * sizeof(wchar));
        if (str == nullptr) return nullptr;
        int strLen = VT_STR_LEN;

        console.Write(VT_GET_DEVICE_ATTRIBUTES);

        INPUT_RECORD buffer[32];
        DWORD readCount;
        ::ReadConsoleInput(console.cons.consoleInput, buffer, LEN(buffer), &readCount);

        wstring wstr;
        for (size_t i = 0; i < readCount; i++)
        {
            if (IsVTInput(&buffer[i]))
            {
                wstr += buffer[i].Event.KeyEvent.uChar.UnicodeChar;
            }
        }

        //理解这里的处理详见:https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#query-state
        if (String::Compare(wstr, L"\x1b[?1;0c"))
        {
            wstr = L"VT101 with No Options";
        }

        //复制字符串
        auto r = ::wcscpy_s(str, strLen, wstr.c_str());
        //fail:
        if (r != 0)
        {
            ::CoTaskMemFree(str);
            return nullptr;
        }

        return str;
    }

    std::wstring VTConverter::VTResetStyle()
    {
        wstring wstr;

        wchar* buf = MinVTResetStyle();
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTForeColor(Color24 foreColor)
    {
        wstring wstr;

        wchar* buf = MinVTForeColor(foreColor);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTBackColor(Color24 backColor)
    {
        wstring wstr;

        wchar* buf = MinVTBackColor(backColor);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTColor(Color24 foreColor, Color24 backColor)
    {
        wstring wstr;

        wchar* buf = MinVTColor(foreColor, backColor);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTUnderline(bool underLine)
    {
        wstring wstr;

        wchar* buf = MinVTUnderline(underLine);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTWindowTitle(std::wstring title)
    {
        wstring wstr;

        wchar* buf = MinVTWindowTitle(title.c_str());
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTCursorPos(COORD pos)
    {
        wstring wstr;

        wchar* buf = MinVTCursorPos(pos);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTCursorVisible(bool visible)
    {
        wstring wstr;

        wchar* buf = MinVTCursorVisible(visible);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTTerminalColor(int color)
    {
        wstring wstr;

        wchar* buf = MinVTTerminalColor(color);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTTerminalForeColor(MinConsoleNative::TerminalColor tcolor)
    {
        wstring wstr;

        wchar* buf = MinVTTerminalForeColor(tcolor);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTTerminalBackColor(MinConsoleNative::TerminalColor tcolor)
    {
        wstring wstr;

        wchar* buf = MinVTTerminalBackColor(tcolor);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTTerminalSize(COORD size)
    {
        wstring wstr;

        wchar* buf = MinVTTerminalSize(size);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    std::wstring VTConverter::VTPaletteColor(int index, byte r, byte g, byte b)
    {
        wstring wstr;

        wchar* buf = MinVTPaletteColor(index, r, g, b);
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }

    bool VTConverter::VTSupport()
    {
        return MinVTSupport();
    }

    void VTConverter::VTEnableMouseInput()
    {
        MinVTEnableMouseInput();
    }

    void VTConverter::VTDisableMouseInput()
    {
        MinVTDisableMouseInput();
    }

    COORD VTConverter::VTGetCursorPos()
    {
        return MinVTGetCursorPos();
    }

    std::wstring VTConverter::VTGetDeviceAttributes()
    {
        wstring wstr;

        wchar* buf = MinVTGetDeviceAttributes();
        //复制字符串内容(copy string content):
        wstr = buf;
        ::CoTaskMemFree(buf);

        return wstr;
    }
}