#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    class String
    {
    public:
        static std::wstring Trim(const std::wstring& wstr);

        static std::wstring TrimStart(const std::wstring& wstr);

        static std::wstring TrimEnd(const std::wstring& wstr);

        static std::wstring TrimAll(const std::wstring& wstr);

        static bool CompareIgnoreCase(const std::string& a, const std::string& b);

        static bool CompareIgnoreCase(const std::wstring& a, const std::wstring& b);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::string& str);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::wstring& wstr);

        static bool ToBool(const std::string& str);

        static bool ToBool(const std::wstring& wstr);

        //===========XXToString===========

        static std::string BoolToString(bool value);

        static std::string CharToString(char c);

        static std::string WstringToString(const std::wstring& wstr);

        //===========XXToWstring===========

        static std::wstring BoolToWstring(bool value);

        static std::wstring WcharToWstring(wchar wc);

        static std::wstring StringToWstring(const std::string& str);
    };
}