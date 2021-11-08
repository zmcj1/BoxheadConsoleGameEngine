#include "..\MinConsoleNative\MinConsoleNative.h"
#include "Stopwatch.h"

#define SW32

int main()
{
#if defined(SW32)
    win32::Stopwatch sw;
    while (true)
    {
        sw.Start();
        Sleep(100);
        sw.Stop();
        double dt = sw.ElapsedMilliseconds();
        console.WriteLine(std::to_wstring(dt));
    }
#else
    MinTimer timer = MinInitTimer();
    while (true)
    {
        MinStartTimer(&timer);
        Sleep(100);
        MinStopTimer(&timer);
        double deltaTime = MinTimeTimer(&timer, 1000);
        console.WriteLine(std::to_wstring(deltaTime));
    }
#endif

    return 0;
}