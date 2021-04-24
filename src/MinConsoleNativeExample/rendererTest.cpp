#include "..\MinConsoleNative\MinConsoleNative.h"

int main()
{
    GridRenderer renderer(60, 30, GridRendererMode::Fast);

    renderer.Clear();

    renderer.Draw(Vector2::zero, L"rushB冲冲冲asaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊!!!", { 255,0,0 }, { 0,0,0 }, false);

    renderer.Render();

    console.ReadLine();
    return 0;
}