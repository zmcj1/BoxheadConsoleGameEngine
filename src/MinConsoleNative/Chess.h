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

    enum class ChessSymbolType
    {
        Default = 1,
        Hollow = 2,
        Square = 3,
        HollowSquare = 4,
        Diamond = 5,
        HollowDiamond = 6,
    };

    class Chess
    {
    private:
        Chess()
        {
        }

    public:
        //SEE:https://en.wikipedia.org/wiki/Box-drawing_character
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
        static wchar ChessSymbol;

    public:
        static void Init(ChessboardType type);

        static void ChangeChessSymbol(ChessSymbolType symbolType);

        //Construct a chessboard, notice that the chessboard maybe displays differently in different fonts in Windows Console.
        static std::vector<std::vector<std::wstring>> Generate(int width, int height);

        static bool PlayChess(std::vector<std::vector<std::wstring>>& chessboard, int x, int y);
    };
}