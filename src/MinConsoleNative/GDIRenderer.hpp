#pragma once

#include "MinDefines.hpp"
#include "Console.hpp" //color24

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinPutPixel(HWND hwnd, int x, int y, Color24 color);

    class GDIRenderer
    {
    private:
        GDIRenderer()
        {
        }

    public:
        static bool PutPixel(int x, int y, Color24 color);
    };
}