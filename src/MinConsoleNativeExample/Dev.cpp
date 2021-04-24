#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    ConsoleEngine ce;
    ce.ConstructConsole(L"dev", PaletteType::Legacy, 60, 30, FontSize::_10x20);
    console.ReadLine();

    int x = GetSystemMetrics(SM_CXSCREEN) / 2;
    int y = GetSystemMetrics(SM_CYSCREEN) / 2;

    Vector2 vec2(window.GetDesktopSize());
    vec2 = vec2 / 2;

    POINT point = window.GetCenterPosOfWindowInDesktop();
    return 0;
}