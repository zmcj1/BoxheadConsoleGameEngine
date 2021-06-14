#pragma once

#include "MinDefines.h"
#include "Console.h" //color24

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinPutPixel(HWND hwnd, int x, int y, Color24 color);

    class GDIRenderer
    {
    public:
        static bool PutPixel(int x, int y, Color24 color);
    };
}