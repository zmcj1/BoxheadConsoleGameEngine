#include "MinDefines.h"
#include "Singleton.h"

namespace MinConsoleNative
{
    EXPORT_FUNC GetWinVersion(uint* MajorVer, uint* MinorVer, uint* BuildNumber);

    //See:https://docs.microsoft.com/en-us/windows/win32/sysinfo/operating-system-version
    //Windows10Ver:https://en.wikipedia.org/wiki/Windows_10_version_history#Version_2004_(May_2020_Update)
    class WinVersion
    {
    private:
        uint majorVer;
        uint minorVer;
        uint buildNumber;

    public:
        uint MajorVer()
        {
            return majorVer;
        }

        uint MinorVer()
        {
            return minorVer;
        }

        uint BuildNumber()
        {
            return buildNumber;
        }

        bool IsWindows2000();

        bool IsWindowsXP();

        bool IsWindowsVista();

        bool IsWindows7();

        bool IsWindows8();

        bool IsWindows8point1();

        bool IsWindows8Or8point1();

        bool IsWindows10();

        //==========================================

        bool IsWindows2000OrLater();

        bool IsWindowsXPOrLater();

        bool IsWindowsVistaOrLater();

        bool IsWindows7OrLater();

        bool IsWindows8Or8point1OrLater();

        bool IsWindows10OrLater();

        //See:https://devblogs.microsoft.com/commandline/windows-10-creators-update-whats-new-in-bashwsl-windows-console/
        bool IsWindows10CreatorsOrLater();

        bool IsWindows10FallCreatorsOrLater();

        bool IsWindows10Version1809OrLater();

        WinVersion();
    };

    extern Singleton<WinVersion> winVersionInstance;
}