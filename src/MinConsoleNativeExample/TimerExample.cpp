#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    MinTimer timer;
    MinInitTimer(&timer);
    double deltaTime = 0;
    while (true)
    {
        MinStartTimer(&timer);
        Sleep(100);
        MinStopTimer(&timer);
        MinTimeTimer(&timer, &deltaTime, 1000);
        console.WriteLine(std::to_wstring(deltaTime));
    }

    return 0;
}