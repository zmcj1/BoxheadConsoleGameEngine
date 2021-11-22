#pragma once

#include "MinDefines.hpp"
#include "Console.hpp"
#include "Vector2.hpp"
#include <string>

namespace MinConsoleNative
{
    enum class CellRendererMode
    {
        TrueColor = 1,      //RGB(24bit) support, partial render
        Fast = 2,           //16 colors support, full render
        Mixed = 3,          //RGB(24bit) support, mixed render
        FastTrueColor = 4,  //RGB(24bit)颜色支持, 全面渲染
    };

    struct Cell
    {
    public:
        wchar c;
        Color24 foreColor;
        Color24 backColor;
        bool underScore;
        bool isLeadingByte; //This var is used internally and should be ignored.

        Cell()
        {
            this->c = _T(' '); //fill this with space
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
            this->isLeadingByte = false;
        }

        Cell(wchar c)
        {
            this->c = c;
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
            this->isLeadingByte = false;
        }

        Cell(wchar c, const Color24& foreColor)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = Color24();
            this->underScore = false;
            this->isLeadingByte = false;
        }

        Cell(wchar c, const Color24& foreColor, const Color24& backColor)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = false;
            this->isLeadingByte = false;
        }

        Cell(wchar c, const Color24& foreColor, const Color24& backColor, bool underScore)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = underScore;
            this->isLeadingByte = false;
        }

        Cell(wchar c, const Color24& foreColor, const Color24& backColor, bool underScore, bool isLeadingByte)
        {
            this->c = c;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = underScore;
            this->isLeadingByte = isLeadingByte;
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
        CHAR_INFO* charInfos;

    public:
        CellRenderer(int consoleWidth, int consoleHeight, CellRendererMode mode);

        ~CellRenderer();

        void Clear(const Cell& cell = Cell());

        void Render();

        void Draw(const Vector2& pos, const Cell& cell);

        void DrawString(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore);

        int DrawString2(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore);

        void DrawStringWrap(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore);

        int DrawString2Wrap(const Vector2& pos, const std::wstring& wstr, Color24 foreColor, Color24 backColor, bool underScore);

        void DrawBorderBox(const Vector2& pos, const Vector2& size, const Vector2& borderSize, const Cell& cell, const Cell& borderCell);

        void DrawBorderBox2(const Vector2& pos, const Vector2& size, const Vector2& borderSize, const std::wstring& cellWstr, Color24 cellForeColor, Color24 cellBackColor, bool cellUnderScore, const std::wstring& borderWstr, Color24 borderForeColor, Color24 borderBackColor, bool borderUnderScore);

    private:
        void RenderFast();

        void RenderMixed();

        void RenderTrueColor();

        void RenderFastTrueColor();
    };
}