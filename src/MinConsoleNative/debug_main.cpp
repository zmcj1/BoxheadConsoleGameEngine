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

    //Console console;
    //ConsoleFont cf = console.GetConsoleFont();
    //cf.FontSize = { 8,16 };
    //cf.SetFaceNameQuick(L"Consolas");
    //console.SetConsoleFont(cf);

    wstring wstr = String::Trim(L" _  _ _  ");
    wstr = String::TrimStart(L"  sd   ");
    wstr = String::TrimEnd(L" aasda  ");

    cin.get();
    return 0;
}

#endif