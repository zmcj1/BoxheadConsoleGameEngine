#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    GridRenderer renderer(10, 30, GridRendererMode::Fast);

    renderer.Clear();

    renderer.DrawWrap(Vector2::zero, L"墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙1234", { 255,0,0 }, { 0,0,0 }, false);

    renderer.Render();

    console.ReadLine();
    return 0;
}