#pragma once

#include "MinDefines.hpp"
#include <string>
#include <vector>

// Doc:https://docs.microsoft.com/en-us/windows/win32/api/commdlg/nf-commdlg-getopenfilenamew
// 参考:https://blog.csdn.net/fx_odyssey/article/details/77481939

namespace MinConsoleNative
{
    struct FileFilter
    {
    public:
        std::wstring desc;
        std::wstring extension;

        FileFilter(const std::wstring& desc, const std::wstring& extension)
        {
            this->desc = desc;
            this->extension = extension;
        }
    };

    class FileDialog
    {
    public:
        static std::wstring Open(const std::vector<FileFilter>* filters = nullptr);
    };
}