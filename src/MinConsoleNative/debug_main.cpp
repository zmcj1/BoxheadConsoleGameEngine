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

    bool legacyCon = ConRegistry::IsUsingLegacyConsole();
    cout << legacyCon;

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

    //Timer timer;
    //while (true)
    //{
    //    timer.Start();
    //    Sleep(10);
    //    timer.Stop();
    //    double deltaTime = timer.Time();
    //    cout << deltaTime << "\n";
    //}

    cin.get();
    return 0;
}

#endif