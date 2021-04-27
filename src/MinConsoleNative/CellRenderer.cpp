#include "CellRenderer.h"

namespace MinConsoleNative
{
    CellRenderer::CellRenderer(int consoleWidth, int consoleHeight, CellRendererMode mode)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->mode = mode;
        this->cellArray = new Cell[consoleWidth * consoleHeight];
        this->cellArrayBuffer = new Cell[consoleWidth * consoleHeight];
    }

    CellRenderer::~CellRenderer()
    {
        delete[] this->cellArray;
        delete[] this->cellArrayBuffer;
    }

    void CellRenderer::Clear(const Cell& cell)
    {
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            this->cellArrayBuffer[i] = this->cellArray[i];  //copy
            this->cellArray[i] = cell;                      //set default
        }
    }

    void CellRenderer::Render()
    {
        CHAR_INFO* charInfos = new CHAR_INFO[consoleWidth * consoleHeight];
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            const Cell& cell = this->cellArray[i];

            ushort att = 0;
            att |= ConsoleColorToUshort(cell.foreColor.ToConsoleColor(), cell.backColor.ToConsoleColor());
            if (cell.underScore)
            {
                att |= COMMON_LVB_UNDERSCORE;
            }

            charInfos[i].Attributes = att;
            charInfos[i].Char.UnicodeChar = cell.c;
        }
        console.WriteConsoleOutputW(charInfos, 0, 0, consoleWidth, consoleHeight);
        delete[] charInfos;
    }

    void CellRenderer::Draw(const Vector2& pos, const Cell& cell)
    {
        if (pos.x < 0 || pos.x > consoleWidth - 1 ||
            pos.y < 0 || pos.y > consoleHeight - 1)
        {
            return;
        }
        int index = consoleWidth * pos.y + pos.x;
        this->cellArray[index] = cell;
    }
}