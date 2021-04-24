#pragma once

#include "MinDefines.h"
#include "Console.h"
#include <string>

namespace MinConsoleNative
{
    struct Grid
    {
    public:
        std::wstring wstr;
        Color24 foreColor;
        Color24 backColor;
        bool under_score;

        Grid()
        {
            this->wstr = _T("");
            this->foreColor = Color24();
            this->backColor = Color24();
            this->under_score = false;
        }

        Grid(std::wstring wstr)
        {
            this->wstr = wstr;
            this->foreColor = Color24();
            this->backColor = Color24();
            this->under_score = false;
        }

        Grid(std::wstring wstr, Color24 foreColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = Color24();
            this->under_score = false;
        }

        Grid(std::wstring wstr, Color24 foreColor, Color24 backColor)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->under_score = false;
        }

        Grid(std::wstring wstr, Color24 foreColor, Color24 backColor, bool under_score)
        {
            this->wstr = wstr;
            this->foreColor = foreColor;
            this->backColor = backColor;
            this->under_score = under_score;
        }

        bool operator ==(const Grid& other) const
        {
            if (wstr == other.wstr &&
                foreColor == other.foreColor &&
                backColor == other.backColor &&
                under_score == other.under_score)
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
                under_score == other.under_score)
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

    };
}