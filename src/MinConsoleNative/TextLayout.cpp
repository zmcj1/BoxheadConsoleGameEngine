#include "TextLayout.h"
#include "String.h"

using namespace std;

namespace MinConsoleNative
{
    TextLayout::TextLayout(Console console)
    {
        this->console = console;
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
            CharWidth charWidth;
            //save as cache
            if (charWidthCacheDict.count(item) == 0)
            {
                charWidth = console.GetWcharWidth(item);
                charWidthCacheDict[item] = charWidth;
            }
            else
            {
                charWidth = charWidthCacheDict[item];
            }
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
}