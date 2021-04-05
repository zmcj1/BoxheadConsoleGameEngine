#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    EXPORT_FUNC IsLegacyConsole(bool* yes);

    class ConRegistry
    {
    public:
        static bool IsUseLegacyConsole();
    };
}