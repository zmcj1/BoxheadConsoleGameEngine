#pragma once

#include "MinDefines.h"
#include <utility>
#include <string>

namespace MinConsoleNative
{
    enum class CharWidth
    {
        Unknown = 0,
        Half = 1,
        Full = 2,
    };

    enum class ConsoleColor
    {
        BLACK = 0,
        DARKBLUE = 1,
        DARKGREEN = 2,
        DARKCYAN = 3,
        DARKRED = 4,
        DARKMAGENTA = 5,
        DARKYELLOW = 6,
        GRAY = 7,
        DARKGRAY = 8,
        BLUE = 9,
        GREEN = 10,
        CYAN = 11,
        RED = 12,
        MAGENTA = 13,
        YELLOW = 14,
        WHITE = 15,
    };

    inline ushort ConsoleColorToUshort(ConsoleColor foreColor, ConsoleColor backColor)
    {
        return (ushort)((ushort)foreColor | ((ushort)backColor << 4));
    }

    inline std::pair<ConsoleColor, ConsoleColor> UshortToConsoleColor(ushort u)
    {
        std::pair<ConsoleColor, ConsoleColor> result;
        result.first = (ConsoleColor)(u & 0x000F);
        result.second = (ConsoleColor)((u & 0x00F0) / 16);
        return result;
    }

    struct ConsoleColorPair
    {
    public:
        ConsoleColor foreColor;
        ConsoleColor backColor;

        ConsoleColorPair()
        {
            this->foreColor = ConsoleColor::GRAY;
            this->backColor = ConsoleColor::BLACK;
        }

        ConsoleColorPair(ConsoleColor foreColor)
        {
            this->foreColor = foreColor;
            this->backColor = ConsoleColor::BLACK;
        }

        ConsoleColorPair(ConsoleColor foreColor, ConsoleColor backColor)
        {
            this->foreColor = foreColor;
            this->backColor = backColor;
        }

        ConsoleColorPair(ushort u)
        {
            std::pair<ConsoleColor, ConsoleColor> cp = UshortToConsoleColor(u);
            this->foreColor = cp.first;
            this->backColor = cp.second;
        }

        ushort ToUshort()
        {
            return ConsoleColorToUshort(foreColor, backColor);
        }
    };

    struct Color24
    {
    public:
        uint r;
        uint g;
        uint b;

        Color24()
        {
            this->r = 0;
            this->g = 0;
            this->b = 0;
        }

        Color24(uint r, uint g, uint b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        bool operator ==(const Color24& other)
        {
            if (r == other.r && g == other.g && b == other.b)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator !=(const Color24& other)
        {
            if (r == other.r && g == other.g && b == other.b)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        //Algorithm:https://stackoverflow.com/questions/1988833/converting-color-to-consolecolor
        ConsoleColor ToConsoleColor()
        {
            int index = (r > 128 || g > 128 || b > 128) ? 8 : 0; // Bright bit
            index |= (r > 64) ? 4 : 0; // Red bit
            index |= (g > 64) ? 2 : 0; // Green bit
            index |= (b > 64) ? 1 : 0; // Blue bit
            return (ConsoleColor)index;
        }
    };

    struct ConsoleInputMode
    {
    public:
        bool _ENABLE_PROCESSED_INPUT;               //default is TRUE(recommend to FALSE to avoid pressing CTRL+C to close the console program)
        bool _ENABLE_LINE_INPUT;                    //default is TRUE
        bool _ENABLE_ECHO_INPUT;                    //default is TRUE
        bool _ENABLE_WINDOW_INPUT;                  //default is FALSE(recommend to TRUE)
        bool _ENABLE_MOUSE_INPUT;                   //default is TRUE
        bool _ENABLE_INSERT_MODE;                   //default is TRUE
        bool _ENABLE_QUICK_EDIT_MODE;               //default is TRUE(recommend to FALSE)
        bool _ENABLE_EXTENDED_FLAGS;                //default is TRUE
        bool _ENABLE_AUTO_POSITION;                 //default is TRUE
        bool _ENABLE_VIRTUAL_TERMINAL_INPUT;        //default is FALSE

        ConsoleInputMode()
        {
            this->_ENABLE_PROCESSED_INPUT = true;
            this->_ENABLE_LINE_INPUT = true;
            this->_ENABLE_ECHO_INPUT = true;
            this->_ENABLE_WINDOW_INPUT = false;
            this->_ENABLE_MOUSE_INPUT = true;
            this->_ENABLE_INSERT_MODE = true;
            this->_ENABLE_QUICK_EDIT_MODE = true;
            this->_ENABLE_EXTENDED_FLAGS = true;
            this->_ENABLE_AUTO_POSITION = true;
            this->_ENABLE_VIRTUAL_TERMINAL_INPUT = false;
        }

        static ConsoleInputMode Standard()
        {
            ConsoleInputMode cim;
            cim._ENABLE_PROCESSED_INPUT = false;
            cim._ENABLE_WINDOW_INPUT = true;
            cim._ENABLE_QUICK_EDIT_MODE = false;
            return cim;
        }
    };

    struct ConsoleOutputMode
    {
    public:
        bool _ENABLE_PROCESSED_OUTPUT;              //default is TRUE
        bool _ENABLE_WRAP_AT_EOL_OUTPUT;            //default is TRUE
        bool _ENABLE_VIRTUAL_TERMINAL_PROCESSING;   //default is FALSE(recommend to TRUE, If want to use the VT100 sequence)
        bool _DISABLE_NEWLINE_AUTO_RETURN;          //default is FALSE
        bool _ENABLE_LVB_GRID_WORLDWIDE;            //default is FALSE

        ConsoleOutputMode()
        {
            this->_ENABLE_PROCESSED_OUTPUT = true;
            this->_ENABLE_WRAP_AT_EOL_OUTPUT = true;
            this->_ENABLE_VIRTUAL_TERMINAL_PROCESSING = false;
            this->_DISABLE_NEWLINE_AUTO_RETURN = false;
            this->_ENABLE_LVB_GRID_WORLDWIDE = false;
        }

        static ConsoleOutputMode Standard()
        {
            ConsoleOutputMode com;
            com._ENABLE_VIRTUAL_TERMINAL_PROCESSING = true;
            return com;
        }
    };

    struct ConsoleMode
    {
    public:
        ConsoleInputMode inputMode;
        ConsoleOutputMode outputMode;

        ConsoleMode()
        {
            this->inputMode = ConsoleInputMode();
            this->outputMode = ConsoleOutputMode();
        }

        ConsoleMode(ConsoleInputMode inputMode, ConsoleOutputMode outputMode)
        {
            this->inputMode = inputMode;
            this->outputMode = outputMode;
        }

        static ConsoleMode Standard()
        {
            auto inputMode = ConsoleInputMode::Standard();
            auto outputMode = ConsoleOutputMode::Standard();
            ConsoleMode consoleMode(inputMode, outputMode);
            return consoleMode;
        }
    };

    struct ConsoleSession
    {
    public:
        HWND consoleWindow;
        HANDLE consoleInput;
        HANDLE consoleOutput;

    public:
        ConsoleSession()
        {
            this->consoleWindow = nullptr;
            this->consoleInput = nullptr;
            this->consoleOutput = nullptr;
        }

        ConsoleSession(HWND consoleWindow, HANDLE consoleInput, HANDLE consoleOutput)
        {
            this->consoleWindow = consoleWindow;
            this->consoleInput = consoleInput;
            this->consoleOutput = consoleOutput;
        }
    };

    struct ConsoleFont
    {
    public:
        DWORD FontIndex{ 0 };
        COORD FontSize{ 0 };
        uint FontFamily{ 0 };
        uint FontWeight{ 0 };
        wchar FaceName[LF_FACESIZE]{ 0 };

        ConsoleFont()
        {
        }

        void SetFaceNameQuick(const std::wstring& faceName)
        {
            size_t fontNameLength = faceName.size();
            ::wcscpy_s(this->FaceName, fontNameLength + 1, faceName.c_str());
        }
    };

    extern const int MAX_INPUT_CHAR_COUNT;

    EXPORT_FUNC MinInitConsoleSession(ConsoleSession* cons);

    //return true means successful enable VT!
    EXPORT_FUNC MinEnableConsoleVT(ConsoleSession* cons);

    EXPORT_FUNC MinGetConsolePalette(ConsoleSession* cons, DWORD index, Color24* color);

    EXPORT_FUNC MinSetConsolePalette(ConsoleSession* cons, DWORD index, Color24 color);

    EXPORT_FUNC MinGetConsoleMode(ConsoleSession* cons, ConsoleMode* consoleMode);

    EXPORT_FUNC MinSetConsoleMode(ConsoleSession* cons, ConsoleMode consoleMode);

    EXPORT_FUNC MinGetConsoleFont(ConsoleSession* cons, ConsoleFont* consoleFont);

    EXPORT_FUNC MinSetConsoleFont(ConsoleSession* cons, ConsoleFont consoleFont);

    EXPORT_FUNC MinGetConsoleWindowSize(ConsoleSession* cons, POINT* size);

    EXPORT_FUNC MinSetConsoleWindowSize(ConsoleSession* cons, POINT size);

    EXPORT_FUNC MinGetConsoleBufferSize(ConsoleSession* cons, POINT* size);

    EXPORT_FUNC MinSetConsoleBufferSize(ConsoleSession* cons, POINT size);

    EXPORT_FUNC MinGetConsoleForeColor(ConsoleSession* cons, ConsoleColor* foreColor);

    EXPORT_FUNC MinGetConsoleBackColor(ConsoleSession* cons, ConsoleColor* backColor);

    EXPORT_FUNC MinSetConsoleForeColor(ConsoleSession* cons, ConsoleColor foreColor);

    EXPORT_FUNC MinSetConsoleBackColor(ConsoleSession* cons, ConsoleColor backColor);

    EXPORT_FUNC MinGetConsoleCursorPos(ConsoleSession* cons, COORD* pos);

    EXPORT_FUNC MinSetConsoleCursorPos(ConsoleSession* cons, COORD pos);

    //size of buffer should be : charCount * sizeof(wchar)
    EXPORT_FUNC MinReadConsole(ConsoleSession* cons, wchar* buffer, int charCount);

    EXPORT_FUNC MinWriteConsole(ConsoleSession* cons, const wchar* buffer);

    //You can use something like this:arr[i].Attributes |= COMMON_LVB_UNDERSCORE
    EXPORT_FUNC MinWriteConsoleOutput(ConsoleSession* cons, const CHAR_INFO* charInfos, short x, short y, short width, short height);

    EXPORT_FUNC MinGetCharWidth(ConsoleSession* cons, wchar c, CharWidth* cw);

    class Console
    {
    public:
        ConsoleSession cons;

        Console();

        Console(ConsoleSession cons);

        Console(HWND consoleWindow, HANDLE consoleInput, HANDLE consoleOutput);

        Color24 GetConsolePalette(DWORD index);

        //Notice:After calling this API, the screen buffer will change!
        bool SetConsolePalette(DWORD index, const Color24& color);

        ConsoleMode GetConsoleMode();

        bool SetConsoleMode(const ConsoleMode& consoleMode);

        ConsoleFont GetConsoleFont();

        bool SetConsoleFont(const ConsoleFont& consoleFont);

        POINT GetConsoleWindowSize();

        bool SetConsoleWindowSize(POINT size);

        POINT GetConsoleBufferSize();

        bool SetConsoleBufferSize(POINT size);

        ConsoleColor GetConsoleForeColor();

        ConsoleColor GetConsoleBackColor();

        bool SetConsoleForeColor(ConsoleColor foreColor);

        bool SetConsoleBackColor(ConsoleColor backColor);

        COORD GetConsoleCursorPos();

        bool SetConsoleCursorPos(COORD pos);

        std::wstring ReadConsoleW();

        bool WriteConsoleW(const std::wstring& msg);

        bool WriteConsoleOutputW(const CHAR_INFO* charInfos, short x, short y, short width, short height);

        CharWidth GetWcharWidth(wchar c);
    };
}