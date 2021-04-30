#include "Chess.h"

namespace MinConsoleNative
{
    std::vector<std::wstring> Chess::Generate(int width, int height)
    {
        std::vector<std::wstring> chessBoard;
        if (width < 2 || height < 2) return chessBoard;

        //fill the chessBoard with spaces
        for (int i = 0; i < height; i++)
        {
            chessBoard.push_back(std::wstring(width, _T(' ')));
        }

        //first line
        chessBoard[0][0] = _T('┌');
        for (int i = 1; i < width - 1; i++)
        {
            chessBoard[0][i] = _T('┬');
        }
        chessBoard[0][width - 1] = _T('┐');

        //last line
        chessBoard[height - 1][0] = _T('└');
        for (int i = 1; i < width - 1; i++)
        {
            chessBoard[height - 1][i] = _T('┴');
        }
        chessBoard[height - 1][width - 1] = _T('┘');

        //content
        for (int i = 1; i < height - 1; i++)
        {
            chessBoard[i][0] = _T('├');
            for (int j = 1; j < width - 1; j++)
            {
                chessBoard[i][j] = _T('┼');
            }
            chessBoard[i][width - 1] = _T('┤');
        }

        return chessBoard;
    }

    bool Chess::IsChessChar(wchar wc)
    {
        if (wc == _T('┌') || wc == _T('┬') || wc == _T('┐') ||
            wc == _T('├') || wc == _T('┼') || wc == _T('┤') ||
            wc == _T('└') || wc == _T('┴') || wc == _T('┘'))
        {
            return true;
        }
        return false;
    }
}