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
        GridRenderer::Clear();
    }

    GridRenderer::~GridRenderer()
    {
        delete[] this->gridArray;
    }

    void GridRenderer::Clear()
    {
        for (int i = 0; i < logicalWidth * logicalHeight; i++)
        {
            this->gridArray[i].wstr = L"  ";
            this->gridArray[i].foreColor = Color24();
            this->gridArray[i].backColor = Color24();
            this->gridArray[i].underScore = false;
        }
    }

    void GridRenderer::Render()
    {
        if (mode == GridRendererMode::Fast)
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
                else
                {
                    throw "error";
                }
            }

            console.WriteConsoleOutputW(charInfos, 0, 0, logicalWidth * 2, logicalHeight);

            delete[] charInfos;
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
            Vector2 position(pos.x + i, pos.y);
            wstring wstrGrid = wstrGrids[i];
            GridRenderer::Draw(position, Grid(wstrGrid, foreColor, backColor, underScore));
        }

        return wstrGrids.size();
    }
}