#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    //CellRenderer cr(60, 30, CellRendererMode::Mixed);
    //cr.Clear();
    //cr.Draw({ 59,29 }, Cell(L'a', { 255,0,0 }, { 0,0,0 }, true));
    //cr.Render();
    //console.ReadLine();
    //return 0;

    GridRenderer renderer(10, 30, GridRendererMode::Fast);
    renderer.Clear();
    renderer.DrawStringWrap(Vector2(2, 2), L"墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙1234", { 177,0,0 }, { 0,0,0 }, true);
    renderer.DrawStringWrap(Vector2(9, 10), L"吊", { 88,0,190 }, { 0,0,0 }, false);
    renderer.Render();
    console.ReadLine();
    return 0;
}