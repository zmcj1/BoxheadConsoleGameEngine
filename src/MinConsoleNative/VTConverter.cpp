#include "VTConverter.h"
#include <cstdio>

using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC MinVTResetStyle(wchar* str, int strLen)
    {
        //ESC [ <n> m
        //<n> : 0
        int r = swprintf_s(str, strLen, L"%ls[0m", _T(ESC));
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTForeColor(wchar* str, int strLen, Color24 foreColor)
    {
        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTBackColor(wchar* str, int strLen, Color24 backColor)
    {
        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[48;2;%d;%d;%dm", _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTColor(wchar* str, int strLen, Color24 foreColor, Color24 backColor)
    {
        //ESC [ <n> m
        //<n> : 38 ; 2 ; <r> ; <g> ; <b>
        //ESC [ <n> m
        //<n> : 48 ; 2 ; <r> ; <g> ; <b>
        int r = swprintf_s(str, strLen, L"%ls[38;2;%d;%d;%dm%ls[48;2;%d;%d;%dm", _T(ESC), foreColor.r, foreColor.g, foreColor.b, _T(ESC), backColor.r, backColor.g, backColor.b);
        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    EXPORT_FUNC MinVTUnderline(wchar* str, int strLen, bool underLine)
    {
        //ESC [ <n> m
        //<n> : 4	    Underline
        //<n> : 24      No underline
        int r = 0;
        if (underLine)
        {
            r = swprintf_s(str, strLen, L"%ls[4m", _T(ESC));
        }
        else
        {
            r = swprintf_s(str, strLen, L"%ls[24m", _T(ESC));
        }

        if (r == -1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    std::wstring VTConverter::ResetStyle()
    {
        wchar buf[VT_STR_LEN];
        MinVTResetStyle(buf, VT_STR_LEN);
        return std::wstring(buf);
    }

    std::wstring VTConverter::ForeColor(Color24 foreColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTForeColor(buf, VT_STR_LEN, foreColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::BackColor(Color24 backColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTBackColor(buf, VT_STR_LEN, backColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::Color(Color24 foreColor, Color24 backColor)
    {
        wchar buf[VT_STR_LEN];
        MinVTColor(buf, VT_STR_LEN, foreColor, backColor);
        return std::wstring(buf);
    }

    std::wstring VTConverter::Underline(bool underLine)
    {
        wchar buf[VT_STR_LEN];
        MinVTUnderline(buf, VT_STR_LEN, underLine);
        return std::wstring(buf);
    }
}