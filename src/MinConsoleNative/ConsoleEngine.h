#pragma once

#include "MinDefines.h"
#include "Console.h"
#include "PaletteSystem.h"
#include <string>

namespace MinConsoleNative
{
    enum class FontSize
    {
        _6x12,
        _8x16,
        _10x20,
    };

    enum class ConsoleEngineException
    {
        WrongFontSize = 1,
    };

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