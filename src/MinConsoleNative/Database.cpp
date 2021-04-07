#include "Database.h"
#include "File.h"
#include "String.h"
using namespace std;

namespace MinConsoleNative
{
    Database::Database()
    {
        this->savePath = File::Combine(File::GetDirectoryPath(), _T("database.txt"));
        //if not exsists, create it.
        FileMode status = File::Status(this->savePath);
        if (status != FileMode::File)
        {
            File::Creat(this->savePath, FileMode::File);
        }
    }

    Database::Database(const std::wstring& savePath)
    {
        this->savePath = savePath;
        //if not exsists, create it.
        FileMode status = File::Status(this->savePath);
        if (status != FileMode::File)
        {
            File::Creat(this->savePath, FileMode::File);
        }
    }

    int Database::GetInt(const std::wstring& key, int defaultVal)
    {
        wstring result = GetString(key, _T("null"));

        if (!String::CompareStringIgnoreCase(result, _T("null")))
        {
            return _wtoi(result.c_str());
        }

        return defaultVal;
    }

    float Database::GetFloat(const std::wstring& key, float defaultVal)
    {
        wstring result = GetString(key, _T("null"));

        if (!String::CompareStringIgnoreCase(result, _T("null")))
        {
            return _wtof(result.c_str());
        }

        return defaultVal;
    }

    bool Database::GetBool(const std::wstring& key, bool defaultVal)
    {
        wstring result = GetString(key, _T("null"));

        if (!String::CompareStringIgnoreCase(result, _T("null")))
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
            if (eqaul_sign_index != wstring::npos)
            {
                wstring keyField = line.substr(0, eqaul_sign_index);
                wstring keyFieldWithoutSpace = String::TrimAll(keyField);

                if (keyFieldWithoutSpace._Equal(key))
                {
                    wstring valueField = line.substr(eqaul_sign_index + 1, line.size());
                    wstring valueFieldWithoutSpace = String::TrimAll(valueField);

                    return valueFieldWithoutSpace;
                }
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
        SetString(key, String::ToWstring(value));
    }

    void Database::SetString(const std::wstring& key, const std::wstring& value)
    {
        auto lines = File::ReadAllLines(this->savePath);
        //If the last line is empty, remove the last line.
        if (lines[lines.size() - 1].empty())
        {
            lines.erase(lines.begin() + lines.size() - 1);
        }

        bool key_exists = false;
        bool need_to_write = false;

        for (size_t i = 0; i < lines.size(); i++)
        {
            wstring line = lines[i];

            size_t eqaul_sign_index = line.find(_T("="));
            if (eqaul_sign_index != wstring::npos)
            {
                wstring keyField = line.substr(0, eqaul_sign_index);
                wstring keyFieldWithoutSpace = String::TrimAll(keyField);

                if (keyFieldWithoutSpace._Equal(key))
                {
                    key_exists = true;

                    wstring valueField = line.substr(eqaul_sign_index + 1, line.size());
                    wstring valueFieldWithoutSpace = String::TrimAll(valueField);

                    if (valueFieldWithoutSpace != value)
                    {
                        need_to_write = true;
                        lines[i] = keyFieldWithoutSpace + _T(" = ") + value;
                    }

                    break;
                }
            }
        }

        if (need_to_write)
        {
            File::WriteAllLines(this->savePath, lines, WriteMode::Cover);
        }
        else if (!key_exists)
        {
            wstring newLine;
            newLine = _T("\n") + key + _T(" = ") + value;

            File::WriteAllText(this->savePath, newLine, WriteMode::Append);
        }
    }
}