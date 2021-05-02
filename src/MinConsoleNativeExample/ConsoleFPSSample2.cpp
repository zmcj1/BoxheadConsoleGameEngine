#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    NativeRenderer::defaultCharInfo = { L' ', 0x30 };
    NativeRenderer renderer(30, 30);
    renderer.Clear();
    renderer.Draw({ 3, 2 }, { L'A', 0x70 });
    renderer.DrawString({ 4, 3 }, L"hello world!1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    renderer.DrawString2({ 4, 4 }, L"你好世界1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    renderer.Render();
    console.ReadLine();
    return 0;
}