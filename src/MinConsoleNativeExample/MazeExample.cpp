#include "../MinConsoleNative/MinConsoleNative.h"
#include <vector>
#define MAZE_WIDTH   59
#define MAZE_HEIGHT  59
#define CONW (MAZE_WIDTH * 2) + 1 //+1 for compatibility with legacy console
#define CONH (MAZE_HEIGHT + 1)

int main()
{
    ConsoleEngine consoleEngine;
    if (consoleEngine.consoleType == ConsoleType::WindowsConsole)
    {
        consoleEngine.ConstructConsole(L"Maze", PaletteType::Legacy, CONW, CONH,
            6, 12, L"Consolas", FW_NORMAL);
    }
    else if (consoleEngine.consoleType == ConsoleType::WindowsLegacyConsole)
    {
        console.SetConsoleWindowAndBufferSize({ CONW, CONH });
    }

    std::vector<Vector2> obstacles = MazeGenerator::GenerateMaze(MAZE_WIDTH, MAZE_HEIGHT);

    SearchResult navResult = Navigation::Navigate({ 1, 1 }, { MAZE_WIDTH - 2, MAZE_HEIGHT - 2 }, SearchDirection::Four, NAV_UNLIMITED_DEPTH, obstacles, SearchMethod::DFS);

    for (int i = 0; i < MAZE_HEIGHT; i++)
    {
        for (int j = 0; j < MAZE_WIDTH; j++)
        {
            if (Vector<Vector2>::Contains(obstacles, Vector2(j, i)))
            {
                console.Write(L"  ", { 0, 0, 0 }, { 207, 238, 238 });
            }
            else if (Navigation::ContainsPosition(navResult.path, Vector2(j, i)))
            {
                console.Write(L"  ", { 0, 0, 0 }, { 255, 30, 0 });
            }
            else
            {
                console.Write(L"  ");
            }
        }
        console.WriteLine();
    }

    console.ReadLine();
    return 0;
}