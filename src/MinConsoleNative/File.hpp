#pragma once

#include "MinDefines.hpp"
#include "String.hpp"
#include <string>
#include <vector>

namespace MinConsoleNative
{
    enum class FileMode
    {
        None = 0,
        File = 1,
        Directory = 2,
    };

    enum class WriteMode
    {
        Cover = 1,
        Append = 2,
    };

    //使用ExternFree释放该函数的返回值
    EXPORT_FUNC_EX(wchar*) MinToShortPathName(_IN_ const wchar* path);

    class File
    {
    private:
        File()
        {
        }

    public:
        //Convert absolute path to short path
        static std::wstring ToShortPathName(const std::wstring& path);

        static std::wstring GetDirectoryPath();

        static std::wstring GetExePath();

        static std::wstring Combine(const std::wstring& p1, const std::wstring& p2);

        static std::wstring GetFileExtension(const std::wstring& path);

        //from:https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
        //extension must include dot(.)
        //return filename, not filepath
        static std::vector<std::wstring> GetFileNamesWithExtension(const std::wstring& folderPath, const std::wstring& extension);

        static bool Exists(const std::wstring& path);

        //See:https://stackoverflow.com/questions/8233842/how-to-check-if-directory-exist-using-c-and-winapi
        static FileMode Status(const std::wstring& path);

        static bool Creat(const std::wstring& path, FileMode mode = FileMode::File, bool withUTF8BOM = false);

        static bool Delete(const std::wstring& path);

        //If the file is empty, return a vector containing a empty line.
        static std::vector<std::wstring> ReadAllLines(const std::wstring& path, const std::wstring& separator = NEW_LINEW);

        static std::wstring ReadAllText(const std::wstring& path);

        static std::vector<MinConsoleNative::byte> ReadAllBytes(const std::wstring& path);

        static bool WriteAllLines(const std::wstring& path, std::vector<std::wstring> lines, WriteMode write_mode = WriteMode::Cover, Encoding encoding = Encoding::UTF8);

        static bool WriteAllText(const std::wstring& path, const std::wstring& text, WriteMode write_mode = WriteMode::Cover, Encoding encoding = Encoding::UTF8);

        static bool WriteAllBytes(const std::wstring& path, const std::vector<MinConsoleNative::byte>& bytes, WriteMode write_mode = WriteMode::Cover);

        static bool Clear(const std::wstring& path);
    };
}