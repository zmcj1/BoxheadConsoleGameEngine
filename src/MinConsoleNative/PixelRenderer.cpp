#include "PixelRenderer.h"

namespace MinConsoleNative
{
    PixelRenderer::PixelRenderer(Console& console, int consoleWidth, int consoleHeight, PixelRendererMode rendererMode) : console(console)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->rendererMode = rendererMode;
    }

    PixelRenderer::~PixelRenderer()
    {

    }
}