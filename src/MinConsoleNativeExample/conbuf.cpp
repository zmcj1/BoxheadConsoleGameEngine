#include "MinConsoleNative.hpp"

int main()
{
    HANDLE oldBuf = MinGetStdHandle(StdHandleType::Output);
    HANDLE newBuf = MinCreateConsoleScreenBuffer();
    console.SetConsoleActiveScreenBuffer(newBuf);

    ConsoleFont cf = MinGetConsoleFont(newBuf);
    cf.SetFontName(L"Consolas");
    cf.FontSize = { 4, 4 };
    MinSetConsoleFont(newBuf, cf);
    MinSetConsoleWindowAndBufferSize(newBuf, { 120, 30 });
    Sleep(200);

    POINT windowSize = window.GetClientSize();
    int x = windowSize.x / 4;
    int y = windowSize.y / 4;

    windowSize = window.GetClientSize();
    x = windowSize.x / 6;
    y = windowSize.y / 12;

    Console newConsole;
    newConsole.cons.consoleOutput = newBuf;
    newConsole.SetConsoleWindowAndBufferSize({ x, y });



    console.ReadLine();

    console.FlushConsoleInputBuffer();

    console.SetConsoleActiveScreenBuffer(oldBuf);

    cf.FontSize = { 6, 12 };
    MinSetConsoleFont(oldBuf, cf);
    MinSetConsoleWindowAndBufferSize(oldBuf, { x, y });


    console.ReadLine();
    return 0;
}