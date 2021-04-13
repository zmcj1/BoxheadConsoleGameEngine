#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <map>
#include <vector>

namespace MinConsoleNative
{
    //color count limit
    constexpr int WINCON_PALETTE_COLOR_LIMIT = 16;

    enum class PaletteType
    {
        Legacy = 1,
        Modern = 2,
    };

    class ConsolePalette
    {
    public:
        std::map<ConsoleColor, Color24> consolePalette;
    };

    class PaletteSystem
    {
    public:
        std::map<PaletteType, ConsolePalette> palettes;

        PaletteSystem();

        ConsolePalette GetCurrentConsolePalette();

        bool SetCurrentConsolePalette(PaletteType type);
    };
}