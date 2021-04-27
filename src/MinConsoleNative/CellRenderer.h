#pragma once

#include "MinDefines.h"
#include "Console.h"
#include "Vector2.h"
#include <string>

namespace MinConsoleNative
{
    enum class CellRendererMode
    {
        //TrueColor = 1,
        Fast = 2,
        //Mixed = 3,
    };

    struct Cell
    {
    public:
        wchar c;
        Color24 foreColor;
        Color24 backColor;
        bool underScore;

        Cell()
        {
            this->c = _T(' '); //fill this with space
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Cell(wchar c)
        {
            this->c = c;
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Cell(wchar c, const Color24& foreColor)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = Color24();
            this->underScore = false;
        }

        Cell(wchar c, const Color24& foreColor, const Color24& backColor)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = false;
        }

        Cell(wchar c, const Color24& foreColor, const Color24& backColor, bool underScore)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = underScore;
        }

        bool operator ==(const Cell& other) const
        {
            if (c == other.c &&
                foreColor == other.foreColor &&
                backColor == other.backColor &&
                underScore == other.underScore)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator !=(const Cell& other) const
        {
            if (c == other.c &&
                foreColor == other.foreColor &&
                backColor == other.backColor &&
                underScore == other.underScore)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    };

    class CellRenderer
    {
    public:
        int consoleWidth;
        int consoleHeight;
        CellRendererMode mode;

    private:
        Cell* cellArray;
        Cell* cellArrayBuffer;

    public:
        CellRenderer(int consoleWidth, int consoleHeight, CellRendererMode mode);

        ~CellRenderer();

        void Clear(const Cell& cell = Cell());

        void Render();

        void Draw(const Vector2& pos, const Cell& cell);
    };
}