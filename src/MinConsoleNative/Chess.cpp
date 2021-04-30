#include "Chess.h"
#include "TextLayout.h"

namespace MinConsoleNative
{
    wchar Chess::FirstLineLeft = L'┌';
    wchar Chess::FirstLineMiddle = L'┬';
    wchar Chess::FirstLineRight = L'┐';
    wchar Chess::LastLineLeft = L'└';
    wchar Chess::LastLineMiddle = L'┴';
    wchar Chess::LastLineRight = L'┘';
    wchar Chess::MiddleLineLeft = L'├';
    wchar Chess::MiddleLineMiddle = L'┼';
    wchar Chess::MiddleLineRight = L'┤';
    wchar Chess::ConnectSymbol = L'─';

    void Chess::Init(ChessboardType type)
    {
        switch (type)
        {
        case ChessboardType::Normal:
            Chess::FirstLineLeft = L'┌';
            Chess::FirstLineMiddle = L'┬';
            Chess::FirstLineRight = L'┐';
            Chess::LastLineLeft = L'└';
            Chess::LastLineMiddle = L'┴';
            Chess::LastLineRight = L'┘';
            Chess::MiddleLineLeft = L'├';
            Chess::MiddleLineMiddle = L'┼';
            Chess::MiddleLineRight = L'┤';
            Chess::ConnectSymbol = L'─';
            break;
        case ChessboardType::Double:
            Chess::FirstLineLeft = L'╔';
            Chess::FirstLineMiddle = L'╦';
            Chess::FirstLineRight = L'╗';
            Chess::LastLineLeft = L'╚';
            Chess::LastLineMiddle = L'╩';
            Chess::LastLineRight = L'╝';
            Chess::MiddleLineLeft = L'╠';
            Chess::MiddleLineMiddle = L'╬';
            Chess::MiddleLineRight = L'╣';
            Chess::ConnectSymbol = L'═';
            break;
        case ChessboardType::Bold:
            Chess::FirstLineLeft = L'┏';
            Chess::FirstLineMiddle = L'┳';
            Chess::FirstLineRight = L'┓';
            Chess::LastLineLeft = L'┗';
            Chess::LastLineMiddle = L'┻';
            Chess::LastLineRight = L'┛';
            Chess::MiddleLineLeft = L'┣';
            Chess::MiddleLineMiddle = L'╋';
            Chess::MiddleLineRight = L'┫';
            Chess::ConnectSymbol = L'━';
            break;
        }
    }

    std::vector<std::vector<std::wstring>> Chess::Generate(int width, int height)
    {
        std::vector<std::vector<std::wstring>> chessBoard;

        //fill the chessBoard with empty blocks.
        for (int i = 0; i < height; i++)
        {
            std::vector<std::wstring> line = std::vector<std::wstring>();
            for (int j = 0; j < width; j++)
            {
                line.push_back(std::wstring(L"  "));
            }
            chessBoard.push_back(line);
        }

        //first line
        chessBoard[0][0] = TextLayout::CombineWchar(FirstLineLeft, ConnectSymbol);
        for (int i = 1; i < width - 1; i++)
        {
            chessBoard[0][i] = TextLayout::CombineWchar(FirstLineMiddle, ConnectSymbol);
        }
        chessBoard[0][width - 1] = TextLayout::CombineWchar(FirstLineRight, _T(' '));

        //last line
        chessBoard[height - 1][0] = TextLayout::CombineWchar(LastLineLeft, ConnectSymbol);
        for (int i = 1; i < width - 1; i++)
        {
            chessBoard[height - 1][i] = TextLayout::CombineWchar(LastLineMiddle, ConnectSymbol);
        }
        chessBoard[height - 1][width - 1] = TextLayout::CombineWchar(LastLineRight, _T(' '));

        //middle line
        for (int i = 1; i < height - 1; i++)
        {
            chessBoard[i][0] = TextLayout::CombineWchar(MiddleLineLeft, ConnectSymbol);
            for (int j = 1; j < width - 1; j++)
            {
                chessBoard[i][j] = TextLayout::CombineWchar(MiddleLineMiddle, ConnectSymbol);
            }
            chessBoard[i][width - 1] = TextLayout::CombineWchar(MiddleLineRight, _T(' '));
        }

        return chessBoard;
    }
}