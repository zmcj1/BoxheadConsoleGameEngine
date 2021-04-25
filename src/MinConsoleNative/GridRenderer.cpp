#include "GridRenderer.h"
#include "TextLayout.h"

using namespace std;

namespace MinConsoleNative
{
    GridRenderer::GridRenderer(int logicalWidth, int logicalHeight, GridRendererMode mode)
    {
        this->logicalWidth = logicalWidth;
        this->logicalHeight = logicalHeight;
        this->mode = mode;
        this->gridArray = new Grid[logicalWidth * logicalHeight];
        this->gridArrayBuffer = new Grid[logicalWidth * logicalHeight];
    }

    GridRenderer::~GridRenderer()
    {
        delete[] this->gridArray;
        delete[] this->gridArrayBuffer;
    }

    void GridRenderer::Clear(const Grid& grid)
    {
        for (int i = 0; i < logicalWidth * logicalHeight; i++)
        {
            this->gridArrayBuffer[i] = this->gridArray[i];  //copy
            this->gridArray[i] = grid;                      //set default
        }
    }

    void GridRenderer::Render()
    {
        if (mode == GridRendererMode::Fast)
        {
            ConsoleType consoleType = console.GetConsoleType();
            if (consoleType == ConsoleType::WindowsLegacyConsole)
            {
                //draw true color
                for (int i = 0; i < logicalWidth * logicalHeight; i++)
                {
                    const Grid& grid = this->gridArray[i];
                    const Grid& gridBuffer = this->gridArrayBuffer[i];
                    if (grid != gridBuffer)
                    {
                        COORD position = { i % logicalWidth * 2, i / logicalWidth };
                        COORD beforePosition = console.GetConsoleCursorPos();
                        console.SetConsoleCursorPos(position);
                        console.Write(L"  ", grid.foreColor, grid.backColor, grid.underScore);
                        console.SetConsoleCursorPos(beforePosition);
                    }
                }
                //draw string
                wstring wstr;
                for (int i = 0; i < logicalWidth * logicalHeight; i++)
                {
                    if (this->gridArray[i].wstr == L"") wstr += L"  ";
                    else wstr += this->gridArray[i].wstr;
                }
                vector<wstring> lines = textLayout.WstringToLines(wstr, logicalWidth * 2, true);
                for (int i = 0; i < lines.size(); i++)
                {
                    console.WriteConsoleOutputCharacterW(lines[i], { 0, (short)i });
                }
            }
            else
            {
                CHAR_INFO* charInfos = new CHAR_INFO[logicalWidth * 2 * logicalHeight];

                for (int i = 0; i < logicalWidth * logicalHeight; i++)
                {
                    const Grid& grid = this->gridArray[i];

                    ushort att = 0;
                    att |= ConsoleColorToUshort(grid.foreColor.ToConsoleColor(), grid.backColor.ToConsoleColor());
                    if (grid.underScore)
                    {
                        att |= COMMON_LVB_UNDERSCORE;
                    }

                    if (grid.wstr.size() == 1)
                    {
                        charInfos[i * 2].Attributes = att | COMMON_LVB_LEADING_BYTE;
                        charInfos[i * 2].Char.UnicodeChar = grid.wstr[0];
                        charInfos[i * 2 + 1].Attributes = att | COMMON_LVB_TRAILING_BYTE;
                        charInfos[i * 2 + 1].Char.UnicodeChar = L' ';
                    }
                    else if (grid.wstr.size() == 2)
                    {
                        charInfos[i * 2].Attributes = att;
                        charInfos[i * 2].Char.UnicodeChar = grid.wstr[0];
                        charInfos[i * 2 + 1].Attributes = att;
                        charInfos[i * 2 + 1].Char.UnicodeChar = grid.wstr[1];
                    }
                    else if (grid.wstr.size() == 0)
                    {
                        charInfos[i * 2].Attributes = att;
                        charInfos[i * 2].Char.UnicodeChar = L' ';
                        charInfos[i * 2 + 1].Attributes = att;
                        charInfos[i * 2 + 1].Char.UnicodeChar = L' ';
                    }
                    else
                    {
                        throw GridRendererException::WrongWstrGridSize;
                    }
                }

                console.WriteConsoleOutputW(charInfos, 0, 0, logicalWidth * 2, logicalHeight);

                delete[] charInfos;
            }
        }
        else if (mode == GridRendererMode::TrueColor)
        {
            for (int i = 0; i < logicalWidth * logicalHeight; i++)
            {
                const Grid& grid = this->gridArray[i];
                const Grid& gridBuffer = this->gridArrayBuffer[i];
                if (grid != gridBuffer)
                {
                    COORD position = { i % logicalWidth * 2, i / logicalWidth };
                    COORD beforePosition = console.GetConsoleCursorPos();
                    console.SetConsoleCursorPos(position);
                    console.Write(grid.wstr, grid.foreColor, grid.backColor, grid.underScore);
                    console.SetConsoleCursorPos(beforePosition);
                }
            }
        }
        else if (mode == GridRendererMode::Mixed)
        {
            //draw true color
            for (int i = 0; i < logicalWidth * logicalHeight; i++)
            {
                const Grid& grid = this->gridArray[i];
                const Grid& gridBuffer = this->gridArrayBuffer[i];
                if (grid != gridBuffer)
                {
                    COORD position = { i % logicalWidth * 2, i / logicalWidth };
                    COORD beforePosition = console.GetConsoleCursorPos();
                    console.SetConsoleCursorPos(position);
                    console.Write(L"  ", grid.foreColor, grid.backColor, grid.underScore);
                    console.SetConsoleCursorPos(beforePosition);
                }
            }
            //draw string
            wstring wstr;
            for (int i = 0; i < logicalWidth * logicalHeight; i++)
            {
                if (this->gridArray[i].wstr == L"") wstr += L"  ";
                else wstr += this->gridArray[i].wstr;
            }
            vector<wstring> lines = textLayout.WstringToLines(wstr, logicalWidth * 2, true);
            for (int i = 0; i < lines.size(); i++)
            {
                console.WriteConsoleOutputCharacterW(lines[i], { 0, (short)i });
            }
        }
    }

    void GridRenderer::Draw(const Vector2& pos, const Grid& grid)
    {
        if (pos.x < 0 || pos.x > logicalWidth - 1 ||
            pos.y < 0 || pos.y > logicalHeight - 1)
        {
            return;
        }
        int index = logicalWidth * pos.y + pos.x;
        this->gridArray[index] = grid;
    }

    int GridRenderer::Draw(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore)
    {
        vector<wstring> wstrGrids = textLayout.WstringToGrids(wstr);

        for (int i = 0; i < wstrGrids.size(); i++)
        {
            GridRenderer::Draw(Vector2(pos.x + i, pos.y), Grid(wstrGrids[i], foreColor, backColor, underScore));
        }

        return wstrGrids.size();
    }

    int GridRenderer::DrawWrap(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore)
    {
        vector<wstring> wstrGrids = textLayout.WstringToGrids(wstr);

        for (int i = 0; i < wstrGrids.size(); i++)
        {
            int positionX = pos.x + i;
            int positionY = pos.y;
            while (positionX > logicalWidth - 1)
            {
                positionX -= logicalWidth;
                positionY++;
            }
            GridRenderer::Draw(Vector2(positionX, positionY), Grid(wstrGrids[i], foreColor, backColor, underScore));
        }

        return wstrGrids.size();
    }
}