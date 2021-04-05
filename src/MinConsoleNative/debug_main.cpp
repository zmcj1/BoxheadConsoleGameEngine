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
    cout << legacyCon << "\n\n\n";

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

    Timer timer;
    while (true)
    {
        timer.Start();
        Sleep(10);
        timer.Stop();
        double deltaTime = timer.Time();
        if (Input::GetKey('A'))
        {
            cout << Input::CheckKeyState(VK_CAPITAL) << "\n";
            cout << deltaTime << "\n";
        }
    }

    //for (size_t i = 0; i < 10; i++)
    //{
    //    uint v = Random::Range(0, 1);
    //    cout << v << "\n";
    //}

    cin.get();
    return 0;
}

#endif