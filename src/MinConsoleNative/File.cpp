#include "File.hpp"
#include "String.hpp"
using namespace std;

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(wchar*) MinToShortPathName(_IN_ const wchar* path)
    {
        int count = ::wcslen(path) + 1;
        wchar* wstr = ExternAlloc<wchar>(count);
        ::ZeroMemory(wstr, count * sizeof(wchar));

        wstring shortPathName = File::ToShortPathName(path);
        wcscpy_s(wstr, count, shortPathName.c_str());

        return wstr;
    }

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

    std::wstring File::GetFileDir(const std::wstring& path)
    {
        size_t pos = path.find_last_of(L'\\');
        if (pos == wstring::npos)
        {
            return std::wstring();
        }
        return path.substr(0, pos + 1);
    }

    std::vector<std::wstring> File::GetFileNamesWithExtension(const std::wstring& folderPath, const std::wstring& extension)
    {
        vector<wstring> names;
        wstring search_path = folderPath + L"/*" + extension;
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                // read all (real) files in current folder
                // , delete '!' read other 2 default folder . and ..
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                {
                    names.push_back(fd.cFileName);
                }
            }
            while (::FindNextFile(hFind, &fd));
            ::FindClose(hFind);
        }
        return names;
    }

    std::vector<std::wstring> File::GetSubFolders(const std::wstring& rootFolderPath, bool relative)
    {
        vector<wstring> subFolders;
        wstring search_path = rootFolderPath + L"/*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY &&
                    fd.cFileName[0] != L'.')
                {
                    if (relative)
                    {
                        subFolders.push_back(fd.cFileName);
                    }
                    else
                    {
                        wchar buffer[MAX_PATH];
                        GetFullPathName(rootFolderPath.c_str(), MAX_PATH, buffer, 0);
                        subFolders.push_back(File::Combine(std::wstring(buffer), fd.cFileName));
                    }
                }
            }
            while (::FindNextFile(hFind, &fd));
            ::FindClose(hFind);
        }
        return subFolders;
    }

    void File::GetAllSubFolders(const std::wstring& rootFolderPath, std::vector<std::wstring>& allSubFolders)
    {
        std::vector<std::wstring> subFolders = File::GetSubFolders(rootFolderPath, false);
        for (const auto& subFolder : subFolders)
        {
            allSubFolders.push_back(subFolder);
            File::GetAllSubFolders(subFolder, allSubFolders);
        }
    }

    std::vector<std::wstring> File::GetAllSubFolders(const std::wstring& rootFolderPath)
    {
        std::vector<std::wstring> subFolders;
        File::GetAllSubFolders(rootFolderPath, subFolders);
        return subFolders;
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

        return FileMode::None;            // unknown
    }

    bool File::Creat(const std::wstring& path, FileMode mode, bool withUTF8BOM)
    {
        if (File::Exists(path))
            return false;

        if (mode == FileMode::File)
        {
            HANDLE fileHandle = CreateFile(path.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ | FILE_SHARE_WRITE,
                nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);

            if (fileHandle == INVALID_HANDLE_VALUE)
            {
                return false;
            }

            //write UTF-8 BOM
            if (withUTF8BOM)
            {
                byte BOM[3];
                BOM[0] = 0xEF;
                BOM[1] = 0xBB;
                BOM[2] = 0xBF;
                DWORD written = 0;

                bool write_suc = WriteFile(fileHandle, BOM, LEN(BOM), &written, nullptr);

                //This not only frees up system resources, but can have wider influence on things like sharing the file or device and committing data to disk.
                bool close_suc = CloseHandle(fileHandle);

                return write_suc && close_suc;
            }
            else
            {
                bool close_suc = CloseHandle(fileHandle);

                return close_suc;
            }
        }
        else if (mode == FileMode::Directory)
        {
            bool creat_suc = ::CreateDirectory(path.c_str(), NULL) != 0;
            return creat_suc;
        }
        else
        {
            return false;
        }
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

    std::vector<std::wstring> File::ReadAllLines(const std::wstring& path, const std::wstring& separator)
    {
        std::vector<std::wstring> lines;

        if (!Exists(path))
        {
            return lines;
        }

        wstring text = ReadAllText(path);
        lines = String::Split(text, separator);

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
        ::ZeroMemory(arr, size * sizeof(char));

        DWORD written = 0;
        bool readSuccess = ReadFile(fileHandle, arr, size, &written, nullptr);

        ::CloseHandle(fileHandle);

        if (!readSuccess)
        {
            delete[] arr;
            return text;
        }

        bool utf8String = String::IsUTF8String(arr);
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

    std::vector<MinConsoleNative::byte> File::ReadAllBytes(const std::wstring& path)
    {
        std::vector<MinConsoleNative::byte> bytes;

        if (!Exists(path))
        {
            return bytes;
        }

        HANDLE fileHandle = CreateFile(path.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

        if (fileHandle == INVALID_HANDLE_VALUE)
        {
            return bytes;
        }

        DWORD size = 0;
        size = GetFileSize(fileHandle, nullptr);

        MinConsoleNative::byte* arr = new MinConsoleNative::byte[size];
        ::ZeroMemory(arr, size * sizeof(char));

        DWORD written = 0;
        bool readSuccess = ReadFile(fileHandle, arr, size, &written, nullptr);

        ::CloseHandle(fileHandle);

        if (!readSuccess)
        {
            delete[] arr;
            return bytes;
        }

        for (int i = 0; i < size; i++)
        {
            bytes.push_back(arr[i]);
        }

        return bytes;
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
        bool write_suc = WriteFile(fileHandle, buf.c_str(), buf.size(), &written, nullptr);

        bool close_suc = ::CloseHandle(fileHandle);

        return write_suc && close_suc;
    }

    bool File::WriteAllBytes(const std::wstring& path, const std::vector<MinConsoleNative::byte>& bytes, WriteMode write_mode)
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

        DWORD written = 0;

        bool write_suc = WriteFile(fileHandle, bytes.data(), bytes.size(), &written, nullptr);

        bool close_suc = ::CloseHandle(fileHandle);

        return write_suc && close_suc;
    }

    bool File::Clear(const std::wstring& path)
    {
        return WriteAllText(path, L"", WriteMode::Cover);
    }
}