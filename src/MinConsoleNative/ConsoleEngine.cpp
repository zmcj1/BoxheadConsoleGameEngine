#include "ConsoleEngine.h"
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
        this->fpsTimer += deltaTime;
        if (this->fpsTimer >= this->fpsInterval)
        {
            this->fpsTimer = 0.0f;
            //Show FPS in the title bar
            wchar_t newTitle[MAX_PATH];
            swprintf_s(newTitle, MAX_PATH, _T("%s - FPS: %3.2f"), this->title.c_str(), 1.0f / deltaTime);
            //this API works in Windows Terminal :)
            Console::Global.GetInstance().SetTitle(newTitle);
        }
    }

    void ConsoleEngine::OnDestroy()
    {
    }

    ConsoleEngine::ConsoleEngine()
    {
        this->consoleType = Console::Global.GetInstance().GetConsoleType();
    }

    void ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight)
    {
        ConsoleFont consoleFont = console.GetConsoleFont();
        ConsoleEngine::ConstructConsole(title, paletteType, consoleWidth, consoleHeight, consoleFont.FontSize.X, consoleFont.FontSize.Y);
    }

    void ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, FontSize fontSize)
    {
        POINT size = GetFontSize(fontSize);
        int fontWidth = size.x;
        int fontHeight = size.y;
        ConsoleEngine::ConstructConsole(title, paletteType, consoleWidth, consoleHeight, fontWidth, fontHeight);
    }

    void ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight)
    {
        this->title = title;

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

    void ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight, const std::wstring& fontName, int fontWeight)
    {
        ConsoleFont consoleFont = Console::Global.GetInstance().GetConsoleFont();
        consoleFont.FontWeight = (uint)fontWeight;
        consoleFont.SetFontName(fontName);
        Console::Global.GetInstance().SetConsoleFont(consoleFont);

        ConsoleEngine::ConstructConsole(title, paletteType, consoleWidth, consoleHeight, fontWidth, fontHeight);
    }

    COORD ConsoleEngine::ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight, const std::wstring& fontName, int fontWeight, bool fullScreen)
    {
        //Set console font
        ConsoleFont consoleFont = console.GetConsoleFont();
        consoleFont.FontWeight = (uint)fontWeight;
        consoleFont.SetFontName(fontName);
        consoleFont.SetFontWidth(fontWidth);
        consoleFont.SetFontHeight(fontHeight);
        console.SetConsoleFont(consoleFont);

        if (fullScreen)
        {
            COORD maxSize = ::GetLargestConsoleWindowSize(console.cons.consoleOutput);
            ConsoleEngine::ConstructConsole(title, paletteType, maxSize.X, maxSize.Y, fontWidth, fontHeight);
            ::ShowWindow(window.windowHandle, SW_MAXIMIZE);
            return maxSize;
        }
        else
        {
            ConsoleEngine::ConstructConsole(title, paletteType, consoleWidth, consoleHeight, fontWidth, fontHeight);
            return { (short)consoleWidth, (short)consoleHeight };
        }
    }

    void ConsoleEngine::ConstructTerminal(const std::wstring& title)
    {
        this->title = title;
        //clear the screen buffer
        Console::Global.GetInstance().Clear();
        //Set window position
        POINT centerPos = window.GetCenterPosOfWindowInDesktop();
        window.SetWindowPos(centerPos);
        //set terminal title
        console.SetTitle(title);
    }

    void ConsoleEngine::Construct(const std::wstring& title, int consoleWidth, int consoleHeight)
    {
        //兼容3种版本的控制台
        //此方法在Windows 11默认控制台下有bug, 所以暂时全部使用ConstructTerminal
        if (this->consoleType == ConsoleType::WindowsTerminal)
        {
            ConstructTerminal(title);
        }
        else if (this->consoleType == ConsoleType::WindowsConsole)
        {
            ConstructTerminal(title);
            //ConstructConsole(title, PaletteType::Legacy, consoleWidth, consoleHeight);
        }
        else if (this->consoleType == ConsoleType::WindowsLegacyConsole)
        {
            ConstructTerminal(title);
            //ConstructConsole(title, PaletteType::Legacy, consoleWidth, consoleHeight);
        }
        else
        {
            //unknown
        }
    }

    void ConsoleEngine::StartLoop(int fps, bool disableConsoleCursor)
    {
        this->running = true;

        //For Windows Terminal, we only need to set once.
        if (disableConsoleCursor && this->consoleType == ConsoleType::WindowsTerminal)
        {
            //this function is also useful for Windows Terminal.
            Console::Global.GetInstance().SetConsoleCursorVisible(false);
        }

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
            if (disableConsoleCursor && this->consoleType == ConsoleType::WindowsConsole)
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