#include "MinConsoleNative.hpp"

using namespace std;

int main()
{
    console.SetConsoleCursorVisible(false);
    console.SetConsoleWindowAndBufferSize({ 120, 30 });

    int consoleWidth = console.GetConsoleWindowSize().x;
    int consoleHeight = console.GetConsoleWindowSize().y;

    CellRenderer renderer(consoleWidth, consoleHeight, CellRendererMode::TrueColor);
    renderer.Clear();
    //出于未知原因，禁止在右下角打印的限制被解除了
    //同时Console打印的时候也显示正常
    for (size_t i = 0; i < consoleWidth * consoleHeight; i++)
    {
        console.Write(L"大");
    }
    renderer.Render();
    console.ReadLine();
    return 0;
}