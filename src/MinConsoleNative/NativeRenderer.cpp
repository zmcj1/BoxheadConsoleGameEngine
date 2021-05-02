#include "NativeRenderer.h"
#include "TextLayout.h"
#include <vector>

using namespace std;

namespace MinConsoleNative
{
    CHAR_INFO NativeRenderer::defaultCharInfo = { L' ', 0x00 };

    NativeRenderer::NativeRenderer(int consoleWidth, int consoleHeight)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->charInfos = new CHAR_INFO[consoleWidth * consoleHeight];
    }

    NativeRenderer::~NativeRenderer()
    {
        delete[] this->charInfos;
    }

    void NativeRenderer::Clear(const CHAR_INFO& charInfo)
    {
        for (int i = 0; i < consoleWidth * consoleHeight; i++)
        {
            this->charInfos[i].Attributes = charInfo.Attributes;
            this->charInfos[i].Char.UnicodeChar = charInfo.Char.UnicodeChar;
        }
    }

    void NativeRenderer::Render()
    {
        console.WriteConsoleOutputW(this->charInfos, 0, 0, consoleWidth, consoleHeight);
    }

    void NativeRenderer::Draw(const Vector2& pos, const CHAR_INFO& charInfo)
    {
        if (pos.x < 0 || pos.x > consoleWidth - 1 ||
            pos.y < 0 || pos.y > consoleHeight - 1) return;
        int index = consoleWidth * pos.y + pos.x;
        this->charInfos[index] = charInfo;
    }

    void NativeRenderer::DrawString(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore)
    {
        ushort att = ConsoleColorToUshort(foreColor, backColor);
        if (underScore) att |= COMMON_LVB_UNDERSCORE;
        for (int i = 0; i < wstr.size(); i++)
        {
            NativeRenderer::Draw(Vector2(pos.x + i, pos.y), { wstr[i], att });
        }
    }

    int NativeRenderer::DrawString2(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore)
    {
        ushort att = ConsoleColorToUshort(foreColor, backColor);
        if (underScore) att |= COMMON_LVB_UNDERSCORE;

        vector<wstring> grids = textLayout.WstringToGrids(wstr);
        for (int i = 0; i < grids.size(); i++)
        {
            const wstring& gridStr = grids[i];
            if (gridStr.size() == 1)
            {
                NativeRenderer::Draw(Vector2(pos.x + i * 2, pos.y), { gridStr[0],
                    (ushort)(att | COMMON_LVB_LEADING_BYTE) });
                NativeRenderer::Draw(Vector2(pos.x + i * 2 + 1, pos.y), { L' ',
                    (ushort)(att | COMMON_LVB_TRAILING_BYTE) });
            }
            else if (gridStr.size() == 2)
            {
                NativeRenderer::Draw(Vector2(pos.x + i * 2, pos.y), { gridStr[0], att });
                NativeRenderer::Draw(Vector2(pos.x + i * 2 + 1, pos.y), { gridStr[1], att });
            }
        }
        return grids.size();
    }

    void NativeRenderer::DrawStringWrap(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore)
    {
        ushort att = ConsoleColorToUshort(foreColor, backColor);
        if (underScore) att |= COMMON_LVB_UNDERSCORE;
        for (int i = 0; i < wstr.size(); i++)
        {
            int positionX = pos.x + i;
            int positionY = pos.y;
            while (positionX > consoleWidth - 1)
            {
                positionX -= consoleWidth;
                positionY++;
            }
            NativeRenderer::Draw(Vector2(positionX, positionY), { wstr[i], att });
        }
    }

    int NativeRenderer::DrawString2Wrap(const Vector2& pos, const std::wstring& wstr, ConsoleColor foreColor, ConsoleColor backColor, bool underScore)
    {
        ushort att = ConsoleColorToUshort(foreColor, backColor);
        if (underScore) att |= COMMON_LVB_UNDERSCORE;

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
                NativeRenderer::Draw(Vector2(positionX, positionY), { gridStr[0],
                    (ushort)(att | COMMON_LVB_LEADING_BYTE) });
                NativeRenderer::Draw(Vector2(positionX + 1, positionY), { L' ',
                    (ushort)(att | COMMON_LVB_TRAILING_BYTE) });
            }
            else if (gridStr.size() == 2)
            {
                NativeRenderer::Draw(Vector2(positionX, positionY), { gridStr[0], att });
                NativeRenderer::Draw(Vector2(positionX + 1, positionY), { gridStr[1], att });
            }
        }
        return grids.size();
    }
}