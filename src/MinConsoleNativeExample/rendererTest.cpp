#include "MinConsoleNative.hpp"

int main()
{
    CellRenderer cr(30, 30, CellRendererMode::TrueColor);
    cr.Clear();
    cr.Draw({ 29, 29 }, Cell(L'a', { 255,0,0 }, { 0,0,0 }, true));
    cr.DrawStringWrap({ 20, 10 }, L"asdaasaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", { 255,0,0 }, { 0,0,0 }, true);
    cr.DrawString2Wrap({ 20, 20 }, L"askd的艰苦拉萨大家看来急啊抗衰老登陆看看奥斯卡大奖", { 255,0,0 }, { 0,0,0 }, true);
    cr.DrawBorderBox({ 0,0 }, { 15,15 }, { 1,1 }, Cell(L'0', { 0,255,0 }), Cell(L'#', { 255,0,0 }));
    cr.DrawBorderBox2({ 2,0 }, { 10,10 }, { 1,1 }, L"内", { 0,0,255 }, { 0,0,0 }, false, L"墙", { 255,0,0 }, { 0,0,0 }, false);
    cr.Render();
    console.ReadLine();

    GridRenderer renderer(10, 30, GridRendererMode::Fast);
    renderer.Clear();
    renderer.DrawStringWrap(Vector2(2, 2), L"墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙墙1234", { 177,0,0 }, { 0,0,0 }, true);
    renderer.DrawStringWrap(Vector2(9, 10), L"吊", { 88,0,190 }, { 0,0,0 }, false);
    renderer.Render();
    console.ReadLine();

    NativeRenderer nrenderer(30, 30);
    nrenderer.Clear({ L' ', 0x30 });
    nrenderer.DrawString({ 28, 2 }, L"hello world!1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    nrenderer.DrawStringWrap({ 28, 4 }, L"hello world!1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    nrenderer.DrawString2({ 26, 6 }, L"你好世界1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    nrenderer.DrawString2Wrap({ 26, 8 }, L"你好世界1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    nrenderer.Render();
    console.ReadLine();

    return 0;
}