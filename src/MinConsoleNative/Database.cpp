#include "Database.hpp"
#include "File.hpp"
#include "String.hpp"
using namespace std;

namespace MinConsoleNative
{
    const std::wstring DNULL = L"null";

    void CreatSaveFile(const std::wstring& filePath)
    {
        //if file not exsists, create it.
        FileMode status = File::Status(filePath);
        if (status != FileMode::File)
        {
            File::Creat(filePath, FileMode::File);
        }
    }

    Database::Database()
    {
    }

    Database::Database(const std::wstring& fileName)
    {
        this->fileName = fileName;
        this->folderPath = File::GetDirectoryPath();
        this->savePath = File::Combine(this->folderPath, this->fileName);

        CreatSaveFile(this->savePath);
    }

    Database::Database(const std::wstring& fileName, const std::wstring& folderPath)
    {
        this->fileName = fileName;
        this->folderPath = folderPath;
        this->savePath = File::Combine(this->folderPath, this->fileName);

        //create folder before creating file.
        if (File::Status(folderPath) != FileMode::Directory)
        {
            File::Creat(folderPath, FileMode::Directory);
        }

        CreatSaveFile(this->savePath);
    }

    const std::wstring& Database::GetSavePath()
    {
        return this->savePath;
    }

    void Database::SetSavePath(const std::wstring& savePath)
    {
        this->savePath = savePath;
    }

    int Database::GetInt(const std::wstring& key, int defaultVal)
    {
        wstring result = GetString(key, DNULL);

        if (!String::CompareIgnoreCase(result, DNULL))
        {
            return _wtoi(result.c_str());
        }

        return defaultVal;
    }

    float Database::GetFloat(const std::wstring& key, float defaultVal)
    {
        wstring result = GetString(key, DNULL);

        if (!String::CompareIgnoreCase(result, DNULL))
        {
            return _wtof(result.c_str());
        }

        return defaultVal;
    }

    bool Database::GetBool(const std::wstring& key, bool defaultVal)
    {
        wstring result = GetString(key, DNULL);

        if (!String::CompareIgnoreCase(result, DNULL))
        {
            return String::ToBool(result);
        }

        return defaultVal;
    }

    std::wstring Database::GetString(const std::wstring& key, const std::wstring& defaultVal)
    {
        auto lines = File::ReadAllLines(this->savePath);

        for (size_t i = 0; i < lines.size(); i++)
        {
            wstring line = lines[i];

            size_t eqaul_sign_index = line.find(_T("="));
            //Illegal line
            if (eqaul_sign_index == wstring::npos)
            {
                continue;
            }

            wstring keyStr = line.substr(0, eqaul_sign_index);
            wstring keyStrWithoutSpace = String::Trim(keyStr);
            //Find first key
            if (keyStrWithoutSpace._Equal(key))
            {
                wstring valueStr = line.substr(eqaul_sign_index + 1, line.size());
                wstring valueStrWithoutSpace = String::Trim(valueStr);

                return valueStrWithoutSpace;
            }
        }

        return defaultVal;
    }

    void Database::SetInt(const std::wstring& key, int value)
    {
        SetString(key, to_wstring(value));
    }

    void Database::SetFloat(const std::wstring& key, float value)
    {
        SetString(key, to_wstring(value));
    }

    void Database::SetBool(const std::wstring& key, bool value)
    {
        SetString(key, String::BoolToWstring(value));
    }

    void Database::SetString(const std::wstring& key, const std::wstring& value)
    {
        auto lines = File::ReadAllLines(this->savePath);
        //If the file is empty, just write!
        if (lines.size() == 0 || (lines.size() == 1 && lines[0].empty()))
        {
            wstring newLine = key + _T(" = ") + value;
            File::WriteAllText(this->savePath, newLine, WriteMode::Append);
            return;
        }

        bool key_exists = false;
        bool need_to_write = false;

        for (size_t i = 0; i < lines.size(); i++)
        {
            wstring line = lines[i];

            size_t eqaul_sign_index = line.find(_T("="));
            //Illegal line
            if (eqaul_sign_index == wstring::npos)
            {
                continue;
            }

            wstring keyStr = line.substr(0, eqaul_sign_index);
            wstring keyStrWithoutSpace = String::Trim(keyStr);
            //Find first key
            if (keyStrWithoutSpace._Equal(key))
            {
                key_exists = true;

                wstring valueStr = line.substr(eqaul_sign_index + 1, line.size());
                wstring valueStrWithoutSpace = String::Trim(valueStr);
                //If value changed
                if (valueStrWithoutSpace != value)
                {
                    need_to_write = true;
                    lines[i] = keyStrWithoutSpace + _T(" = ") + value;
                }

                break;
            }
        }

        if (need_to_write)
        {
            File::WriteAllLines(this->savePath, lines, WriteMode::Cover);
        }
        else if (!key_exists)
        {
            wstring newLine = _T("\n") + key + _T(" = ") + value;

            File::WriteAllText(this->savePath, newLine, WriteMode::Append);
        }
    }
}