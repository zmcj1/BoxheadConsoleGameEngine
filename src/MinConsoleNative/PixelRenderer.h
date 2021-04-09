#pragma once

#include "MinDefines.h"
#include "Console.h"

namespace MinConsoleNative
{
    enum class PixelRendererMode
    {
        FastMode = 1,
        TrueColor = 2,
        Mixed = 3,
    };

    class PixelRenderer
    {
    public:
        Console& console;
        int consoleWidth;
        int consoleHeight;
        PixelRendererMode rendererMode;

        PixelRenderer(Console& console, int consoleWidth, int consoleHeight, PixelRendererMode rendererMode);

        ~PixelRenderer();


    };
}