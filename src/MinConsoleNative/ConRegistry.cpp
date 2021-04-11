#include "ConRegistry.h"
#include "WinVersion.h"

namespace MinConsoleNative
{
    EXPORT_FUNC MinIsUsingLegacyConsole(bool* yes)
    {
        static bool isLegacy10 = false, checked = false;

        if (!checked)
        {
            if (WinVersion::Global.GetInstance().IsWindows10OrLater())
            {
                HKEY key;
                bool forceV2 = false;
                DWORD value = 0, type = 0, size = sizeof(value);

                if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Console", 0, KEY_READ, &key) == 0)
                {
                    if (RegQueryValueEx(key, L"ForceV2", NULL, &type, (LPBYTE)&value, &size) == 0)
                    {
                        forceV2 = ((type == REG_DWORD) && size && (value != 0));
                    }
                    RegCloseKey(key);
                }

                isLegacy10 = !forceV2;
            }

            checked = true;
        }

        *yes = isLegacy10;

        return true;
    }

    EXPORT_FUNC MinUseLegacyConsole(bool yes)
    {
        HKEY key;

        if (::RegOpenKeyEx(HKEY_CURRENT_USER, L"Console", 0, KEY_READ | KEY_WRITE, &key) == ERROR_SUCCESS)
        {
            DWORD value = !yes;

            LSTATUS result = ::RegSetValueEx(key, L"ForceV2", 0, REG_DWORD, (BYTE*)&value, sizeof(value));

            ::RegCloseKey(key);

            if (result == ERROR_SUCCESS)
            {
                return true;
            }
        }

        return false;
    }

    EXPORT_FUNC_EX(bool) MinGetConsoleRegistryDWORD(const wchar* valueName, DWORD* data)
    {
        HKEY key;
        bool success = false;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Console", 0, KEY_READ, &key) == ERROR_SUCCESS)
        {
            DWORD type;
            DWORD dataSize = sizeof(DWORD);
            LSTATUS result = RegQueryValueEx(key, valueName, nullptr, &type, (BYTE*)data, &dataSize);
            if (result == ERROR_SUCCESS && type == REG_DWORD)
            {
                success = true;
            }
            RegCloseKey(key);
        }
        return success;
    }

    EXPORT_FUNC_EX(bool) MinSetConsoleRegistryDWORD(const wchar* valueName, DWORD data)
    {
        HKEY key;
        bool success = false;
        if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Console", 0, KEY_READ | KEY_WRITE, &key) == ERROR_SUCCESS)
        {
            LSTATUS result = RegSetValueEx(key, valueName, 0, REG_DWORD, (const byte*)&data, sizeof(DWORD));
            success = result == ERROR_SUCCESS;
            RegCloseKey(key);
        }
        return success;
    }

    bool ConRegistry::IsUsingLegacyConsole()
    {
        bool yes;
        MinIsUsingLegacyConsole(&yes);
        return yes;
    }

    bool ConRegistry::UseLegacyConsole(bool yes)
    {
        return MinUseLegacyConsole(yes);
    }
}