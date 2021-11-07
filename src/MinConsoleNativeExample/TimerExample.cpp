#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    MinTimer timer = MinInitTimer();

    double deltaTime = 0;
    while (true)
    {
        MinStartTimer(&timer);
        Sleep(100);
        MinStopTimer(&timer);
        deltaTime = MinTimeTimer(&timer, 1000);
        console.WriteLine(std::to_wstring(deltaTime));
    }

    return 0;
}