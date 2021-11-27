#pragma once

#include "MinDefines.hpp"
#include <string>

namespace MinConsoleNative
{
    enum class OLCSpriteException
    {
        CantOpenSpriteFile = 1,
    };

    //为了兼容javidx9所创建.spr格式, 这种格式被广泛应用于javidx9创建的控制台游戏中
    //参考:https://github.com/OneLoneCoder/videos/blob/master/olcConsoleGameEngine.h
    class OLCSprite
    {
    public:
        int Width;
        int Height;

    private:
        short* glyphs;
        short* colours;

    public:
        OLCSprite()
        {
            this->Width = 0;
            this->Height = 0;
            this->glyphs = nullptr;
            this->colours = nullptr;
        }

        OLCSprite(int w, int h)
        {
            this->Width = w;
            this->Height = h;
            this->glyphs = new short[w * h];
            this->colours = new short[w * h];
            //set default value:
            for (int i = 0; i < w * h; i++)
            {
                glyphs[i] = L' ';
                colours[i] = 0;
            }
        }

        OLCSprite(const std::wstring& file)
        {
            this->glyphs = nullptr;
            this->colours = nullptr;
            //load from file:
            if (!Load(file))
                throw OLCSpriteException::CantOpenSpriteFile;
        }

    public:
        void SetGlyph(int x, int y, short c)
        {
            if (x < 0 || x >= Width || y < 0 || y >= Height)
                return;
            else
                glyphs[y * Width + x] = c;
        }

        void SetColour(int x, int y, short c)
        {
            if (x < 0 || x >= Width || y < 0 || y >= Height)
                return;
            else
                colours[y * Width + x] = c;
        }

        short GetGlyph(int x, int y)
        {
            if (x < 0 || x >= Width || y < 0 || y >= Height)
                return L' ';
            else
                return glyphs[y * Width + x];
        }

        short GetColour(int x, int y)
        {
            if (x < 0 || x >= Width || y < 0 || y >= Height)
                return 0;
            else
                return colours[y * Width + x];
        }

        short SampleGlyph(float x, float y)
        {
            int sx = (int)(x * (float)Width);
            int sy = (int)(y * (float)Height - 1.0f);
            if (sx < 0 || sx >= Width || sy < 0 || sy >= Height)
                return L' ';
            else
                return glyphs[sy * Width + sx];
        }

        short SampleColour(float x, float y)
        {
            int sx = (int)(x * (float)Width);
            int sy = (int)(y * (float)Height - 1.0f);
            if (sx < 0 || sx >= Width || sy < 0 || sy >= Height)
                return 0;
            else
                return colours[sy * Width + sx];
        }

        bool Save(std::wstring path)
        {
            FILE* f = nullptr;
            _wfopen_s(&f, path.c_str(), L"wb");
            if (f == nullptr)
                return false;

            fwrite(&Width, sizeof(int), 1, f);
            fwrite(&Height, sizeof(int), 1, f);
            fwrite(colours, sizeof(short), Width * Height, f);
            fwrite(glyphs, sizeof(short), Width * Height, f);

            fclose(f);

            return true;
        }

        bool Load(const std::wstring& path)
        {
            if (this->glyphs != nullptr)
                delete[] this->glyphs;
            if (this->colours != nullptr)
                delete[] this->colours;

            FILE* f = nullptr;
            _wfopen_s(&f, path.c_str(), L"rb");
            if (f == nullptr)
                return false;

            std::fread(&Width, sizeof(int), 1, f);
            std::fread(&Height, sizeof(int), 1, f);
            //alloc:
            this->glyphs = new short[Width * Height];
            this->colours = new short[Width * Height];
            //read data from file:
            std::fread(colours, sizeof(short), Width * Height, f);
            std::fread(glyphs, sizeof(short), Width * Height, f);

            std::fclose(f);
            return true;
        }

        void Resize(int newWidth, int newHeight)
        {
            short* newGlyphs = new short[newWidth * newHeight];
            short* newColours = new short[newWidth * newHeight];

            for (int y = 0; y < newHeight; y++)
            {
                for (int x = 0; x < newWidth; x++)
                {
                    newGlyphs[y * newWidth + x] = this->GetGlyph(x, y);
                    newColours[y * newWidth + x] = this->GetColour(x, y);
                }
            }

            delete[] this->glyphs;
            delete[] this->colours;

            this->glyphs = newGlyphs;
            this->colours = newColours;
            this->Width = newWidth;
            this->Height = newHeight;
        }
    };
}