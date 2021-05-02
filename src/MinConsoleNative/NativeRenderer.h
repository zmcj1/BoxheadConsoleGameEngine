#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include "Console.h"

namespace MinConsoleNative
{
    class NativeRenderer
    {
    public:
        int consoleWidth;
        int consoleHeight;
        static CHAR_INFO defaultCharInfo;

    private:
        CHAR_INFO* charInfos;

    public:
        NativeRenderer(int consoleWidth, int consoleHeight);

        ~NativeRenderer();

        void Clear(const CHAR_INFO& charInfo = defaultCharInfo);

        void Render();

        void Draw(const Vector2& pos, const CHAR_INFO& charInfo);

        void DrawString(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore);

        int DrawString2(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore);

        void DrawStringWrap(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore);

        int DrawString2Wrap(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore);
    };
}