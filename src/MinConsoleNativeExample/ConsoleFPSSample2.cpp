#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    NativeRenderer::defaultCharInfo = { L' ', 0x30 };
    NativeRenderer renderer(30, 30);
    renderer.Clear();
    renderer.DrawStringWrap({ 29, 5 }, L"hello world!1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    renderer.DrawString2Wrap({ 26, 3 }, L"你好世界1356", ConsoleColor::RED, ConsoleColor::BLACK, true);
    renderer.Render();
    console.ReadLine();
    return 0;
}