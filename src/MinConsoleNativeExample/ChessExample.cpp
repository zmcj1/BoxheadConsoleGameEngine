#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    ConsoleEngine engine;
    engine.ConstructConsole(L"chess", PaletteType::Legacy, 120, 30, 8, 16, GetFontName(FontName::MSGothic), FW_NORMAL);
    console.SetConsoleCursorVisible(false);

    vector<wstring> chessBoard = Chess::Generate(10, 10);
    chessBoard[0][0] = _T('●');
    chessBoard[0][1] = _T('●');
    chessBoard[0][2] = _T('●');
    chessBoard[0][3] = _T('●');
    chessBoard[0][4] = _T('●');

    GridRenderer grenderer(20, 20, GridRendererMode::TrueColor);
    grenderer.Clear();
    for (int i = 0; i < chessBoard.size(); i++)
    {
        for (int j = 0; j < chessBoard[i].size(); j++)
        {
            wstring str = String::WcharToWstring(chessBoard[i][j]);
            if (Chess::IsChessChar(str[0]))
            {
                str += L' ';
            }
            grenderer.Draw({ j,i }, Grid(str, { 0,255,0 }, { 0,0,255 }, false));
        }
    }
    grenderer.Render();

    console.ReadLine();
    return 0;
}