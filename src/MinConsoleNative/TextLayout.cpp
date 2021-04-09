#include "TextLayout.h"
#include "String.h"
#include "Debug.h"

using namespace std;

namespace MinConsoleNative
{
    TextLayout::TextLayout(Console console)
    {
        this->console = console;
    }

    CharWidth TextLayout::GetWcharWidth(wchar c)
    {
        CharWidth charWidth;
        //check user define first.
        if (charWidthUserDefineDict.count(c) != 0)
        {
            charWidth = charWidthUserDefineDict[c];
        }
        else
        {
            //save as cache
            if (charWidthCacheDict.count(c) == 0)
            {
                charWidth = console.GetWcharWidth(c);
                charWidthCacheDict[c] = charWidth;
            }
            //use cache
            else
            {
                charWidth = charWidthCacheDict[c];
            }
        }
        return charWidth;
    }

    int TextLayout::GetWstringWidth(const std::wstring& str)
    {
        int width = 0;
        for (size_t i = 0; i < str.size(); i++)
        {
            CharWidth cw = GetWcharWidth(str[i]);
            width += (int)cw;
        }
        return width;
    }

    wstring TextLayout::CombineWchar(wchar a1, wchar a2)
    {
        wchar arr[3] = { 0 };
        arr[0] = a1;
        arr[1] = a2;
        return wstring(arr);
    }

    std::vector<std::wstring> TextLayout::WstringToGrids(const std::wstring wstr)
    {
        vector<wstring> grids;
        bool hasTemp = false;
        wchar temp = 0;

        for (int i = 0; i < wstr.length(); i++)
        {
            wchar item = wstr[i];
            CharWidth charWidth = GetWcharWidth(item);

            //combine grid
            if (charWidth == CharWidth::Half)
            {
                if (hasTemp)
                {
                    grids.push_back(CombineWchar(temp, item));
                    hasTemp = false;
                }
                else
                {
                    temp = item;
                    hasTemp = true;
                }
            }
            if (charWidth == CharWidth::Full)
            {
                if (hasTemp)
                {
                    grids.push_back(CombineWchar(temp, _T(' ')));
                    hasTemp = false;
                }
                grids.push_back(String::WcharToWstring(item));
            }
        }

        if (hasTemp)
        {
            grids.push_back(CombineWchar(temp, _T(' ')));
            hasTemp = false;
        }

        return grids;
    }

    std::vector<std::wstring> TextLayout::WstringToLines(const std::wstring wstr, int width, bool fillAll)
    {
        std::vector<std::wstring> lines;

        if (width < 1) return lines;
        if (width == 1)
        {
            for (size_t i = 0; i < wstr.size(); i++)
            {
                lines.push_back(String::WcharToWstring(wstr[i]));
            }
            return lines;
        }

        auto grids = WstringToGrids(wstr);

        int tempWidth = 0;
        wstring tempLine;

        if (width % 2 == 0)
        {
            for (size_t i = 0; i < grids.size(); i++)
            {
                tempWidth += 2;
                tempLine += grids[i];
                if (tempWidth == width)
                {
                    lines.push_back(tempLine);
                    tempWidth = 0;
                    tempLine = wstring();
                }
            }
        }
        else
        {
            for (size_t i = 0; i < grids.size(); i++)
            {
                tempWidth += 2;
                tempLine += grids[i];

                if (tempWidth > width)
                {
                    //double HalfWidth, add one to the last of this line.
                    if (grids[i].size() == 2)
                    {
                        wstring add = tempLine.substr(0, tempLine.size() - grids[i].size());
                        wstring additional = String::WcharToWstring(grids[i][0]);
                        lines.push_back(add + additional);

                        tempWidth = 1;
                        tempLine = String::WcharToWstring(grids[i][1]);
                    }
                    //single FullWidth, put it to the next line.
                    else
                    {
                        wstring add = tempLine.substr(0, tempLine.size() - grids[i].size());
                        wstring additional = String::WcharToWstring(L' ');
                        lines.push_back(add + additional);

                        tempWidth = 2;
                        tempLine = String::WcharToWstring(grids[i][0]);
                    }
                }
                else if (tempWidth == width)
                {
                    lines.push_back(tempLine);
                    tempWidth = 0;
                    tempLine = wstring();
                }
            }
        }

        if (tempLine != L"")
        {
            if (fillAll)
            {
                wstring fill;
                int w = GetWstringWidth(tempLine);
                for (size_t i = 0; i < width - w; i++)
                {
                    fill += L" ";
                }
                lines.push_back(tempLine + fill);
            }
            else
            {
                lines.push_back(tempLine);
            }
            tempLine = wstring();
        }

        return lines;
    }
}