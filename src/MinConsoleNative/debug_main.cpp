#ifdef _DEBUG

#include "MinConsoleNative.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    POINT pos = Window::Global.GetInstance().GetCenterPosOfWindowInDesktop();
    Window::Global.GetInstance().SetWindowPos(pos);
    Console::Global.GetInstance().Clear();
    auto d = Console::Global.GetInstance().ReadLine();
    return 0;

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
}

#endif