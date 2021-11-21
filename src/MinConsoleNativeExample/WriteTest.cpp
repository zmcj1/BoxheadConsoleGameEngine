#include "MinConsoleNative.hpp"

using namespace std;

int main()
{
    //ConsoleOutputMode mode = ConsoleOutputMode::Standard();
    //console.SetConsoleOutputMode(mode);

    HANDLE oldBuffer = console.cons.consoleOutput;
    HANDLE newBuffer = console.CreateConsoleScreenBuffer();

    console.SetConsoleCursorVisible(false);
    console.SetConsoleWindowAndBufferSize({ 120, 30 });

    int consoleWidth = console.GetConsoleWindowSize().x;
    int consoleHeight = console.GetConsoleWindowSize().y;

    wstring wstr1;
    wstring wstr2;

    for (int i = 0; i < consoleHeight; i++)
    {
        for (int j = 0; j < consoleWidth; j++)
        {
            wstr1 += L"1";
            wstr2 += L"2";
        }
    }

    while (true)
    {
        if (Input::GetKey('A'))
        {
            console.Write(wstr1, { 255,0,0 });
        }
        else
        {
            console.Write(wstr2, { 0,0,255 });
        }
        Sleep(20);

        ////双缓冲技术
        //MinANSIWrite2(oldBuffer, wstr1.c_str(), { 255,0,0 });
        //console.SetConsoleActiveScreenBuffer(oldBuffer);
        //Sleep(500);
        //MinANSIWrite2(newBuffer, wstr2.c_str(), { 0,0,255 });
        //console.SetConsoleActiveScreenBuffer(newBuffer);
        //Sleep(500);
    }

    return 0;
}