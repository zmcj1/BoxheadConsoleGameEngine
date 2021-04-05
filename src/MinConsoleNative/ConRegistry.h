#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    EXPORT_FUNC MinIsUsingLegacyConsole(bool* yes);

    EXPORT_FUNC MinUseLegacyConsole(bool yes);

    class ConRegistry
    {
    public:
        static bool IsUsingLegacyConsole();

        static bool UseLegacyConsole(bool yes);
    };
}