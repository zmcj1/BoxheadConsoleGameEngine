#include "File.h"
#include <fstream>
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

        wifstream fInput;
        fInput.open(path.c_str());

        if (!fInput.is_open())
        {
            return lines;
        }

        while (!fInput.eof())
        {
            wstring line;
            getline(fInput, line);

            lines.push_back(line);
        }

        fInput.close();

        return lines;
    }

    std::wstring File::ReadAllText(const std::wstring& path)
    {
        std::wstring text;
        auto list = ReadAllLines(path);
        for (size_t i = 0; i < list.size(); i++)
        {
            if (!list[i].empty())
            {
                text += (list[i] + _T("\n"));
            }
        }
        return text;
    }

    bool File::WriteAllLines(const std::wstring& path, std::vector<std::wstring> lines, WriteMode write_mode)
    {
        if (!Exists(path))
        {
            return false;
        }

        bool suc = false;

        wofstream fOutput;
        if (write_mode == WriteMode::Cover)
        {
            fOutput.open(path.c_str());
        }
        else if (write_mode == WriteMode::Append)
        {
            fOutput.open(path.c_str(), ios::app);
        }

        if (fOutput.is_open())
        {
            suc = true;
        }

        for (size_t i = 0; i < lines.size(); i++)
        {
            if (i == lines.size() - 1)
            {
                fOutput << lines[i];
            }
            else
            {
                fOutput << lines[i] << endl;
            }
        }

        fOutput.close();

        return suc;
    }

    bool File::WriteAllText(const std::wstring& path, const std::wstring& text, WriteMode write_mode)
    {
        if (!Exists(path))
        {
            return false;
        }

        bool suc = false;

        wofstream fOutput;
        if (write_mode == WriteMode::Cover)
        {
            fOutput.open(path.c_str());
        }
        else if (write_mode == WriteMode::Append)
        {
            fOutput.open(path.c_str(), ios::app);
        }

        if (fOutput.is_open())
        {
            suc = true;
        }

        fOutput << text;

        fOutput.close();

        return suc;
    }

    bool File::Clear(const std::wstring& path)
    {
        return WriteAllText(path, L"", WriteMode::Cover);
    }
}