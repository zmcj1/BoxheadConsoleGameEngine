#include "ConRegistry.h"
#include "WinVersion.h"
#include <strsafe.h>

namespace MinConsoleNative
{
    EXPORT_FUNC_EX(bool) MinIsUsingLegacyConsole()
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

        return isLegacy10;
    }

    EXPORT_FUNC_EX(bool) MinUseLegacyConsole(bool yes)
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

    BOOL RegDelnode(HKEY hKeyRoot, LPCTSTR lpSubKey);

    EXPORT_FUNC_EX(bool) MinDeleteConsoleRegistry()
    {
        return RegDelnode(HKEY_CURRENT_USER, L"Console");
    }

    EXPORT_FUNC_EX(ConRegConfig) MinGetConRegConfig()
    {
        ConRegConfig config = { 0 };
        config.ForceV2 = !MinIsUsingLegacyConsole();

        DWORD allowAltF4Close = 0, virtualTerminalLevel = 0;
        MinGetConsoleRegistryDWORD(L"AllowAltF4Close", &allowAltF4Close);
        MinGetConsoleRegistryDWORD(L"VirtualTerminalLevel", &virtualTerminalLevel);

        config.AllowAltF4Close = allowAltF4Close;
        config.VirtualTerminalLevel = virtualTerminalLevel;
        return config;
    }

    EXPORT_FUNC_EX(bool) MinSetConRegConfig(ConRegConfig config)
    {
        MinUseLegacyConsole(!config.ForceV2);
        MinSetConsoleRegistryDWORD(L"AllowAltF4Close", config.AllowAltF4Close);
        MinSetConsoleRegistryDWORD(L"VirtualTerminalLevel", config.VirtualTerminalLevel);
        return true;
    }

    //*************************************************************
    //
    //  RegDelnodeRecurse()
    //
    //  Purpose:    Deletes a registry key and all its subkeys / values.
    //
    //  Parameters: hKeyRoot    -   Root key
    //              lpSubKey    -   SubKey to delete
    //
    //  Return:     TRUE if successful.
    //              FALSE if an error occurs.
    //
    //*************************************************************
    BOOL RegDelnodeRecurse(HKEY hKeyRoot, LPTSTR lpSubKey)
    {
        LPTSTR lpEnd;
        LONG lResult;
        DWORD dwSize;
        TCHAR szName[MAX_PATH];
        HKEY hKey;
        FILETIME ftWrite;

        // First, see if we can delete the key without having
        // to recurse.

        lResult = RegDeleteKey(hKeyRoot, lpSubKey);

        if (lResult == ERROR_SUCCESS)
            return TRUE;

        lResult = RegOpenKeyEx(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

        if (lResult != ERROR_SUCCESS)
        {
            if (lResult == ERROR_FILE_NOT_FOUND)
            {
                //printf("Key not found.\n");
                return TRUE;
            }
            else
            {
                //printf("Error opening key.\n");
                return FALSE;
            }
        }

        // Check for an ending slash and add one if it is missing.

        lpEnd = lpSubKey + lstrlen(lpSubKey);

        if (*(lpEnd - 1) != TEXT('\\'))
        {
            *lpEnd = TEXT('\\');
            lpEnd++;
            *lpEnd = TEXT('\0');
        }

        // Enumerate the keys

        dwSize = MAX_PATH;
        lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
            NULL, NULL, &ftWrite);

        if (lResult == ERROR_SUCCESS)
        {
            do
            {

                *lpEnd = TEXT('\0');
                StringCchCat(lpSubKey, MAX_PATH * 2, szName);

                if (!RegDelnodeRecurse(hKeyRoot, lpSubKey))
                {
                    break;
                }

                dwSize = MAX_PATH;

                lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL,
                    NULL, NULL, &ftWrite);

            }
            while (lResult == ERROR_SUCCESS);
        }

        lpEnd--;
        *lpEnd = TEXT('\0');

        RegCloseKey(hKey);

        // Try again to delete the key.

        lResult = RegDeleteKey(hKeyRoot, lpSubKey);

        if (lResult == ERROR_SUCCESS)
            return TRUE;

        return FALSE;
    }

    //*************************************************************
    //
    //  RegDelnode()
    //
    //  Purpose:    Deletes a registry key and all its subkeys / values.
    //
    //  Parameters: hKeyRoot    -   Root key
    //              lpSubKey    -   SubKey to delete
    //
    //  Return:     TRUE if successful.
    //              FALSE if an error occurs.
    //
    //*************************************************************
    BOOL RegDelnode(HKEY hKeyRoot, LPCTSTR lpSubKey)
    {
        TCHAR szDelKey[MAX_PATH * 2];
        StringCchCopy(szDelKey, MAX_PATH * 2, lpSubKey);

        return RegDelnodeRecurse(hKeyRoot, szDelKey);
    }

    bool ConRegistry::IsUsingLegacyConsole()
    {
        return MinIsUsingLegacyConsole();
    }

    bool ConRegistry::UseLegacyConsole(bool yes)
    {
        return MinUseLegacyConsole(yes);
    }

    bool ConRegistry::DeleteConsoleRegistry()
    {
        return MinDeleteConsoleRegistry();
    }

    ConRegConfig ConRegistry::GetConRegConfig()
    {
        return MinGetConRegConfig();
    }

    bool ConRegistry::SetConRegConfig(const ConRegConfig& config)
    {
        return MinSetConRegConfig(config);
    }
}