#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    //test in Windows Terminal:
    int fx = console.GetConsoleFont().FontSize.X; //this value will always be 0 in WT.
    int fy = console.GetConsoleFont().FontSize.Y;
    console.WriteLine(to_wstring(fx) + L" " + to_wstring(fy));
    int ww = console.GetConsoleWindowSize().x;
    int wh = console.GetConsoleWindowSize().y;
    console.WriteLine(to_wstring(ww) + L" " + to_wstring(wh));
    console.ReadLine();
    console.Clear();

    ConsoleFont consoleFont = console.GetConsoleFont();
    POINT consoleWindowSize = console.GetConsoleWindowSize();

    int targetClientWidth = consoleFont.FontSize.X * consoleWindowSize.x;
    int targetClientHeight = consoleFont.FontSize.Y * consoleWindowSize.y;

    POINT realClientSize = window.GetClientSize();

    float realConsoleFontX = (float)realClientSize.x / consoleWindowSize.x;
    float realConsoleFontY = (float)realClientSize.y / consoleWindowSize.y;
    console.WriteLine(to_wstring(realConsoleFontX) + L" " + to_wstring(realConsoleFontY));
    console.ReadLine();
    return 0;
}