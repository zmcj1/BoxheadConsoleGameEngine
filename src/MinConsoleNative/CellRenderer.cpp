#include "CellRenderer.hpp"
#include "String.hpp"
#include "TextLayout.hpp"
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
        if (mode == CellRendererMode::Fast)
        {
            this->charInfos = new CHAR_INFO[consoleWidth * consoleHeight];
        }
        else
        {
            this->charInfos = nullptr;
        }
    }

    CellRenderer::~CellRenderer()
    {
        delete[] this->cellArray;
        delete[] this->cellArrayBuffer;
        if (mode == CellRendererMode::Fast)
        {
            delete[] this->charInfos;
        }
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

    void CellRenderer::DrawString(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore)
    {
        for (int i = 0; i < wstr.size(); i++)
        {
            CellRenderer::Draw(Vector2(pos.x + i, pos.y), Cell(wstr[i], foreColor, backColor, underScore));
        }
    }

    int CellRenderer::DrawString2(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore)
    {
        vector<wstring> grids = textLayout.WstringToGrids(wstr);
        for (int i = 0; i < grids.size(); i++)
        {
            const wstring& gridStr = grids[i];
            if (gridStr.size() == 1)
            {
                CellRenderer::Draw(Vector2(pos.x + i * 2, pos.y), Cell(gridStr[0], foreColor, backColor, underScore, true));
                CellRenderer::Draw(Vector2(pos.x + i * 2 + 1, pos.y), Cell(L' ', foreColor, backColor, underScore, false));
            }
            else if (gridStr.size() == 2)
            {
                CellRenderer::Draw(Vector2(pos.x + i * 2, pos.y), Cell(gridStr[0], foreColor, backColor, underScore));
                CellRenderer::Draw(Vector2(pos.x + i * 2 + 1, pos.y), Cell(gridStr[1], foreColor, backColor, underScore));
            }
        }
        return grids.size();
    }

    void CellRenderer::DrawStringWrap(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore)
    {
        for (int i = 0; i < wstr.size(); i++)
        {
            int positionX = pos.x + i;
            int positionY = pos.y;
            while (positionX > consoleWidth - 1)
            {
                positionX -= consoleWidth;
                positionY++;
            }
            CellRenderer::Draw(Vector2(positionX, positionY), Cell(wstr[i], foreColor, backColor, underScore));
        }
    }

    int CellRenderer::DrawString2Wrap(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore)
    {
        vector<wstring> grids = textLayout.WstringToGrids(wstr);
        for (int i = 0; i < grids.size(); i++)
        {
            int positionX = pos.x + i * 2;
            int positionY = pos.y;
            while (positionX > consoleWidth - 1)
            {
                positionX -= consoleWidth;
                positionY++;
            }
            const wstring& gridStr = grids[i];
            if (gridStr.size() == 1)
            {
                CellRenderer::Draw(Vector2(positionX, positionY), Cell(gridStr[0], foreColor, backColor, underScore, true));
                CellRenderer::Draw(Vector2(positionX + 1, positionY), Cell(L' ', foreColor, backColor, underScore, false));
            }
            else if (gridStr.size() == 2)
            {
                CellRenderer::Draw(Vector2(positionX, positionY), Cell(gridStr[0], foreColor, backColor, underScore));
                CellRenderer::Draw(Vector2(positionX + 1, positionY), Cell(gridStr[1], foreColor, backColor, underScore));
            }
        }
        return grids.size();
    }

    void CellRenderer::DrawBorderBox(const Vector2& pos, const Vector2& size, const Vector2& borderSize, const Cell& cell, const Cell& borderCell)
    {
        for (int i = 0; i < size.y; i++)
        {
            for (int j = 0; j < size.x; j++)
            {
                if (i >= 0 && i < borderSize.y || j >= 0 && j < borderSize.x ||
                    i <= size.y - 1 && i > size.y - 1 - borderSize.y ||
                    j <= size.x - 1 && j > size.x - 1 - borderSize.x)
                {
                    CellRenderer::Draw(Vector2(pos.x + j, pos.y + i), borderCell);
                }
                else
                {
                    CellRenderer::Draw(Vector2(pos.x + j, pos.y + i), cell);
                }
            }
        }
    }

    void CellRenderer::DrawBorderBox2(const Vector2& pos, const Vector2& size, const Vector2& borderSize, const std::wstring& cellWstr, Color24 cellForeColor, Color24 cellBackColor, bool cellUnderScore, const std::wstring& borderWstr, Color24 borderForeColor, Color24 borderBackColor, bool borderUnderScore)
    {
        for (int i = 0; i < size.y; i++)
        {
            for (int j = 0; j < size.x; j++)
            {
                if (i >= 0 && i < borderSize.y || j >= 0 && j < borderSize.x ||
                    i <= size.y - 1 && i > size.y - 1 - borderSize.y ||
                    j <= size.x - 1 && j > size.x - 1 - borderSize.x)
                {
                    CellRenderer::DrawString2(Vector2(pos.x + j * 2, pos.y + i), borderWstr, borderForeColor, borderBackColor, borderUnderScore);
                }
                else
                {
                    CellRenderer::DrawString2(Vector2(pos.x + j * 2, pos.y + i), cellWstr, cellForeColor, cellBackColor, cellUnderScore);
                }
            }
        }
    }

    void CellRenderer::RenderFast()
    {
        bool findLeadingByte = false;
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            const Cell& cell = this->cellArray[i];
            ushort att = 0;
            att |= MinConsoleColorToUshort(cell.foreColor.ToConsoleColor(), cell.backColor.ToConsoleColor());
            if (cell.underScore) att |= COMMON_LVB_UNDERSCORE;
            if (cell.isLeadingByte)
            {
                att |= COMMON_LVB_LEADING_BYTE;
                findLeadingByte = true;
            }
            else if (findLeadingByte)
            {
                att |= COMMON_LVB_TRAILING_BYTE;
                findLeadingByte = false;
            }
            charInfos[i].Attributes = att;
            charInfos[i].Char.UnicodeChar = cell.c;
        }
        console.WriteConsoleOutputW(charInfos, 0, 0, consoleWidth, consoleHeight);
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
        wstring* lines = new wstring[consoleHeight];
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            lines[i / consoleWidth] += this->cellArray[i].c;
            const Cell& cell = this->cellArray[i];
            if (cell.isLeadingByte)
            {
                i++;
            }
        }
        for (int i = 0; i < consoleHeight; i++)
        {
            console.WriteConsoleOutputCharacterW(lines[i], { 0, (short)i });
        }
        delete[] lines;
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