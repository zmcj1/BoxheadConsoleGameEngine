#include "PaletteSystem.hpp"

namespace MinConsoleNative
{
    PaletteSystem::PaletteSystem()
    {
        ConsolePalette legacyPalette;
        ConsolePalette modernPalette;

        legacyPalette.consolePalette[ConsoleColor::BLACK] = { 0, 0, 0 };
        legacyPalette.consolePalette[ConsoleColor::DARKBLUE] = { 0, 0, 128 };
        legacyPalette.consolePalette[ConsoleColor::DARKGREEN] = { 0, 128, 0 };
        legacyPalette.consolePalette[ConsoleColor::DARKCYAN] = { 0, 128, 128 };
        legacyPalette.consolePalette[ConsoleColor::DARKRED] = { 128, 0, 0 };
        legacyPalette.consolePalette[ConsoleColor::DARKMAGENTA] = { 128, 0, 128 };
        legacyPalette.consolePalette[ConsoleColor::DARKYELLOW] = { 128, 128, 0 };
        legacyPalette.consolePalette[ConsoleColor::GRAY] = { 192, 192, 192 };
        legacyPalette.consolePalette[ConsoleColor::DARKGRAY] = { 128, 128, 128 };
        legacyPalette.consolePalette[ConsoleColor::BLUE] = { 0, 0, 255 };
        legacyPalette.consolePalette[ConsoleColor::GREEN] = { 0, 255, 0 };
        legacyPalette.consolePalette[ConsoleColor::CYAN] = { 0, 255, 255 };
        legacyPalette.consolePalette[ConsoleColor::RED] = { 255, 0, 0 };
        legacyPalette.consolePalette[ConsoleColor::MAGENTA] = { 255, 0, 255 };
        legacyPalette.consolePalette[ConsoleColor::YELLOW] = { 255, 255, 0 };
        legacyPalette.consolePalette[ConsoleColor::WHITE] = { 255, 255, 255 };

        modernPalette.consolePalette[ConsoleColor::BLACK] = { 12, 12, 12 };
        modernPalette.consolePalette[ConsoleColor::DARKBLUE] = { 0, 55, 218 };
        modernPalette.consolePalette[ConsoleColor::DARKGREEN] = { 19, 161, 14 };
        modernPalette.consolePalette[ConsoleColor::DARKCYAN] = { 58, 150, 221 };
        modernPalette.consolePalette[ConsoleColor::DARKRED] = { 197, 15, 31 };
        modernPalette.consolePalette[ConsoleColor::DARKMAGENTA] = { 136, 23, 152 };
        modernPalette.consolePalette[ConsoleColor::DARKYELLOW] = { 193, 156, 0 };
        modernPalette.consolePalette[ConsoleColor::GRAY] = { 204, 204, 204 };
        modernPalette.consolePalette[ConsoleColor::DARKGRAY] = { 118, 118, 118 };
        modernPalette.consolePalette[ConsoleColor::BLUE] = { 59, 120, 255 };
        modernPalette.consolePalette[ConsoleColor::GREEN] = { 22, 198, 12 };
        modernPalette.consolePalette[ConsoleColor::CYAN] = { 97, 214, 214 };
        modernPalette.consolePalette[ConsoleColor::RED] = { 231, 72, 86 };
        modernPalette.consolePalette[ConsoleColor::MAGENTA] = { 180, 0, 158 };
        modernPalette.consolePalette[ConsoleColor::YELLOW] = { 249, 241, 165 };
        modernPalette.consolePalette[ConsoleColor::WHITE] = { 242, 242, 242 };

        this->palettes[PaletteType::Legacy] = legacyPalette;
        this->palettes[PaletteType::Modern] = modernPalette;
        this->curPalette = GetConsolePalette();
    }

    Color24 PaletteSystem::GetCurrentConsolePaletteColor(DWORD index)
    {
        return this->curPalette.consolePalette[(ConsoleColor)index];
    }

    bool PaletteSystem::SetCurrentConsolePaletteColor(DWORD index, const Color24& color)
    {
        bool suc = Console::Global.GetInstance().SetConsolePalette(index, color);
        if (suc)
        {
            this->curPalette.consolePalette[(ConsoleColor)index] = color;
        }
        return suc;
    }

    ConsolePalette PaletteSystem::GetConsolePalette()
    {
        ConsolePalette consolePalette;
        for (int i = 0; i < WINCON_PALETTE_COLOR_LIMIT; i++)
        {
            Color24 color = Console::Global.GetInstance().GetConsolePalette((DWORD)i);
            consolePalette.consolePalette[(ConsoleColor)i] = color;
        }
        return consolePalette;
    }

    bool PaletteSystem::SetConsolePalette(ConsolePalette consolePalette)
    {
        bool suc = true;
        for (int i = 0; i < WINCON_PALETTE_COLOR_LIMIT; i++)
        {
            Color24 color = consolePalette.consolePalette[(ConsoleColor)i];
            suc &= Console::Global.GetInstance().SetConsolePalette(i, color);
        }
        return suc;
    }

    bool PaletteSystem::CurPaletteIsLegacyPalette()
    {
        return this->curPalette == this->palettes[PaletteType::Legacy];
    }

    ConsoleColor PaletteSystem::GetCurPaletteClosestConsoleColor(const Color24& color)
    {
        ConsoleColor result = ConsoleColor::BLACK;
        double r = color.r;
        double g = color.g;
        double b = color.b;
        double delta = std::numeric_limits<double>::max(); //MAX_DOUBLE
        for (int i = 0; i < WINCON_PALETTE_COLOR_LIMIT; i++)
        {
            ConsoleColor consoleColor = (ConsoleColor)i;
            Color24 c = GetCurrentConsolePaletteColor(i);
            double t = pow(c.r - r, 2.0) + pow(c.g - g, 2.0) + pow(c.b - b, 2.0);
            if (t == 0.0)
            {
                return consoleColor;
            }
            else if (t < delta)
            {
                delta = t;
                result = consoleColor;
            }
        }
        return result;
    }

    PaletteSystem& paletteSystem = PaletteSystem::Global.GetInstance();
}