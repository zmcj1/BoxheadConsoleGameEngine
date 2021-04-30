#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

int main()
{
    ConsoleEngine engine;
    engine.ConstructConsole(L"chess", PaletteType::Legacy, 120, 30, 8, 16, GetFontName(FontName::MSGothic), FW_NORMAL);
    console.SetConsoleCursorVisible(false);

    Chess::Init(ChessboardType::Bold);
    vector<vector<wstring>> chessBoard = Chess::Generate(10, 10);
    chessBoard[0][2] = _T("● ");

    GridRenderer grenderer(10, 10, GridRendererMode::Fast);
    grenderer.Clear();
    for (int i = 0; i < chessBoard.size(); i++)
    {
        for (int j = 0; j < chessBoard[i].size(); j ++)
        {
            grenderer.Draw({ j , i }, Grid(chessBoard[i][j], { 0,255,0 }, { 0,0,255 }, false));
        }
    }
    grenderer.Render();

    console.ReadLine();
    return 0;
}