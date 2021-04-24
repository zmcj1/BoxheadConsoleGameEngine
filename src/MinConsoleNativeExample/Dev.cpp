#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    int x = GetSystemMetrics(SM_CXSCREEN) / 2;
    int y = GetSystemMetrics(SM_CYSCREEN) / 2;

    Vector2 vec2(window.GetDesktopSize());
    vec2 = vec2 / 2;

    POINT point = window.GetCenterPosOfWindowInDesktop();
    return 0;
}