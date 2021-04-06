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
        static uint StringToHashCode(const std::string& str);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint WstringToHashCode(const std::wstring& wstr);

        static bool CompareStringIgnoreCase(const std::string& a, const std::string& b);

        static bool CompareStringIgnoreCase(const std::wstring& a, const std::wstring& b);

        static std::string ToString(bool value);

        static std::wstring ToWstring(bool value);

        static bool ToBool(const std::string& str);

        static bool ToBool(const std::wstring& wstr);

        static std::wstring StringToWstring(const std::string& str);

        static std::string WstringToString(const std::wstring& wstr);

        static std::string CharToString(char c);

        static std::wstring WcharToWstring(wchar wc);
    };
}