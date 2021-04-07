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

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::string& str);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::wstring& wstr);

        static bool CompareIgnoreCase(const std::string& a, const std::string& b);

        static bool CompareIgnoreCase(const std::wstring& a, const std::wstring& b);

        static bool ToBool(const std::string& str);

        static bool ToBool(const std::wstring& wstr);

        //===========ToString===========

        static std::string ToString(bool value);

        static std::string ToString(char c);

        static std::string ToString(const std::wstring& wstr);

        //===========ToWstring===========

        static std::wstring ToWstring(bool value);

        static std::wstring ToWstring(wchar wc);

        static std::wstring ToWstring(const std::string& str);
    };
}