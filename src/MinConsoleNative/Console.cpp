﻿#include "Console.h"
#include "WinVersion.h"
#include "VTConverter.h"
#include "ConRegistry.h"
#include "Debug.h"
#include "PaletteSystem.h"
#include <conio.h> //Windows only

using namespace std;

namespace MinConsoleNative
{
    const int MAX_INPUT_CHAR_COUNT = 2048;

    EXPORT_FUNC_EX(bool) MinAllocConsole(_OUT_ ConsoleSession* cons)
    {
        bool allocSuc = ::AllocConsole();
        if (allocSuc)
        {
            bool initSuc = MinInitConsoleSession(cons);
            return initSuc;
        }
        return false;
    }

    EXPORT_FUNC_EX(bool) MinFreeConsole()
    {
        return ::FreeConsole();
    }

    EXPORT_FUNC MinInitConsoleSession(ConsoleSession* cons)
    {
        cons->consoleInput = ::GetStdHandle(STD_INPUT_HANDLE);
        if (cons->consoleInput == INVALID_HANDLE_VALUE)
        {
            return false;
        }
        cons->consoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
        if (cons->consoleOutput == INVALID_HANDLE_VALUE)
        {
            return false;
        }
        cons->consoleWindow = ::GetConsoleWindow();
        if (cons->consoleWindow == nullptr)
        {
            return false;
        }
        //Set CodePage to UTF-8, this will always be right.
        ::SetConsoleCP(CP_UTF8);
        ::SetConsoleOutputCP(CP_UTF8);
        //Ensure that the Chinese input method works normally.
        COORD pos;
        MinGetConsoleCursorPos(cons->consoleOutput, &pos);
        MinSetConsoleCursorPos(cons->consoleOutput, pos);
        return true;
    }

    EXPORT_FUNC MinEnableConsoleVT(HANDLE consoleInput, HANDLE consoleOutput)
    {
        bool supportVT = WinVersion::Global.GetInstance().IsWindows10CreatorsOrLater();
        if (supportVT)
        {
            ConsoleMode cm;
            cm.outputMode._ENABLE_VIRTUAL_TERMINAL_PROCESSING = true;
            return MinSetConsoleMode(consoleInput, consoleOutput, cm);
        }
        return false;
    }

    EXPORT_FUNC MinGetConsolePalette(HANDLE consoleOutput, DWORD index, Color24* color)
    {
        CONSOLE_SCREEN_BUFFER_INFOEX csbi;
        csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
        ::GetConsoleScreenBufferInfoEx(consoleOutput, &csbi);

        COLORREF colorRef = csbi.ColorTable[index];
        color->r = colorRef & 0x0000FF;
        color->g = (colorRef & 0x00FF00) >> 8;
        color->b = (colorRef & 0xFF0000) >> 16;
        return true;
    }

    EXPORT_FUNC MinSetConsolePalette(HANDLE consoleOutput, DWORD index, Color24 color)
    {
        CONSOLE_SCREEN_BUFFER_INFOEX csbi;
        //get
        csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
        ::GetConsoleScreenBufferInfoEx(consoleOutput, &csbi);
        //set
        csbi.ColorTable[index] = color.r + (color.g << 8) + (color.b << 16);
        return ::SetConsoleScreenBufferInfoEx(consoleOutput, &csbi);
    }

    EXPORT_FUNC_EX(ConsoleInputMode) MinGetConsoleInputMode(HANDLE consoleInput)
    {
        ConsoleInputMode cim;
        ConsoleInputMode* cim_ptr = &cim;

        DWORD inputMode = 0;
        ::GetConsoleMode(consoleInput, &inputMode);

        cim_ptr->_ENABLE_PROCESSED_INPUT =
            (inputMode & ENABLE_PROCESSED_INPUT) == ENABLE_PROCESSED_INPUT;
        cim_ptr->_ENABLE_LINE_INPUT =
            (inputMode & ENABLE_LINE_INPUT) == ENABLE_LINE_INPUT;
        cim_ptr->_ENABLE_ECHO_INPUT =
            (inputMode & ENABLE_ECHO_INPUT) == ENABLE_ECHO_INPUT;
        cim_ptr->_ENABLE_WINDOW_INPUT =
            (inputMode & ENABLE_WINDOW_INPUT) == ENABLE_WINDOW_INPUT;
        cim_ptr->_ENABLE_MOUSE_INPUT =
            (inputMode & ENABLE_MOUSE_INPUT) == ENABLE_MOUSE_INPUT;
        cim_ptr->_ENABLE_INSERT_MODE =
            (inputMode & ENABLE_INSERT_MODE) == ENABLE_INSERT_MODE;
        cim_ptr->_ENABLE_QUICK_EDIT_MODE =
            (inputMode & ENABLE_QUICK_EDIT_MODE) == ENABLE_QUICK_EDIT_MODE;
        cim_ptr->_ENABLE_EXTENDED_FLAGS =
            (inputMode & ENABLE_EXTENDED_FLAGS) == ENABLE_EXTENDED_FLAGS;
        cim_ptr->_ENABLE_AUTO_POSITION =
            (inputMode & ENABLE_AUTO_POSITION) == ENABLE_AUTO_POSITION;
        cim_ptr->_ENABLE_VIRTUAL_TERMINAL_INPUT =
            (inputMode & ENABLE_VIRTUAL_TERMINAL_INPUT) == ENABLE_VIRTUAL_TERMINAL_INPUT;

        return *cim_ptr;
    }

    EXPORT_FUNC_EX(bool) MinSetConsoleInputMode(HANDLE consoleInput, ConsoleInputMode mode)
    {
        DWORD inputMode = 0;
        const ConsoleInputMode* cim_ptr = &mode;

        if (cim_ptr->_ENABLE_PROCESSED_INPUT)
            inputMode |= ENABLE_PROCESSED_INPUT;
        if (cim_ptr->_ENABLE_LINE_INPUT)
            inputMode |= ENABLE_LINE_INPUT;
        if (cim_ptr->_ENABLE_ECHO_INPUT)
            inputMode |= ENABLE_ECHO_INPUT;
        if (cim_ptr->_ENABLE_WINDOW_INPUT)
            inputMode |= ENABLE_WINDOW_INPUT;
        if (cim_ptr->_ENABLE_MOUSE_INPUT)
            inputMode |= ENABLE_MOUSE_INPUT;
        if (cim_ptr->_ENABLE_INSERT_MODE)
            inputMode |= ENABLE_INSERT_MODE;
        if (cim_ptr->_ENABLE_QUICK_EDIT_MODE)
            inputMode |= ENABLE_QUICK_EDIT_MODE;
        if (cim_ptr->_ENABLE_EXTENDED_FLAGS)
            inputMode |= ENABLE_EXTENDED_FLAGS;
        if (cim_ptr->_ENABLE_AUTO_POSITION)
            inputMode |= ENABLE_AUTO_POSITION;
        if (cim_ptr->_ENABLE_VIRTUAL_TERMINAL_INPUT)
            inputMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

        return ::SetConsoleMode(consoleInput, inputMode);
    }

    EXPORT_FUNC_EX(ConsoleOutputMode) MinGetConsoleOutputMode(HANDLE consoleOutput)
    {
        ConsoleOutputMode com;
        ConsoleOutputMode* com_ptr = &com;

        DWORD outputMode = 0;
        ::GetConsoleMode(consoleOutput, &outputMode);

        com_ptr->_ENABLE_PROCESSED_OUTPUT =
            (outputMode & ENABLE_PROCESSED_OUTPUT) == ENABLE_PROCESSED_OUTPUT;
        com_ptr->_ENABLE_WRAP_AT_EOL_OUTPUT =
            (outputMode & ENABLE_WRAP_AT_EOL_OUTPUT) == ENABLE_WRAP_AT_EOL_OUTPUT;
        com_ptr->_ENABLE_VIRTUAL_TERMINAL_PROCESSING =
            (outputMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        com_ptr->_DISABLE_NEWLINE_AUTO_RETURN =
            (outputMode & DISABLE_NEWLINE_AUTO_RETURN) == DISABLE_NEWLINE_AUTO_RETURN;
        com_ptr->_ENABLE_LVB_GRID_WORLDWIDE =
            (outputMode & ENABLE_LVB_GRID_WORLDWIDE) == ENABLE_LVB_GRID_WORLDWIDE;

        return *com_ptr;
    }

    EXPORT_FUNC_EX(bool) MinSetConsoleOutputMode(HANDLE consoleOutput, ConsoleOutputMode mode)
    {
        DWORD outputMode = 0;
        const ConsoleOutputMode* com_ptr = &mode;

        if (com_ptr->_ENABLE_PROCESSED_OUTPUT)
            outputMode |= ENABLE_PROCESSED_OUTPUT;
        if (com_ptr->_ENABLE_WRAP_AT_EOL_OUTPUT)
            outputMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
        if (com_ptr->_ENABLE_VIRTUAL_TERMINAL_PROCESSING)
            outputMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (com_ptr->_DISABLE_NEWLINE_AUTO_RETURN)
            outputMode |= DISABLE_NEWLINE_AUTO_RETURN;
        if (com_ptr->_ENABLE_LVB_GRID_WORLDWIDE)
            outputMode |= ENABLE_LVB_GRID_WORLDWIDE;

        return ::SetConsoleMode(consoleOutput, outputMode);
    }

    EXPORT_FUNC MinGetConsoleMode(HANDLE consoleInput, HANDLE consoleOutput, ConsoleMode* consoleMode)
    {
        ConsoleInputMode cim;
        ConsoleOutputMode com;

        ConsoleInputMode* cim_ptr = &cim;
        ConsoleOutputMode* com_ptr = &com;

        DWORD inputMode = 0, outputMode = 0;
        ::GetConsoleMode(consoleInput, &inputMode);
        ::GetConsoleMode(consoleOutput, &outputMode);

        cim_ptr->_ENABLE_PROCESSED_INPUT =
            (inputMode & ENABLE_PROCESSED_INPUT) == ENABLE_PROCESSED_INPUT;
        cim_ptr->_ENABLE_LINE_INPUT =
            (inputMode & ENABLE_LINE_INPUT) == ENABLE_LINE_INPUT;
        cim_ptr->_ENABLE_ECHO_INPUT =
            (inputMode & ENABLE_ECHO_INPUT) == ENABLE_ECHO_INPUT;
        cim_ptr->_ENABLE_WINDOW_INPUT =
            (inputMode & ENABLE_WINDOW_INPUT) == ENABLE_WINDOW_INPUT;
        cim_ptr->_ENABLE_MOUSE_INPUT =
            (inputMode & ENABLE_MOUSE_INPUT) == ENABLE_MOUSE_INPUT;
        cim_ptr->_ENABLE_INSERT_MODE =
            (inputMode & ENABLE_INSERT_MODE) == ENABLE_INSERT_MODE;
        cim_ptr->_ENABLE_QUICK_EDIT_MODE =
            (inputMode & ENABLE_QUICK_EDIT_MODE) == ENABLE_QUICK_EDIT_MODE;
        cim_ptr->_ENABLE_EXTENDED_FLAGS =
            (inputMode & ENABLE_EXTENDED_FLAGS) == ENABLE_EXTENDED_FLAGS;
        cim_ptr->_ENABLE_AUTO_POSITION =
            (inputMode & ENABLE_AUTO_POSITION) == ENABLE_AUTO_POSITION;
        cim_ptr->_ENABLE_VIRTUAL_TERMINAL_INPUT =
            (inputMode & ENABLE_VIRTUAL_TERMINAL_INPUT) == ENABLE_VIRTUAL_TERMINAL_INPUT;

        com_ptr->_ENABLE_PROCESSED_OUTPUT =
            (outputMode & ENABLE_PROCESSED_OUTPUT) == ENABLE_PROCESSED_OUTPUT;
        com_ptr->_ENABLE_WRAP_AT_EOL_OUTPUT =
            (outputMode & ENABLE_WRAP_AT_EOL_OUTPUT) == ENABLE_WRAP_AT_EOL_OUTPUT;
        com_ptr->_ENABLE_VIRTUAL_TERMINAL_PROCESSING =
            (outputMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) == ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        com_ptr->_DISABLE_NEWLINE_AUTO_RETURN =
            (outputMode & DISABLE_NEWLINE_AUTO_RETURN) == DISABLE_NEWLINE_AUTO_RETURN;
        com_ptr->_ENABLE_LVB_GRID_WORLDWIDE =
            (outputMode & ENABLE_LVB_GRID_WORLDWIDE) == ENABLE_LVB_GRID_WORLDWIDE;

        consoleMode->inputMode = cim;
        consoleMode->outputMode = com;

        return true;
    }

    EXPORT_FUNC MinSetConsoleMode(HANDLE consoleInput, HANDLE consoleOutput, ConsoleMode consoleMode)
    {
        DWORD inputMode = 0, outputMode = 0;

        const ConsoleInputMode* cim_ptr = &consoleMode.inputMode;
        const ConsoleOutputMode* com_ptr = &consoleMode.outputMode;

        if (cim_ptr->_ENABLE_PROCESSED_INPUT)
            inputMode |= ENABLE_PROCESSED_INPUT;
        if (cim_ptr->_ENABLE_LINE_INPUT)
            inputMode |= ENABLE_LINE_INPUT;
        if (cim_ptr->_ENABLE_ECHO_INPUT)
            inputMode |= ENABLE_ECHO_INPUT;
        if (cim_ptr->_ENABLE_WINDOW_INPUT)
            inputMode |= ENABLE_WINDOW_INPUT;
        if (cim_ptr->_ENABLE_MOUSE_INPUT)
            inputMode |= ENABLE_MOUSE_INPUT;
        if (cim_ptr->_ENABLE_INSERT_MODE)
            inputMode |= ENABLE_INSERT_MODE;
        if (cim_ptr->_ENABLE_QUICK_EDIT_MODE)
            inputMode |= ENABLE_QUICK_EDIT_MODE;
        if (cim_ptr->_ENABLE_EXTENDED_FLAGS)
            inputMode |= ENABLE_EXTENDED_FLAGS;
        if (cim_ptr->_ENABLE_AUTO_POSITION)
            inputMode |= ENABLE_AUTO_POSITION;
        if (cim_ptr->_ENABLE_VIRTUAL_TERMINAL_INPUT)
            inputMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;

        if (com_ptr->_ENABLE_PROCESSED_OUTPUT)
            outputMode |= ENABLE_PROCESSED_OUTPUT;
        if (com_ptr->_ENABLE_WRAP_AT_EOL_OUTPUT)
            outputMode |= ENABLE_WRAP_AT_EOL_OUTPUT;
        if (com_ptr->_ENABLE_VIRTUAL_TERMINAL_PROCESSING)
            outputMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (com_ptr->_DISABLE_NEWLINE_AUTO_RETURN)
            outputMode |= DISABLE_NEWLINE_AUTO_RETURN;
        if (com_ptr->_ENABLE_LVB_GRID_WORLDWIDE)
            outputMode |= ENABLE_LVB_GRID_WORLDWIDE;

        bool is = ::SetConsoleMode(consoleInput, inputMode);
        bool os = ::SetConsoleMode(consoleOutput, outputMode);
        return is && os;
    }

    EXPORT_FUNC MinGetConsoleFont(HANDLE consoleOutput, ConsoleFont* consoleFont)
    {
        //get
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        ::GetCurrentConsoleFontEx(consoleOutput, false, &cfi);
        //set
        consoleFont->FontIndex = cfi.nFont;
        consoleFont->FontSize = cfi.dwFontSize;
        consoleFont->FontFamily = cfi.FontFamily;
        consoleFont->FontWeight = cfi.FontWeight;
        size_t fontNameLength = wcslen(cfi.FaceName);
        ::wcscpy_s(consoleFont->FaceName, fontNameLength + 1, cfi.FaceName);
        return true;
    }

    EXPORT_FUNC MinSetConsoleFont(HANDLE consoleOutput, ConsoleFont consoleFont)
    {
        //get
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        ::GetCurrentConsoleFontEx(consoleOutput, false, &cfi);
        //set
        cfi.dwFontSize = consoleFont.FontSize;
        cfi.FontWeight = consoleFont.FontWeight;
        size_t fontNameLength = wcslen(consoleFont.FaceName);
        ::wcscpy_s(cfi.FaceName, fontNameLength + 1, consoleFont.FaceName);
        return ::SetCurrentConsoleFontEx(consoleOutput, false, &cfi);
    }

    EXPORT_FUNC MinGetConsoleWindowSize(HANDLE consoleOutput, POINT* size)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);
        size->x = (csbi.srWindow.Right - csbi.srWindow.Left) + 1;
        size->y = (csbi.srWindow.Bottom - csbi.srWindow.Top) + 1;
        return true;
    }

    EXPORT_FUNC MinSetConsoleWindowSize(HANDLE consoleOutput, POINT size)
    {
        SMALL_RECT sm;
        sm.Left = 0;
        sm.Top = 0;
        sm.Right = size.x - 1;
        sm.Bottom = size.y - 1;
        return ::SetConsoleWindowInfo(consoleOutput, true, &sm);
    }

    EXPORT_FUNC MinGetConsoleBufferSize(HANDLE consoleOutput, POINT* size)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);
        size->x = csbi.dwSize.X;
        size->y = csbi.dwSize.Y;
        return true;
    }

    EXPORT_FUNC MinSetConsoleBufferSize(HANDLE consoleOutput, POINT size)
    {
        COORD coord;
        coord.X = size.x;
        coord.Y = size.y;
        return ::SetConsoleScreenBufferSize(consoleOutput, coord);
    }

    EXPORT_FUNC_EX(bool) MinCheckSize(HANDLE consoleOutput, POINT size)
    {
        COORD maxSize = ::GetLargestConsoleWindowSize(consoleOutput);
        if (size.x > maxSize.X)
        {
            Debug::SetLastMinErrorMsg(_T("The specified consoleWidth is too large"));
            return false;
        }
        if (size.y > maxSize.Y)
        {
            Debug::SetLastMinErrorMsg(_T("The specified consoleHeight is too large"));
            return false;
        }
        return true;
    }

    EXPORT_FUNC_EX(void) MinSetConsoleWindowAndBufferSize(HANDLE consoleOutput, POINT size)
    {
        //It may be possible to avoid the Windows console crashing when adjusting the screen size in Windows 10.
        //MinSetConsoleCursorPos(consoleOutput, { 0, 0 });

        //Avoid the console buffer size is smaller than the console window size, so we set it to 1, 1. But if this line cause an exception, try to disable this line of code.
        MinSetConsoleWindowSize(consoleOutput, { 1, 1 });
        MinSetConsoleBufferSize(consoleOutput, size);
        MinSetConsoleWindowSize(consoleOutput, size);
    }

    EXPORT_FUNC MinGetConsoleForeColor(HANDLE consoleOutput, ConsoleColor* foreColor)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);
        *foreColor = (ConsoleColor)(csbi.wAttributes & 0x000F);
        return true;
    }

    EXPORT_FUNC MinGetConsoleBackColor(HANDLE consoleOutput, ConsoleColor* backColor)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);
        *backColor = (ConsoleColor)((csbi.wAttributes & 0x00F0) / 16);
        return true;
    }

    EXPORT_FUNC MinSetConsoleForeColor(HANDLE consoleOutput, ConsoleColor foreColor)
    {
        ConsoleColor backColor = ConsoleColor::BLACK;
        MinGetConsoleBackColor(consoleOutput, &backColor);
        ushort att = (ushort)((ushort)foreColor | ((ushort)backColor << 4));
        return ::SetConsoleTextAttribute(consoleOutput, att);
    }

    EXPORT_FUNC MinSetConsoleBackColor(HANDLE consoleOutput, ConsoleColor backColor)
    {
        ConsoleColor foreColor = ConsoleColor::GRAY;
        MinGetConsoleForeColor(consoleOutput, &foreColor);
        ushort att = (ushort)((ushort)foreColor | ((ushort)backColor << 4));
        return ::SetConsoleTextAttribute(consoleOutput, att);
    }

    EXPORT_FUNC_EX(bool) MinResetConsoleColor(HANDLE consoleOutput)
    {
        bool set_foreColor_suc = MinSetConsoleForeColor(consoleOutput, ConsoleColor::GRAY);
        bool set_backColor_suc = MinSetConsoleBackColor(consoleOutput, ConsoleColor::BLACK);
        return set_foreColor_suc && set_backColor_suc;
    }

    EXPORT_FUNC MinGetConsoleCursorPos(HANDLE consoleOutput, COORD* pos)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);
        *pos = csbi.dwCursorPosition;
        return true;
    }

    EXPORT_FUNC MinSetConsoleCursorPos(HANDLE consoleOutput, COORD pos)
    {
        return ::SetConsoleCursorPosition(consoleOutput, pos);
    }

    EXPORT_FUNC MinReadConsole(HANDLE consoleInput, wchar* buffer, int charCount)
    {
        DWORD read = 0;
        return ::ReadConsole(consoleInput, buffer, charCount, &read, nullptr);
    }

    EXPORT_FUNC MinReadConsoleInput(HANDLE consoleInput, OnReadConsoleMouseInputRecord callback1, OnReadConsoleKeyboardInputRecord callback2, OnConsoleOutputBufferChanged callback3)
    {
        ConsoleInputMode inputMode = MinGetConsoleInputMode(consoleInput);
        if (!inputMode._ENABLE_WINDOW_INPUT || inputMode._ENABLE_QUICK_EDIT_MODE)
        {
            Debug::OutputLine(L"IMPORTANT:Please turn on EnableWindowInput and turn off EnableQuickEditMode");
            return false;
        }

        //IMPORTANT!!!
        //Invoke GetNumberOfConsoleInputEvents first instead of directly invoke ReadConsoleInput, otherwise it will block the entire thread.
        DWORD eventNumber = 0;
        bool suc1 = ::GetNumberOfConsoleInputEvents(consoleInput, &eventNumber);
        if (!suc1) return false;
        if (eventNumber == 0) return true;

        // The number read by GetNumberOfConsoleInputEvents is not necessarily equal to the real number, so we have to creat const array here.
        const int BUF_SIZE = 64;
        INPUT_RECORD inputBuf[BUF_SIZE];
        bool suc2 = ::ReadConsoleInput(consoleInput, inputBuf, BUF_SIZE, &eventNumber);
        if (!suc2) return false;
        if (eventNumber == 0) return true;
        if (eventNumber > BUF_SIZE) return false; //Current array cannot contain all events!

        ConsoleMouseInputRecord mouseInputRecord;
        ConsoleKeyboardInputRecord keyboardInputRecord;
        uint keyState = 0;

        for (DWORD i = 0; i < eventNumber; i++)
        {
            switch (inputBuf[i].EventType)
            {
            case KEY_EVENT:
                //set status
                keyState = inputBuf[i].Event.KeyEvent.dwControlKeyState;
                keyboardInputRecord._RIGHT_ALT_PRESSED = keyState & RIGHT_ALT_PRESSED;
                keyboardInputRecord._LEFT_ALT_PRESSED = keyState & LEFT_ALT_PRESSED;
                keyboardInputRecord._RIGHT_CTRL_PRESSED = keyState & RIGHT_CTRL_PRESSED;
                keyboardInputRecord._LEFT_CTRL_PRESSED = keyState & LEFT_CTRL_PRESSED;
                keyboardInputRecord._SHIFT_PRESSED = keyState & SHIFT_PRESSED;
                keyboardInputRecord._NUMLOCK_ON = keyState & NUMLOCK_ON;
                keyboardInputRecord._SCROLLLOCK_ON = keyState & SCROLLLOCK_ON;
                keyboardInputRecord._CAPSLOCK_ON = keyState & CAPSLOCK_ON;
                keyboardInputRecord._ENHANCED_KEY = keyState & ENHANCED_KEY;
                //readkey
                if (inputBuf[i].Event.KeyEvent.bKeyDown)
                {
                    keyboardInputRecord.KeyChar = inputBuf[i].Event.KeyEvent.uChar.UnicodeChar;
                    keyboardInputRecord.VirtualKey = inputBuf[i].Event.KeyEvent.wVirtualKeyCode;
                    //invoke callback
                    if (callback2 != nullptr)
                    {
                        callback2(keyboardInputRecord);
                    }
                }
                break;
            case MOUSE_EVENT:
                //this value will be right.
                mouseInputRecord.position = inputBuf[i].Event.MouseEvent.dwMousePosition;
                //switch
                switch (inputBuf[i].Event.MouseEvent.dwEventFlags)
                {
                case MOUSE_MOVED:
                    mouseInputRecord.moved = true;
                    break;
                case DOUBLE_CLICK:
                    mouseInputRecord.doubleClick = true;
                    break;
                case MOUSE_WHEELED:
                    DWORD buttonState = inputBuf[i].Event.MouseEvent.dwButtonState;
                    int value = buttonState >> sizeof(buttonState) * 8;
                    if (value > 0)
                    {
                        mouseInputRecord.mouseWheelDir = MouseWheelDirection::Up;
                    }
                    else if (value < 0)
                    {
                        mouseInputRecord.mouseWheelDir = MouseWheelDirection::Down;
                    }
                    else
                    {
                        mouseInputRecord.mouseWheelDir = MouseWheelDirection::None;
                    }
                    break;
                }
                //invoke callback
                if (callback1 != nullptr)
                {
                    callback1(mouseInputRecord);
                }
                break;
            case WINDOW_BUFFER_SIZE_EVENT:
                //invoke callback
                if (callback3 != nullptr)
                {
                    callback3(inputBuf[i].Event.WindowBufferSizeEvent.dwSize);
                }
                break;
            }
        }

        return true;
    }

    EXPORT_FUNC_EX(bool) MinReadConsoleOneInput(HANDLE consoleInput, OnReadConsoleMouseInputRecord callback1, OnReadConsoleKeyboardInputRecord callback2, OnConsoleOutputBufferChanged callback3)
    {
        //IMPORTANT!!!
        //Invoke GetNumberOfConsoleInputEvents first instead of directly invoke ReadConsoleInput, otherwise it will block the entire thread.
        DWORD eventNumber;
        bool suc1 = ::GetNumberOfConsoleInputEvents(consoleInput, &eventNumber);
        if (!suc1) return false;
        if (eventNumber == 0) return true;

        INPUT_RECORD inputBuf;
        bool suc2 = ::ReadConsoleInput(consoleInput, &inputBuf, 1, &eventNumber);
        if (!suc2) return false;
        if (eventNumber == 0) return false;

        ConsoleMouseInputRecord mouseInputRecord;
        ConsoleKeyboardInputRecord keyboardInputRecord;
        uint keyState = 0;

        switch (inputBuf.EventType)
        {
        case KEY_EVENT:
            //set status
            keyState = inputBuf.Event.KeyEvent.dwControlKeyState;
            keyboardInputRecord._RIGHT_ALT_PRESSED = keyState & RIGHT_ALT_PRESSED;
            keyboardInputRecord._LEFT_ALT_PRESSED = keyState & LEFT_ALT_PRESSED;
            keyboardInputRecord._RIGHT_CTRL_PRESSED = keyState & RIGHT_CTRL_PRESSED;
            keyboardInputRecord._LEFT_CTRL_PRESSED = keyState & LEFT_CTRL_PRESSED;
            keyboardInputRecord._SHIFT_PRESSED = keyState & SHIFT_PRESSED;
            keyboardInputRecord._NUMLOCK_ON = keyState & NUMLOCK_ON;
            keyboardInputRecord._SCROLLLOCK_ON = keyState & SCROLLLOCK_ON;
            keyboardInputRecord._CAPSLOCK_ON = keyState & CAPSLOCK_ON;
            keyboardInputRecord._ENHANCED_KEY = keyState & ENHANCED_KEY;
            //readkey
            if (inputBuf.Event.KeyEvent.bKeyDown)
            {
                keyboardInputRecord.KeyChar = inputBuf.Event.KeyEvent.uChar.UnicodeChar;
                keyboardInputRecord.VirtualKey = inputBuf.Event.KeyEvent.wVirtualKeyCode;
                //invoke callback
                if (callback2 != nullptr)
                {
                    callback2(keyboardInputRecord);
                }
            }
            break;
        case MOUSE_EVENT:
            //this value will be right.
            mouseInputRecord.position = inputBuf.Event.MouseEvent.dwMousePosition;
            //switch
            switch (inputBuf.Event.MouseEvent.dwEventFlags)
            {
            case MOUSE_MOVED:
                mouseInputRecord.moved = true;
                break;
            case DOUBLE_CLICK:
                mouseInputRecord.doubleClick = true;
                break;
            case MOUSE_WHEELED:
                DWORD buttonState = inputBuf.Event.MouseEvent.dwButtonState;
                int value = buttonState >> sizeof(buttonState) * 8;
                if (value > 0)
                {
                    mouseInputRecord.mouseWheelDir = MouseWheelDirection::Up;
                }
                else if (value < 0)
                {
                    mouseInputRecord.mouseWheelDir = MouseWheelDirection::Down;
                }
                else
                {
                    mouseInputRecord.mouseWheelDir = MouseWheelDirection::None;
                }
                break;
            }
            //invoke callback
            if (callback1 != nullptr)
            {
                callback1(mouseInputRecord);
            }
            break;
        case WINDOW_BUFFER_SIZE_EVENT:
            //invoke callback
            if (callback3 != nullptr)
            {
                callback3(inputBuf.Event.WindowBufferSizeEvent.dwSize);
            }
            break;
        }

        return true;
    }

    EXPORT_FUNC MinWriteConsole(HANDLE consoleOutput, const wchar* buffer)
    {
        int len = wcslen(buffer);
        DWORD wr = 0;
        return ::WriteConsole(consoleOutput, buffer, len, &wr, nullptr);
    }

    EXPORT_FUNC MinWriteConsoleOutput(HANDLE consoleOutput, const CHAR_INFO* charInfos, short x, short y, short width, short height)
    {
        COORD size;
        size.X = width;
        size.Y = height;

        COORD coord;
        coord.X = 0;
        coord.Y = 0;

        SMALL_RECT smallRect;
        smallRect.Left = x;
        smallRect.Top = y;
        smallRect.Right = x + width - 1;
        smallRect.Bottom = y + height - 1;

        return ::WriteConsoleOutput(consoleOutput, charInfos, size, coord, &smallRect);
    }

    EXPORT_FUNC MinWriteConsoleOutputAttribute(HANDLE consoleOutput, const ushort* att, int attCount, COORD pos)
    {
        DWORD written = 0;
        return ::WriteConsoleOutputAttribute(consoleOutput, att, attCount, pos, &written);
    }

    EXPORT_FUNC MinWriteConsoleOutputCharacter(HANDLE consoleOutput, const wchar* str, int charCount, COORD pos)
    {
        DWORD written = 0;
        return ::WriteConsoleOutputCharacter(consoleOutput, str, charCount, pos, &written);
    }

    EXPORT_FUNC MinCreateConsoleScreenBuffer(HANDLE* consoleOutput)
    {
        *consoleOutput = ::CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ,
            FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        return consoleOutput != INVALID_HANDLE_VALUE;
    }

    EXPORT_FUNC MinSetConsoleActiveScreenBuffer(HANDLE consoleOutput)
    {
        return ::SetConsoleActiveScreenBuffer(consoleOutput);
    }

    EXPORT_FUNC MinCloseConsoleScreenBuffer(HANDLE consoleOutput)
    {
        return ::CloseHandle(consoleOutput);
    }

    EXPORT_FUNC MinCreateFile(ConsoleFile fileMode, HANDLE* handle)
    {
        const wchar* modeString = nullptr;
        switch (fileMode)
        {
        case ConsoleFile::Read:
            modeString = CONSOLE_INPUT_STRING;
            break;
        case ConsoleFile::Write:
            modeString = CONSOLE_OUTPUT_STRING;
            break;
        }

        if (modeString == nullptr) return false;

        *handle = ::CreateFile(modeString,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr, OPEN_EXISTING, 0, nullptr);

        return *handle != INVALID_HANDLE_VALUE;
    }

    EXPORT_FUNC MinWriteFile(HANDLE handle, const char* str)
    {
        DWORD written = 0;
        return ::WriteFile(handle, str, strlen(str), &written, nullptr);
    }

    EXPORT_FUNC MinReadFile(HANDLE handle, char* buffer, DWORD bufferLen)
    {
        DWORD readCount = 0;
        return ::ReadFile(handle, buffer, bufferLen, &readCount, nullptr);
    }

    EXPORT_FUNC MinGetCharWidth(HWND consoleWindow, HANDLE consoleOutput, wchar c, CharWidth* cw)
    {
        HDC hdc = GetDC(consoleWindow);

        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof(cfi);
        GetCurrentConsoleFontEx(consoleOutput, false, &cfi);

        //get default value
        HGDIOBJ hfont = GetCurrentObject(hdc, OBJ_FONT);
        LOGFONT logFont;
        GetObject(hfont, sizeof(logFont), &logFont);

        logFont.lfHeight = cfi.dwFontSize.Y;
        logFont.lfWidth = cfi.dwFontSize.X;
        logFont.lfEscapement;
        logFont.lfOrientation;
        logFont.lfWeight = cfi.FontWeight;
        logFont.lfItalic;
        logFont.lfUnderline;
        logFont.lfStrikeOut;
        logFont.lfCharSet = ANSI_CHARSET; //Set it to ANSI
        logFont.lfOutPrecision;
        logFont.lfClipPrecision;
        logFont.lfQuality;
        logFont.lfPitchAndFamily = cfi.FontFamily;
        wcscpy_s(logFont.lfFaceName, LF_FACESIZE, cfi.FaceName);

        HFONT hFont = CreateFontIndirect(&logFont);

        ((HFONT)SelectObject((hdc), (HGDIOBJ)(HFONT)(hFont)));

        TEXTMETRICW textm;

        bool suc = GetTextMetrics(hdc, &textm);
        bool isTrueType = textm.tmPitchAndFamily == TMPF_TRUETYPE;

        int width = 0;
        if (isTrueType)
        {
            ABC abc;
            GetCharABCWidths(hdc, c, c, &abc); //GetCharWidth
            width = abc.abcA + abc.abcB + abc.abcC;
        }
        else
        {
            GetCharWidth32(hdc, c, c, &width); //GetCharWidth
        }

        if (width >= textm.tmMaxCharWidth)
        {
            *cw = CharWidth::Full;
        }
        else
        {
            *cw = CharWidth::Half;
        }

        ReleaseDC(consoleWindow, hdc);

        return true;
    }

    EXPORT_FUNC MinGetStringWidth(HWND consoleWindow, HANDLE consoleOutput, const wchar* str, int* width)
    {
        size_t len = wcslen(str);

        for (size_t i = 0; i < len; i++)
        {
            CharWidth cw;
            MinGetCharWidth(consoleWindow, consoleOutput, str[i], &cw);
            *width += (int)cw;
        }
        return true;
    }

    EXPORT_FUNC MinGetTitle(wchar* titleBuffer, int sizeOfBuffer)
    {
        return ::GetConsoleTitle(titleBuffer, sizeOfBuffer) == 0;
    }

    EXPORT_FUNC MinSetTitle(const wchar* titleBuffer)
    {
        return ::SetConsoleTitle(titleBuffer);
    }

    EXPORT_FUNC MinGetConsoleCursorVisible(HANDLE consoleOutput, bool* visible)
    {
        CONSOLE_CURSOR_INFO cci;
        ::GetConsoleCursorInfo(consoleOutput, &cci);
        *visible = cci.bVisible;
        return true;
    }

    EXPORT_FUNC MinSetConsoleCursorVisible(HANDLE consoleOutput, bool visible)
    {
        CONSOLE_CURSOR_INFO cci;
        ::GetConsoleCursorInfo(consoleOutput, &cci);
        cci.bVisible = visible;
        return ::SetConsoleCursorInfo(consoleOutput, &cci);
    }

    EXPORT_FUNC MinClear(HANDLE consoleOutput)
    {
        ConsoleType consoleType = ConsoleType::WindowsConsole;
        MinGetConsoleType(&consoleType);
        if (consoleType == ConsoleType::WindowsTerminal)
        {
            //Especially effective in Windows Terminal.
            ::system("cls");
            return true;
        }
        else
        {
            POINT bufSize;
            MinGetConsoleBufferSize(consoleOutput, &bufSize);

            int length = bufSize.x * bufSize.y;
            COORD coord = { 0, 0 };
            DWORD written = 0;

            //Put the cursor at its home coordinates.
            MinSetConsoleCursorPos(consoleOutput, { 0, 0 });

            ::FillConsoleOutputCharacter(consoleOutput, _T(' '), length, coord, &written);

            CONSOLE_SCREEN_BUFFER_INFO csbi;
            ::GetConsoleScreenBufferInfo(consoleOutput, &csbi);

            return ::FillConsoleOutputAttribute(consoleOutput, csbi.wAttributes, length, coord, &written);
        }
    }

    EXPORT_FUNC MinSetConsoleCtrlHandler(PHANDLER_ROUTINE handler, bool add)
    {
        return ::SetConsoleCtrlHandler(handler, add);
    }

    EXPORT_FUNC MinGetConsoleType(ConsoleType* type)
    {
        wchar buffer[MAX_PATH] = { 0 };
        GetEnvironmentVariable(L"WT_SESSION", buffer, MAX_PATH);

        //Now support Windows Terminal!
        if (wcscmp(buffer, L"") != 0)
        {
            *type = ConsoleType::WindowsTerminal;
        }
        else
        {
            bool legacy = false;
            MinIsUsingLegacyConsole(&legacy);
            if (legacy)
            {
                *type = ConsoleType::WindowsLegacyConsole;
            }
            else
            {
                *type = ConsoleType::WindowsConsole;
            }
        }
        return true;
    }

    EXPORT_FUNC_EX(bool) MinRefreshScreen(HANDLE consoleOutput, wchar c, ushort att)
    {
        POINT bufSize;
        MinGetConsoleBufferSize(consoleOutput, &bufSize);

        int length = bufSize.x * bufSize.y;
        COORD coord = { 0, 0 };
        DWORD written = 0;

        //Put the cursor at its home coordinates.
        MinSetConsoleCursorPos(consoleOutput, { 0, 0 });

        ::FillConsoleOutputCharacter(consoleOutput, c, length, coord, &written);

        return ::FillConsoleOutputAttribute(consoleOutput, att, length, coord, &written);
    }

    EXPORT_FUNC_EX(bool) MinFlushConsoleInputBuffer(HANDLE consoleInput)
    {
        return ::FlushConsoleInputBuffer(consoleInput);
    }

    bool Console::forceVT = false;

    Console::Console()
    {
        this->cons = Console::InitConsoleSession();
        this->supportVT = MinEnableConsoleVT(cons.consoleInput, cons.consoleOutput);
    }

    Console::Console(ConsoleSession cons)
    {
        this->cons = cons;
        this->supportVT = MinEnableConsoleVT(cons.consoleInput, cons.consoleOutput);
    }

    Console::Console(HWND consoleWindow, HANDLE consoleInput, HANDLE consoleOutput)
    {
        this->cons = ConsoleSession(consoleWindow, consoleInput, consoleOutput);
        this->supportVT = MinEnableConsoleVT(cons.consoleInput, cons.consoleOutput);
    }

    Color24 Console::GetConsolePalette(DWORD index)
    {
        Color24 color;
        MinGetConsolePalette(cons.consoleOutput, index, &color);
        return color;
    }

    bool Console::SetConsolePalette(DWORD index, const Color24& color)
    {
        return MinSetConsolePalette(cons.consoleOutput, index, color);
    }

    ConsoleInputMode Console::GetConsoleInputMode()
    {
        return MinGetConsoleInputMode(cons.consoleInput);
    }

    bool Console::SetConsoleInputMode(ConsoleInputMode mode)
    {
        return MinSetConsoleInputMode(cons.consoleInput, mode);
    }

    ConsoleOutputMode Console::GetConsoleOutputMode()
    {
        return MinGetConsoleOutputMode(cons.consoleOutput);
    }

    bool Console::SetConsoleOutputMode(ConsoleOutputMode mode)
    {
        return MinSetConsoleOutputMode(cons.consoleOutput, mode);
    }

    ConsoleMode Console::GetConsoleMode()
    {
        ConsoleMode cm;
        MinGetConsoleMode(cons.consoleInput, cons.consoleOutput, &cm);
        return cm;
    }

    bool Console::SetConsoleMode(const ConsoleMode& consoleMode)
    {
        return MinSetConsoleMode(cons.consoleInput, cons.consoleOutput, consoleMode);
    }

    ConsoleFont Console::GetConsoleFont()
    {
        ConsoleFont consoleFont;
        MinGetConsoleFont(cons.consoleOutput, &consoleFont);
        return consoleFont;
    }

    bool Console::SetConsoleFont(const ConsoleFont& consoleFont)
    {
        return MinSetConsoleFont(cons.consoleOutput, consoleFont);
    }

    POINT Console::GetConsoleWindowSize()
    {
        POINT point;
        MinGetConsoleWindowSize(cons.consoleOutput, &point);
        return point;
    }

    bool Console::SetConsoleWindowSize(POINT size)
    {
        return MinSetConsoleWindowSize(cons.consoleOutput, size);
    }

    POINT Console::GetConsoleBufferSize()
    {
        POINT size;
        MinGetConsoleBufferSize(cons.consoleOutput, &size);
        return size;
    }

    bool Console::SetConsoleBufferSize(POINT size)
    {
        return MinSetConsoleBufferSize(cons.consoleOutput, size);
    }

    bool Console::CheckSize(POINT size)
    {
        return MinCheckSize(cons.consoleOutput, size);
    }

    void Console::SetConsoleWindowAndBufferSize(POINT size)
    {
        MinSetConsoleWindowAndBufferSize(cons.consoleOutput, size);
    }

    ConsoleColor Console::GetConsoleForeColor()
    {
        ConsoleColor foreColor;
        MinGetConsoleForeColor(cons.consoleOutput, &foreColor);
        return foreColor;
    }

    ConsoleColor Console::GetConsoleBackColor()
    {
        ConsoleColor backColor;
        MinGetConsoleBackColor(cons.consoleOutput, &backColor);
        return backColor;
    }

    bool Console::SetConsoleForeColor(ConsoleColor foreColor)
    {
        return MinSetConsoleForeColor(cons.consoleOutput, foreColor);
    }

    bool Console::SetConsoleBackColor(ConsoleColor backColor)
    {
        return MinSetConsoleBackColor(cons.consoleOutput, backColor);
    }

    bool Console::ResetConsoleColor()
    {
        return MinResetConsoleColor(this->cons.consoleOutput);
    }

    COORD Console::GetConsoleCursorPos()
    {
        COORD pos;
        MinGetConsoleCursorPos(cons.consoleOutput, &pos);
        return pos;
    }

    bool Console::SetConsoleCursorPos(COORD pos)
    {
        return MinSetConsoleCursorPos(cons.consoleOutput, pos);
    }

    std::wstring Console::ReadConsoleW()
    {
        wstring str;

        wchar buffer[sizeof(wchar) * MAX_INPUT_CHAR_COUNT] = { 0 };
        MinReadConsole(cons.consoleInput, buffer, MAX_INPUT_CHAR_COUNT);
        str = buffer;

        return str;
    }

    bool Console::ReadConsoleInputW(OnReadConsoleMouseInputRecord callback1, OnReadConsoleKeyboardInputRecord callback2, OnConsoleOutputBufferChanged callback3)
    {
        return MinReadConsoleInput(cons.consoleInput, callback1, callback2, callback3);
    }

    bool Console::ReadConsoleOneInput(OnReadConsoleMouseInputRecord callback1, OnReadConsoleKeyboardInputRecord callback2, OnConsoleOutputBufferChanged callback3)
    {
        return MinReadConsoleOneInput(cons.consoleInput, callback1, callback2, callback3);
    }

    bool Console::WriteConsoleW(const std::wstring& msg)
    {
        return MinWriteConsole(cons.consoleOutput, msg.c_str());
    }

    bool Console::WriteConsoleOutputW(const CHAR_INFO* charInfos, short x, short y, short width, short height)
    {
        return MinWriteConsoleOutput(cons.consoleOutput, charInfos, x, y, width, height);
    }

    bool Console::WriteConsoleOutputAttribute(const ushort* att, int attCount, COORD pos)
    {
        return MinWriteConsoleOutputAttribute(cons.consoleOutput, att, attCount, pos);
    }

    bool Console::WriteConsoleOutputCharacterW(const std::wstring& str, COORD pos)
    {
        return MinWriteConsoleOutputCharacter(cons.consoleOutput, str.c_str(), str.size(), pos);
    }

    bool Console::RefreshScreen(wchar c, ushort att)
    {
        return MinRefreshScreen(cons.consoleOutput, c, att);
    }

    bool Console::FlushConsoleInputBuffer()
    {
        return MinFlushConsoleInputBuffer(cons.consoleInput);
    }

    ConsoleSession Console::InitConsoleSession()
    {
        ConsoleSession cons;
        MinInitConsoleSession(&cons);
        return cons;
    }

    HANDLE Console::CreateConsoleScreenBuffer()
    {
        HANDLE consoleOutput;
        MinCreateConsoleScreenBuffer(&consoleOutput);
        return consoleOutput;
    }

    bool Console::SetConsoleActiveScreenBuffer(HANDLE consoleOutput)
    {
        return MinSetConsoleActiveScreenBuffer(consoleOutput);
    }

    bool Console::CloseConsoleScreenBuffer(HANDLE consoleOutput)
    {
        return MinCloseConsoleScreenBuffer(consoleOutput);
    }

    HANDLE Console::CreateFileW(ConsoleFile filemode)
    {
        HANDLE handle = nullptr;
        MinCreateFile(filemode, &handle);
        return handle;
    }

    bool Console::WriteFile(std::string str)
    {
        return MinWriteFile(cons.consoleOutput, str.c_str());
    }

    std::string Console::ReadFile()
    {
        char str[MAX_INPUT_CHAR_COUNT] = { 0 };
        MinReadFile(cons.consoleInput, str, MAX_INPUT_CHAR_COUNT);
        return string(str);
    }

    std::wstring Console::GetTitle()
    {
        wstring str;

        wchar titleBuffer[MAX_PATH];
        MinGetTitle(titleBuffer, LEN(titleBuffer));

        str = titleBuffer;
        return str;
    }

    bool Console::SetTitle(const std::wstring& title)
    {
        return MinSetTitle(title.c_str());
    }

    ConsoleType Console::GetConsoleType()
    {
        ConsoleType type;
        MinGetConsoleType(&type);
        return type;
    }

    bool Console::GetConsoleCursorVisible()
    {
        bool visible = false;
        MinGetConsoleCursorVisible(cons.consoleOutput, &visible);
        return visible;
    }

    bool Console::SetConsoleCursorVisible(bool visible)
    {
        return MinSetConsoleCursorVisible(cons.consoleOutput, visible);
    }

    bool Console::Clear()
    {
        return MinClear(cons.consoleOutput);
    }

    CharWidth Console::GetWcharWidth(wchar c)
    {
        CharWidth charWidth;
        MinGetCharWidth(cons.consoleWindow, cons.consoleOutput, c, &charWidth);
        return charWidth;
    }

    int Console::GetWstringWidth(const std::wstring& str)
    {
        int width = 0;
        MinGetStringWidth(cons.consoleWindow, cons.consoleOutput, str.c_str(), &width);
        return width;
    }

    bool Console::GetTreatControlCAsInput()
    {
        ConsoleMode consoleMode = GetConsoleMode();
        return !consoleMode.inputMode._ENABLE_PROCESSED_INPUT;
    }

    void Console::SetTreatControlCAsInput(bool yes)
    {
        ConsoleMode consoleMode = GetConsoleMode();
        consoleMode.inputMode._ENABLE_PROCESSED_INPUT = !yes;
        SetConsoleMode(consoleMode);
    }

    bool Console::SetConsoleCtrlHandler(PHANDLER_ROUTINE handler)
    {
        return MinSetConsoleCtrlHandler(handler, true);
    }

    bool Console::EnableConsoleVT()
    {
        return MinEnableConsoleVT(cons.consoleInput, cons.consoleOutput);
    }

    int Console::Read()
    {
        wstring str = Console::ReadConsoleW();
        size_t index = str.find_last_of(WNEW_LINE);
        wstring strWithOutNewLine = str.substr(0, index - 1);

        if (!strWithOutNewLine.empty()) return strWithOutNewLine[0];
        else return 0;
    }

    bool Console::KeyAvailable()
    {
        return ::_kbhit();
    }

    int Console::ReadKey(bool echo)
    {
        if (echo)
        {
            return ::_getche();
        }
        else
        {
            return ::_getch();
        }
    }

    std::wstring Console::ReadLine()
    {
        wstring str = Console::ReadConsoleW();

        if (str.find(WNEW_LINE) == str.size() - 2)
        {
            str = str.substr(0, str.size() - 2);
        }
        else
        {
            wchar lastChar = str[str.size() - 1];
            if (lastChar == L'\r' || lastChar == L'\n')
            {
                str = str.substr(0, str.size() - 1);
            }
        }
        return str;
    }

    bool Console::Write(const std::wstring& msg)
    {
        return Console::WriteConsoleW(msg);
    }

    bool Console::Write(const std::wstring& msg, ConsoleColor foreColor)
    {
        ConsoleColor fColor = Console::GetConsoleForeColor();
        Console::SetConsoleForeColor(foreColor);
        bool suc = Console::Write(msg);
        Console::SetConsoleForeColor(fColor);
        return suc;
    }

    bool Console::Write(const std::wstring& msg, ConsoleColor foreColor, ConsoleColor backColor)
    {
        ConsoleColor fColor = Console::GetConsoleForeColor();
        ConsoleColor bColor = Console::GetConsoleBackColor();
        Console::SetConsoleForeColor(foreColor);
        Console::SetConsoleBackColor(backColor);
        bool suc = Console::Write(msg);
        Console::SetConsoleForeColor(fColor);
        Console::SetConsoleBackColor(bColor);
        return suc;
    }

    bool Console::WriteLine()
    {
        return Console::Write(L"\n");
    }

    bool Console::WriteLine(const std::wstring& msg)
    {
        return Console::Write(msg + wstring(L"\n"));
    }

    bool Console::WriteLine(const std::wstring& msg, ConsoleColor foreColor)
    {
        return Console::Write(msg + wstring(L"\n"), foreColor);
    }

    bool Console::WriteLine(const std::wstring& msg, ConsoleColor foreColor, ConsoleColor backColor)
    {
        return Console::Write(msg + wstring(L"\n"), foreColor, backColor);
    }

    bool Console::Write(const std::wstring& msg, Color24 foreColor)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            return Console::Write(msg, fc);
        }

        wstring fore_str = VTConverter::VTForeColor(foreColor);
        wstring reset_str = VTConverter::VTResetStyle();
        return Console::Write(fore_str + msg + reset_str);
    }

    bool Console::Write(const std::wstring& msg, Color24 foreColor, Color24 backColor)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            ConsoleColor bc = backColor.ToConsoleColor();
            return Console::Write(msg, fc, bc);
        }

        wstring fore_str = VTConverter::VTForeColor(foreColor);
        wstring back_str = VTConverter::VTBackColor(backColor);
        wstring reset_str = VTConverter::VTResetStyle();
        return Console::Write(fore_str + back_str + msg + reset_str);
    }

    bool Console::Write(const std::wstring& msg, Color24 foreColor, Color24 backColor, bool under_score)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            ConsoleColor bc = backColor.ToConsoleColor();
            return Console::Write(msg, fc, bc);
        }

        wstring fore_str = VTConverter::VTForeColor(foreColor);
        wstring back_str = VTConverter::VTBackColor(backColor);
        wstring us_str = VTConverter::VTUnderline(under_score);
        wstring reset_str = VTConverter::VTResetStyle();
        return Console::Write(fore_str + back_str + us_str + msg + reset_str);
    }

    bool Console::WriteLine(const std::wstring& msg, Color24 foreColor)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            return Console::WriteLine(msg, fc);
        }

        return Console::Write(msg + wstring(L"\n"), foreColor);
    }

    bool Console::WriteLine(const std::wstring& msg, Color24 foreColor, Color24 backColor)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            ConsoleColor bc = backColor.ToConsoleColor();
            return Console::WriteLine(msg, fc, bc);
        }

        return Console::Write(msg + wstring(L"\n"), foreColor, backColor);
    }

    bool Console::WriteLine(const std::wstring& msg, Color24 foreColor, Color24 backColor, bool under_score)
    {
        if (!supportVT && !forceVT)
        {
            ConsoleColor fc = foreColor.ToConsoleColor();
            ConsoleColor bc = backColor.ToConsoleColor();
            return Console::WriteLine(msg, fc, bc);
        }

        return Console::Write(msg + wstring(L"\n"), foreColor, backColor, under_score);
    }

    ConsoleColor Color24::ToConsoleColor() const
    {
        bool isLegacy = PaletteSystem::Global.GetInstance().CurPaletteIsLegacyPalette();
        //Algorithm:https://stackoverflow.com/questions/1988833/converting-color-to-consolecolor
        if (isLegacy)
        {
            int index = (r > 128 || g > 128 || b > 128) ? 8 : 0; // Bright bit
            index |= (r > 64) ? 4 : 0; // Red bit
            index |= (g > 64) ? 2 : 0; // Green bit
            index |= (b > 64) ? 1 : 0; // Blue bit
            return (ConsoleColor)index;
        }
        else
        {
            return PaletteSystem::Global.GetInstance().GetCurPaletteClosestConsoleColor(*this);
        }
    }

    //The short name of the singleton
    Console& console = Console::Global.GetInstance();
}