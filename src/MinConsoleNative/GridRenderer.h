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
        TrueColor = 1,
        Fast = 2,
        Mixed = 3,
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
            this->wstr = _T("");
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(std::wstring wstr)
        {
            this->wstr = wstr;
            this->foreColor = Color24();
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(std::wstring wstr, Color24 foreColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = Color24();
            this->underScore = false;
        }

        Grid(std::wstring wstr, Color24 foreColor, Color24 backColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = false;
        }

        Grid(std::wstring wstr, Color24 foreColor, Color24 backColor, bool under_score)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->underScore = under_score;
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

    public:
        GridRenderer(int logicalWidth, int logicalHeight, GridRendererMode mode);

        ~GridRenderer();

        void Clear();

        void Render();

        void Draw(const Vector2& pos, const Grid& grid);

        //return the logicalWidth of wstr
        int Draw(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore);

        //return the logicalWidth of wstr
        int DrawWrap(const Vector2& pos, const std::wstring& wstr, const Color24& foreColor, const Color24& backColor, bool underScore);
    };
}