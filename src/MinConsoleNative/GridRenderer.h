#pragma once

#include "MinDefines.h"
#include "Vector2.h"
#include "Console.h"
#include <string>
#include <vector>

namespace MinConsoleNative
{
    enum class GridRendererMode
    {
        TrueColor = 1,  //RGB(24bit) support, partial render
        Fast = 2,       //16 colors support, full render
        Mixed = 3,      //RGB(24bit) support, mixed render
    };

    enum class GridRendererException
    {
        WrongWstrGridSize = 1,
    };

    struct Grid
    {
    public:
        std::wstring wstr;
        Color24 foreColor;
        Color24 backColor;
        bool underScore;

        Grid()
        {
            this->wstr = _T("  "); //fill this with spaces
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(const std::wstring& wstr)
        {
            this->wstr = wstr;
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(const std::wstring& wstr, const Color24& foreColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(const std::wstring& wstr, const Color24& foreColor, const Color24& backColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = false;
        }

        Grid(const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = underScore;
        }

        bool operator ==(const Grid& other) const
        {
            if (wstr == other.wstr &&
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

        bool operator !=(const Grid& other) const
        {
            if (wstr == other.wstr &&
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

    class GridRenderer
    {
    public:
        int logicalWidth;
        int logicalHeight;
        GridRendererMode mode;

    private:
        Grid* gridArray;
        Grid* gridArrayBuffer;

    public:
        GridRenderer(int logicalWidth, int logicalHeight, GridRendererMode mode);

        ~GridRenderer();

        void Clear(const Grid& grid = Grid());

        void Render();

        void Draw(const Vector2& pos, const Grid& grid);

        //return the logicalWidth of wstr, return 0 if fails.
        int DrawString(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore);

        //return the logicalWidth of wstr, return 0 if fails.
        int DrawStringWrap(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore);

    private:
        void RenderFast();

        void RenderMixed();

        void RenderTrueColor();
    };
}