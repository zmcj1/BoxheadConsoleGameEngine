#pragma once

#include "MinDefines.h"
#include <vector>
#include <string>

namespace MinConsoleNative
{
    class Chess
    {
    private:
        Chess()
        {
        }

    public:
        //Construct a chessboard, notice that the chessboard displays differently in different fonts in Windows Console.
        static std::vector<std::wstring> Generate(int width, int height);

        static bool IsChessChar(wchar wc);
    };
}