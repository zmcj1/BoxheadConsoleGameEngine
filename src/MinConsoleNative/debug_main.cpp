#ifdef _DEBUG

#include "MinConsoleNative.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    Window window;
    POINT pos = window.GetCenterPosOfWindowInDesktop();
    window.SetWindowPos(pos);

    //bool legacyCon = ConRegistry::IsUsingLegacyConsole();
    //cout << legacyCon << "\n\n\n";

    //MinTimer timer;
    //MinInitTimer(&timer);
    //while (true)
    //{
    //    MinStartTimer(&timer);
    //    Sleep(10);
    //    double deltaTime = 0;
    //    MinStopTimer(&timer);
    //    MinTimeTimer(&timer, &deltaTime);
    //    cout << deltaTime << "\n";
    //}

    //Input::ResetMouseAxis();
    //Timer timer;
    //while (true)
    //{
    //    timer.Start();
    //    Sleep(100);
    //    timer.Stop();
    //    double deltaTime = timer.Time();
    //    Input::CheckMouseAxis();
    //    int diff = Input::GetMouseAxis(MouseAxis::MOUSE_X);
    //    cout << diff << "\n";
    //    if (Input::GetKeyDown('A'))
    //    {
    //        cout << deltaTime << "\n";
    //    }
    //}

    //for (size_t i = 0; i < 10; i++)
    //{
    //    uint v = Random::Range(0, 1);
    //    cout << v << "\n";
    //}

    Console console;
    //ConsoleFont cf = console.GetConsoleFont();
    //cf.FontSize = { 8,16 };
    //cf.SetFaceNameQuick(L"Consolas");
    //console.SetConsoleFont(cf);

    Database database;
    database.SetString(L"name", L"min");
    database.SetString(L"age", L"20");
    database.SetString(L"address", L"Moscow");
    database.SetString(L"gender", L"male");

    wstring a1 = database.GetString(L"name", DNULL);
    wstring a2 = database.GetString(L"age", DNULL);
    wstring a3 = database.GetString(L"address", DNULL);
    wstring a4 = database.GetString(L"gender", DNULL);

    Debug::Log(File::Combine(File::GetDirectoryPath(), L"log.txt"), L"hello world!");

    console.WriteConsoleW(VTConverter::Underline(true));

    console.WriteConsoleW(VTConverter::Color({ 255,55,66 }, { 0,11,189 }));

    console.WriteConsoleW(L"Hello World!\n");

    console.WriteConsoleW(VTConverter::ResetStyle());

    console.WriteConsoleW(L"Hello World!\n");

    console.WriteConsoleW(VTConverter::WindowTitle(L"adasASD1"));

    console.WriteConsoleW(VTConverter::CursorPos({ 10,5 }));

    console.WriteConsoleW(VTConverter::CursorVisible(false));

    console.WriteConsoleW(VTConverter::TerminalColor(36));

    console.WriteConsoleW(VTConverter::TerminalForeColor(TerminalColor::White));

    console.WriteConsoleW(VTConverter::TerminalBackColor(TerminalColor::Red));

    console.WriteConsoleW(L"Hello World!");

    console.ReadConsoleW();

    return 0;
}

#endif