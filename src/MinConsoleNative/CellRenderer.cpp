#include "CellRenderer.h"
#include "String.h"
#include <string>
using namespace std;

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
        if (mode == CellRendererMode::Fast) RenderFast();
        else if (mode == CellRendererMode::TrueColor) RenderTrueColor();
        else if (mode == CellRendererMode::Mixed) RenderMixed();
    }

    void CellRenderer::Draw(const Vector2& pos, const Cell& cell)
    {
        if (pos.x < 0 || pos.x > consoleWidth - 1 ||
            pos.y < 0 || pos.y > consoleHeight - 1) return;
        int index = consoleWidth * pos.y + pos.x;
        this->cellArray[index] = cell;
    }

    void CellRenderer::RenderFast()
    {
        CHAR_INFO* charInfos = new CHAR_INFO[consoleWidth * consoleHeight];
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            const Cell& cell = this->cellArray[i];
            ushort att = 0;
            att |= ConsoleColorToUshort(cell.foreColor.ToConsoleColor(), cell.backColor.ToConsoleColor());
            if (cell.underScore) att |= COMMON_LVB_UNDERSCORE;
            charInfos[i].Attributes = att;
            charInfos[i].Char.UnicodeChar = cell.c;
        }
        console.WriteConsoleOutputW(charInfos, 0, 0, consoleWidth, consoleHeight);
        delete[] charInfos;
    }

    void CellRenderer::RenderMixed()
    {
        //draw true color:
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            const Cell& cell = this->cellArray[i];
            const Cell& cellBuffer = this->cellArrayBuffer[i];
            if (cell != cellBuffer)
            {
                COORD position = { i % consoleWidth, i / consoleWidth };
                COORD beforePosition = console.GetConsoleCursorPos();
                console.SetConsoleCursorPos(position);
                console.Write(String::WcharToWstring(L' '), cell.foreColor, cell.backColor, cell.underScore);
                console.SetConsoleCursorPos(beforePosition);
            }
        }
        //draw string:
        wstring wstr;
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
            wstr += this->cellArray[i].c;
        console.WriteConsoleOutputCharacterW(wstr, { 0,0 });
    }

    void CellRenderer::RenderTrueColor()
    {
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            const Cell& cell = this->cellArray[i];
            const Cell& cellBuffer = this->cellArrayBuffer[i];
            if (cell != cellBuffer)
            {
                COORD position = { i % consoleWidth, i / consoleWidth };
                COORD beforePosition = console.GetConsoleCursorPos();
                console.SetConsoleCursorPos(position);
                console.Write(String::WcharToWstring(cell.c), cell.foreColor, cell.backColor, cell.underScore);
                console.SetConsoleCursorPos(beforePosition);
            }
        }
    }
}