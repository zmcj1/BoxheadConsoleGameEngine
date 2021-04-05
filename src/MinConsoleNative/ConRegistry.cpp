#include "ConRegistry.h"
#include "WinVersion.h"

namespace MinConsoleNative
{
    EXPORT_FUNC IsLegacyConsole(bool* yes)
    {
        static bool isLegacy10 = false, checked = false;

        if (!checked)
        {
            if (winVersionInstance.GetInstance().IsWindows10OrLater())
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

    bool ConRegistry::IsUseLegacyConsole()
    {
        bool yes;
        IsLegacyConsole(&yes);
        return yes;
    }
}