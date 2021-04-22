#include "File.h"
#include "Utils.h"
using namespace std;

namespace MinConsoleNative
{
    std::wstring File::ToShortPathName(const std::wstring& path)
    {
        wchar short_path_name[MAX_PATH];
        ::GetShortPathName(path.c_str(), short_path_name, MAX_PATH);

        wstring result(short_path_name);
        return result;
    }

    std::wstring File::GetDirectoryPath()
    {
        wstring path;

        wchar buffer[MAX_PATH];
        ::GetModuleFileName(NULL, buffer, LEN(buffer));

        path = buffer;
        int index = path.find_last_of(_T('\\'));
        wstring directory_path = path.substr(0, index + 1);

        return directory_path;
    }

    std::wstring File::GetExePath()
    {
        wstring path;

        wchar buffer[MAX_PATH];
        ::GetModuleFileName(NULL, buffer, LEN(buffer));

        path = buffer;
        return path;
    }

    std::wstring File::Combine(const std::wstring& p1, const std::wstring& p2)
    {
        std::wstring path;

        if (p1.back() == _T('\\'))
        {
            path = p1 + p2;
        }
        else
        {
            path = p1 + _T("\\") + p2;
        }

        return path;
    }

    std::wstring File::GetFileExtension(const std::wstring& path)
    {
        wstring extension;

        size_t pos = path.find_last_of(L'.');
        if (pos == wstring::npos)
        {
            return extension;
        }

        extension = path.substr(pos + 1);
        return extension;
    }

    bool File::Exists(const std::wstring& path)
    {
        FileMode type = File::Status(path);
        return type != FileMode::None;
    }

    FileMode File::Status(const std::wstring& path)
    {
        DWORD ftype = GetFileAttributes(path.c_str());

        if (ftype == INVALID_FILE_ATTRIBUTES)
            return FileMode::None;        // something is wrong with your path!

        if (ftype & FILE_ATTRIBUTE_DIRECTORY)
            return FileMode::Directory;   // this is a directory!

        if (ftype & FILE_ATTRIBUTE_ARCHIVE)
            return FileMode::File;        // this is a file!

        return FileMode::None;            // this is not a directory!
    }

    bool File::Creat(const std::wstring& path, FileMode mode, bool withUTF8BOM)
    {
        if (File::Exists(path))
            return false;

        bool result = false;

        if (mode == FileMode::File)
        {
            HANDLE fileHandle = CreateFile(path.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);

            result = fileHandle != INVALID_HANDLE_VALUE;

            //write UTF-8 BOM
            if (withUTF8BOM && result)
            {
                byte BOM[3];
                BOM[0] = 0xEF;
                BOM[1] = 0xBB;
                BOM[2] = 0xBF;
                DWORD written = 0;
                result = WriteFile(fileHandle, BOM, LEN(BOM), &written, nullptr);
            }
        }
        else if (mode == FileMode::Directory)
        {
            result = CreateDirectory(path.c_str(), NULL) != 0;
        }

        return result;
    }

    bool File::Delete(const std::wstring& path)
    {
        FileMode mode = Status(path);

        if (mode == FileMode::None)
        {
            return false;
        }
        else if (mode == FileMode::File)
        {
            return DeleteFile(path.c_str());
        }
        else if (mode == FileMode::Directory)
        {
            return RemoveDirectory(path.c_str()) != 0;
        }
        else
        {
            return false;
        }
    }

    std::vector<std::wstring> File::ReadAllLines(const std::wstring& path)
    {
        std::vector<std::wstring> lines;

        if (!Exists(path))
        {
            return lines;
        }

        wstring text = ReadAllText(path);
        lines = String::Split(text, WNEW_LINE);

        return lines;
    }

    std::wstring File::ReadAllText(const std::wstring& path)
    {
        std::wstring text;

        if (!Exists(path))
        {
            return text;
        }

        HANDLE fileHandle = CreateFile(path.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            return text;
        }

        DWORD size = 0;
        size = GetFileSize(fileHandle, nullptr) + 1;

        char* arr = new char[size];
        ZeroMemory(arr, size);
        DWORD written = 0;
        bool readSuccess = ReadFile(fileHandle, arr, size, &written, nullptr);

        if (!readSuccess)
        {
            delete[] arr;
            return text;
        }

        bool utf8String = is_str_utf8(arr);
        if (utf8String)
        {
            text = String::StringToWstring(string(arr), Encoding::UTF8);
        }
        else
        {
            text = String::StringToWstring(string(arr), Encoding::Default);
        }

        delete[] arr;
        return text;
    }

    bool File::WriteAllLines(const std::wstring& path, std::vector<std::wstring> lines, WriteMode write_mode, Encoding encoding)
    {
        if (!Exists(path))
        {
            return false;
        }

        wstring text;
        for (size_t i = 0; i < lines.size(); i++)
        {
            if (i == lines.size() - 1)
            {
                text += lines[i];
            }
            else
            {
                text += (lines[i] + L"\n");
            }
        }

        return WriteAllText(path, text, write_mode, encoding);
    }

    bool File::WriteAllText(const std::wstring& path, const std::wstring& text, WriteMode write_mode, Encoding encoding)
    {
        if (!Exists(path))
        {
            return false;
        }

        HANDLE fileHandle = INVALID_HANDLE_VALUE;

        if (write_mode == WriteMode::Cover)
        {
            fileHandle = CreateFile(path.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

        }
        //SEE:https://stackoverflow.com/questions/18933283/how-to-append-text-to-a-file-in-windows
        else if (write_mode == WriteMode::Append)
        {
            fileHandle = CreateFile(path.c_str(),
                FILE_APPEND_DATA,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        }

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        string buf = String::WstringToString(text, encoding);
        DWORD written = 0;
        return WriteFile(fileHandle, buf.c_str(), buf.size(), &written, nullptr);
    }

    bool File::Clear(const std::wstring& path)
    {
        return WriteAllText(path, L"", WriteMode::Cover);
    }
}