#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    GridRenderer renderer(10, 30, GridRendererMode::Mixed);

    renderer.Clear();

    renderer.DrawWrap(Vector2(2,2), L"墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙1234", { 177,0,0 }, { 0,0,0 }, false);

    renderer.DrawWrap(Vector2(9,10), L"吊", { 88,0,190 }, { 0,0,0 }, false);

    renderer.Render();

    console.ReadLine();
    return 0;
}