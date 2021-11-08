#pragma once

#include "MinDefines.h"
#include <string>
#include <vector>

namespace MinConsoleNative
{
    enum class Encoding
    {
        Unknown = 0,
        Default = 1,
        UTF8 = 2,
    };

    class String
    {
    public:
        static std::wstring Trim(const std::wstring& wstr);

        static std::wstring TrimStart(const std::wstring& wstr);

        static std::wstring TrimEnd(const std::wstring& wstr);

        static std::wstring TrimAll(const std::wstring& wstr);

        static std::vector<std::wstring> Split(const std::wstring& wstr, const std::wstring& separator);

        //if strings are eqaul, return true
        static bool Compare(const std::string& a, const std::string& b);

        //if strings are eqaul, return true
        static bool Compare(const std::wstring& a, const std::wstring& b);

        //if strings are eqaul, return true
        static bool CompareIgnoreCase(const std::string& a, const std::string& b);

        //if strings are eqaul, return true
        static bool CompareIgnoreCase(const std::wstring& a, const std::wstring& b);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::string& str);

        //See:BKDR Hash Function:https://www.byvoid.com/zhs/blog/string-hash-compare
        static uint ToHashCode(const std::wstring& wstr);

        static bool ToBool(const std::string& str);

        static bool ToBool(const std::wstring& wstr);

        static int ToInt(const std::string& str);

        static int ToInt(const std::wstring& wstr);

        //===========XXToString===========

        static std::string BoolToString(bool value);

        static std::string CharToString(char c);

        static std::string WstringToString(const std::wstring& wstr, Encoding encoding = Encoding::Default);

        //===========XXToWstring===========

        static std::wstring BoolToWstring(bool value);

        static std::wstring WcharToWstring(wchar wc);

        static std::wstring StringToWstring(const std::string& str, Encoding encoding = Encoding::Default);

        //===========functions===========

        //来源:https://blog.csdn.net/thedarkfairytale/article/details/73457200
        static bool IsUTF8String(const char* str);
    };
}