#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    enum class TextRendererMode
    {
        FastMode = 1,
        TrueColor = 2,
        Mixed = 3,
    };

    class TextRenderer
    {
    public:
        TextRendererMode rendererMode;

        TextRenderer();
    };
}