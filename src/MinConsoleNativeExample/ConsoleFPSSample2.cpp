#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    ConsoleFont consoleFont = console.GetConsoleFont();
    POINT consoleWindowSize = console.GetConsoleWindowSize();

    int targetClientWidth = consoleFont.FontSize.X * consoleWindowSize.x;
    int targetClientHeight = consoleFont.FontSize.Y * consoleWindowSize.y;

    POINT realClientSize = window.GetClientSize();

    float realConsoleFontX = (float)realClientSize.x / consoleWindowSize.x;
    float realConsoleFontY = (float)realClientSize.y / consoleWindowSize.y;

    console.ReadLine();
    return 0;
}