#pragma once

#include "MinDefines.h"
#include <vector>
#include <string>

namespace MinConsoleNative
{
    enum class ChessboardType
    {
        Normal = 1,
        Double = 2,
        Bold = 3,
    };

    class Chess
    {
    private:
        Chess()
        {
        }

    public:
        static wchar FirstLineLeft;
        static wchar FirstLineMiddle;
        static wchar FirstLineRight;
        static wchar LastLineLeft;
        static wchar LastLineMiddle;
        static wchar LastLineRight;
        static wchar MiddleLineLeft;
        static wchar MiddleLineMiddle;
        static wchar MiddleLineRight;
        static wchar ConnectSymbol;

    public:
        static void Init(ChessboardType type);

        //Construct a chessboard, notice that the chessboard maybe displays differently in different fonts in Windows Console.
        static std::vector<std::vector<std::wstring>> Generate(int width, int height);
    };
}