#include "MinConsoleNative.hpp"
#include <string>
using namespace std;

bool SetConsoleFontCheck(int consoleWidth, int consoleHeight, int fontWidth, int fontHeight)
{
//#define OLC
#ifndef OLC
    ConsoleFont consoleFont;
    consoleFont.FontFamily = FF_DONTCARE;
    consoleFont.FontWeight = FW_NORMAL;
    consoleFont.SetFontName(L"Consolas");
    consoleFont.SetFontWidth(fontWidth);
    consoleFont.SetFontHeight(fontHeight);
    console.SetConsoleFont(consoleFont);

    console.SetConsoleWindowAndBufferSize({ consoleWidth, consoleHeight });

    while (true)
    {
        if (Input::GetKey('A'))
        {
            POINT windowSize = window.GetClientSize();
            int gx = windowSize.x / fontWidth;
            int gy = windowSize.y / fontHeight;

            //Debug::OutputLine(to_wstring(windowSize.x) + L" " + to_wstring(windowSize.y));
            Debug::OutputLine(to_wstring(gx) + L" " + to_wstring(gy));
            //console.WriteLine(to_wstring(windowSize.x) + L" " + to_wstring(windowSize.y));
        }
        Sleep(100);
    }
    return true;
#else
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontWidth;
    cfi.dwFontSize.Y = fontHeight;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");

    if (!SetCurrentConsoleFontEx(console.cons.consoleOutput, false, &cfi))
        throw "error";

    console.SetConsoleWindowAndBufferSize({ consoleWidth, consoleHeight });
    while (true)
    {
        if (Input::GetKey('A'))
        {
            POINT windowSize = window.GetClientSize();
            int gx = windowSize.x / fontWidth;
            int gy = windowSize.y / fontHeight;

            //Debug::OutputLine(to_wstring(windowSize.x) + L" " + to_wstring(windowSize.y));
            Debug::OutputLine(to_wstring(gx) + L" " + to_wstring(gy));
            //console.WriteLine(to_wstring(windowSize.x) + L" " + to_wstring(windowSize.y));
        }
        Sleep(100);
    }

    return true;
#endif
}

int main()
{
    bool suc = SetConsoleFontCheck(320, 180, 4, 4);
    wstring wstr = String::BoolToWstring(suc);
    console.WriteLine(wstr);
    console.ReadLine();
    return 0;
}