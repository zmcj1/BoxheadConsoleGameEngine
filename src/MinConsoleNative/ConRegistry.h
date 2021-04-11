#pragma once

#include "MinDefines.h"

namespace MinConsoleNative
{
    EXPORT_FUNC MinIsUsingLegacyConsole(_OUT_ bool* yes);

    EXPORT_FUNC MinUseLegacyConsole(_IN_ bool yes);

    EXPORT_FUNC_EX(bool) MinGetConsoleRegistryDWORD(const wchar* valueName, DWORD* data);

    EXPORT_FUNC_EX(bool) MinSetConsoleRegistryDWORD(const wchar* valueName, DWORD data);

    class ConRegistry
    {
    public:
        static bool IsUsingLegacyConsole();

        static bool UseLegacyConsole(bool yes);
    };
}