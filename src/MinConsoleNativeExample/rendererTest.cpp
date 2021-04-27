#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    CellRenderer cr(60, 30, CellRendererMode::Mixed);
    cr.Clear();
    cr.Draw(Vector2(2, 2), Cell(L'a', { 188,0,0 }, { 0,0,0 }, false));
    cr.Render();
    console.ReadLine();
    return 0;

    GridRenderer renderer(10, 30, GridRendererMode::Fast);

    renderer.Clear();

    renderer.DrawWrap(Vector2(2, 2), L"墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙1234", { 177,0,0 }, { 0,0,0 }, true);

    renderer.DrawWrap(Vector2(9, 10), L"吊", { 88,0,190 }, { 0,0,0 }, false);

    renderer.Render();

    console.ReadLine();
    return 0;
}