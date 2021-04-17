﻿#include "ConsoleEngine.h"
#include "Debug.h"
#include "Timer.h"
#include "Window.h"

namespace MinConsoleNative
{
    void ConsoleEngine::OnStart()
    {
    }

    void ConsoleEngine::OnUpdate(float deltaTime)
    {
    }

    void ConsoleEngine::OnDestroy()
    {
    }

    void ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight)
    {
        //Before setting the font, you must first set the console palette and console mode
        if (PaletteSystem::Global.GetInstance().palettes.count(paletteType) != 0)
        {
            ConsolePalette consolePalette = PaletteSystem::Global.GetInstance().palettes[paletteType];
            PaletteSystem::Global.GetInstance().SetConsolePalette(consolePalette);
        }

        //Set console mode
        ConsoleMode cm = ConsoleMode::Standard();
        Console::Global.GetInstance().SetConsoleMode(cm);

        //Set console font
        ConsoleFont consoleFont = Console::Global.GetInstance().GetConsoleFont();
        consoleFont.SetFontWidth(fontWidth);
        consoleFont.SetFontHeight(fontHeight);
        Console::Global.GetInstance().SetConsoleFont(consoleFont);

        //Set console title
        Console::Global.GetInstance().SetTitle(title);

        //check the size, this is important!
        POINT size = { consoleWidth, consoleHeight };
        bool suc = Console::Global.GetInstance().CheckSize(size);
        if (!suc)
        {
            std::wstring errMsg = Debug::GetLastMinErrorMsg();
            Console::Global.GetInstance().WriteLine(errMsg, ConsoleColor::RED);
            Console::Global.GetInstance().ReadLine();
            ::ExitProcess(0);
        }

        //At last:Set console window and buffer size.
        Console::Global.GetInstance().SetConsoleWindowAndBufferSize(size);

        //Wait for the window adjustment, I think we should disable Position the window by the system in registry.
        ::Sleep(100);

        //Set the window position
        POINT centerPos = Window::Global.GetInstance().GetCenterPosOfWindowInDesktop();
        Window::Global.GetInstance().SetWindowPos(centerPos);
    }

    void ConsoleEngine::ConstructTerminal(const std::wstring& title)
    {

    }

    void ConsoleEngine::StartLoop(int fps, bool disableConsoleCursor)
    {
        this->running = true;

        //The time that should be consumed per frame(milli-second).
        double tickTime = 0.0;
        if (fps > 0)
        {
            tickTime = static_cast<double>(1000) / fps;
        }

        Timer timer;
        double dt = 0; //(milli-second)

        //Initialization
        this->OnStart();

        while (this->running)
        {
            timer.Start();

            //What is the use of the code?
            //After testing, the cursor will reappear after the console window size changes, which seems to be a bug.
            if (disableConsoleCursor)
            {
                Console::Global.GetInstance().SetConsoleCursorVisible(false);
            }

            //update logic every frame here
            float deltaTime = (float)dt / 1000.0f;
            this->OnUpdate(deltaTime);

            timer.Stop();
            dt = timer.Time();

            //Control frame rate
            while (dt < tickTime)
            {
                ::Sleep(0); //yield return
                timer.Stop();
                dt = timer.Time();
            }
        }

        //Recycling resources
        this->OnDestroy();
    }

    void ConsoleEngine::StopLoop()
    {
        this->running = false;
    }
}