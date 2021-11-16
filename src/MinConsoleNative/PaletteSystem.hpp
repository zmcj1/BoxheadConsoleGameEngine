#pragma once

#include "MinDefines.hpp"
#include "Console.hpp"
#include "Singleton.hpp"
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

        bool operator ==(ConsolePalette& other)
        {
            bool equal = true;
            equal &= this->consolePalette[ConsoleColor::BLACK] == other.consolePalette[ConsoleColor::BLACK];
            equal &= this->consolePalette[ConsoleColor::DARKBLUE] == other.consolePalette[ConsoleColor::DARKBLUE];
            equal &= this->consolePalette[ConsoleColor::DARKGREEN] == other.consolePalette[ConsoleColor::DARKGREEN];
            equal &= this->consolePalette[ConsoleColor::DARKCYAN] == other.consolePalette[ConsoleColor::DARKCYAN];
            equal &= this->consolePalette[ConsoleColor::DARKRED] == other.consolePalette[ConsoleColor::DARKRED];
            equal &= this->consolePalette[ConsoleColor::DARKMAGENTA] == other.consolePalette[ConsoleColor::DARKMAGENTA];
            equal &= this->consolePalette[ConsoleColor::DARKYELLOW] == other.consolePalette[ConsoleColor::DARKYELLOW];
            equal &= this->consolePalette[ConsoleColor::GRAY] == other.consolePalette[ConsoleColor::GRAY];
            equal &= this->consolePalette[ConsoleColor::DARKGRAY] == other.consolePalette[ConsoleColor::DARKGRAY];
            equal &= this->consolePalette[ConsoleColor::BLUE] == other.consolePalette[ConsoleColor::BLUE];
            equal &= this->consolePalette[ConsoleColor::GREEN] == other.consolePalette[ConsoleColor::GREEN];
            equal &= this->consolePalette[ConsoleColor::CYAN] == other.consolePalette[ConsoleColor::CYAN];
            equal &= this->consolePalette[ConsoleColor::RED] == other.consolePalette[ConsoleColor::RED];
            equal &= this->consolePalette[ConsoleColor::MAGENTA] == other.consolePalette[ConsoleColor::MAGENTA];
            equal &= this->consolePalette[ConsoleColor::YELLOW] == other.consolePalette[ConsoleColor::YELLOW];
            equal &= this->consolePalette[ConsoleColor::WHITE] == other.consolePalette[ConsoleColor::WHITE];
            return equal;
        }
    };

    class PaletteSystem
    {
    public:
        static Singleton<PaletteSystem> Global;

    public:
        ConsolePalette curPalette; //current console palette
        std::map<PaletteType, ConsolePalette> palettes; //include 2 default palettes

        PaletteSystem();

        Color24 GetCurrentConsolePaletteColor(DWORD index);

        bool SetCurrentConsolePaletteColor(DWORD index, const Color24& color);

        ConsolePalette GetConsolePalette();

        bool SetConsolePalette(ConsolePalette consolePalette);

        bool CurPaletteIsLegacyPalette();

        //FROM:https://stackoverflow.com/questions/1988833/converting-color-to-consolecolor
        ConsoleColor GetCurPaletteClosestConsoleColor(const Color24& color);
    };

    extern PaletteSystem& paletteSystem;
}