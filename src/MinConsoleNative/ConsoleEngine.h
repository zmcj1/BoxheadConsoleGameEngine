#pragma once

#include "MinDefines.h"
#include "Console.h"
#include "PaletteSystem.h"
#include <string>

namespace MinConsoleNative
{
    class ConsoleEngine
    {
    private:
        bool running = false;

    protected:
        virtual void OnStart();

        virtual void OnUpdate(float deltaTime);

        virtual void OnDestroy();

    public:
        void ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight);

        void ConstructTerminal(const std::wstring& title);

        //If fps is not a positive number, it means that there is no frame rate limit.
        void StartLoop(int fps = 0, bool disableConsoleCursor = true);

        void StopLoop();
    };
}