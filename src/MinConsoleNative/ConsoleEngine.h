#pragma once

#include "MinDefines.h"
#include "Console.h"
#include "PaletteSystem.h"
#include <string>

namespace MinConsoleNative
{
    enum class FontName
    {
        Terminal = 1,
        Consolas = 2,
    };

    enum class FontSize
    {
        _6x12,
        _8x16,
        _10x20,
    };

    enum class ConsoleEngineException
    {
        UnknownFontName = 1,
        UnknownFontSize = 2,
    };

    inline std::wstring GetFontName(FontName fontName)
    {
        switch (fontName)
        {
        case FontName::Terminal: return L"Terminal";
        case FontName::Consolas: return L"Consolas";
        }
        throw ConsoleEngineException::UnknownFontName;
    }

    inline POINT GetFontSize(FontSize fontSize)
    {
        switch (fontSize)
        {
        case FontSize::_6x12: return { 6, 12 };
        case FontSize::_8x16: return { 8, 16 };
        case FontSize::_10x20: return { 10, 20 };
        }
        throw ConsoleEngineException::UnknownFontSize;
    }

    class ConsoleEngine
    {
    public:
        std::wstring title = L"MinConsole Program";
        ConsoleType consoleType;

    private:
        bool running = false;
        float fpsTimer = 0.0f;
        const float fpsInterval = 0.25f;

    protected:
        virtual void OnStart();

        virtual void OnUpdate(float deltaTime);

        virtual void OnDestroy();

    public:
        ConsoleEngine();

        void ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight);

        void ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, FontSize fontSize);

        void ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight);

        void ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight, const std::wstring& fontName, int fontWeight);

        void ConstructTerminal(const std::wstring& title);

        //If fps is not a positive number, it means that there is no frame rate limit.
        void StartLoop(int fps = 0, bool disableConsoleCursor = true);

        void StopLoop();
    };
}