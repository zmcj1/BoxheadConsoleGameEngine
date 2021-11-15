#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    CHAR_INFO cells[6];
    for (int i = 0; i < 6; i++)
    {
        if (i % 2 == 0)
        {
            cells[i].Char.UnicodeChar = L'大';
            cells[i].Attributes = MinConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::GREEN) |
                COMMON_LVB_LEADING_BYTE;
        }
        else
        {
            cells[i].Char.UnicodeChar = L'\0';
            cells[i].Attributes = MinConsoleColorToUshort(ConsoleColor::RED, ConsoleColor::GREEN) |
                COMMON_LVB_TRAILING_BYTE;
        }
        cells[i].Attributes |= COMMON_LVB_UNDERSCORE;
    }
    Console::Global.GetInstance().WriteConsoleOutputW(cells, 0, 0, 6, 1);
    Console::Global.GetInstance().ReadLine();
    return 0;
}