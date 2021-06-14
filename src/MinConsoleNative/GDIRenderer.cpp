#include "GDIRenderer.h"

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinPutPixel(HWND hwnd, int x, int y, Color24 color)
    {
        HDC hdc = ::GetDC(hwnd);
        ::SetPixel(hdc, x, y, color.ToColorRef());
        return true;
    }

    bool GDIRenderer::PutPixel(int x, int y, Color24 color)
    {
        return MinPutPixel(console.cons.consoleWindow, x, y, color);
    }
}