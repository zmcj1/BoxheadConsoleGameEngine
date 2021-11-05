#pragma once

#include "MinDefines.h"
#include "Console.h"
#include "PaletteSystem.h"
#include <string>

namespace MinConsoleNative
{
    enum class FontName
    {
        Consolas = 1,   //Consolas
        MSGothic = 2,   //MS Gothic
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
        case FontName::Consolas: return L"Consolas";
        case FontName::MSGothic: return L"MS Gothic";
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

        COORD ConstructConsole(const std::wstring& title, PaletteType paletteType, int consoleWidth, int consoleHeight, int fontWidth, int fontHeight, const std::wstring& fontName, int fontWeight, bool fullScreen);

        void ConstructTerminal(const std::wstring& title);

        //一般来说, 推荐使用该API进行初始化以保证对Windows Terminal的最大兼容性
        //*新问题：在Windows11中设置默认控制台为WT会导致ConsoleType获取出现问题（总是为WindowsConsole而不是WT）
        //暂时解决方法：使用Win键 + R输出wt，然后cd到目标路径再手动输入(目标名).exe完成启动
        void Construct(const std::wstring& title, int consoleWidth, int consoleHeight);

        //If fps is not a positive number, it means that there is no frame rate limit.
        void StartLoop(int fps = 0, bool disableConsoleCursor = true);

        void StopLoop();
    };
}