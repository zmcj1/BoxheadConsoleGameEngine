#include "MinDefines.h"
#include "Singleton.h"
#include <string>

namespace MinConsoleNative
{
    //FROM:https://github.com/zhongyang219/ConsoleMusicPlayer/blob/master/MusicPlayer/WinVersionHelper.h
    EXPORT_FUNC MinGetWinVersion(_OUT_ uint* MajorVer, _OUT_ uint* MinorVer, _OUT_ uint* BuildNumber);

    EXPORT_FUNC MinIsWindows2000(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindowsXP(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindowsVista(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows7(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows8(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows8point1(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows8Or8point1(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC_EX(bool) MinIsWindows11(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows2000OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindowsXPOrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindowsVistaOrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows7OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows8Or8point1OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1511OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1607OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    //VT Support
    //(Version:1703) See:https://devblogs.microsoft.com/commandline/windows-10-creators-update-whats-new-in-bashwsl-windows-console/
    EXPORT_FUNC MinIsWindows10CreatorsOrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    //(Version:1709)
    EXPORT_FUNC MinIsWindows10FallCreatorsOrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1803OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1809OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1903OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version1909OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version2004OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version20H2OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC MinIsWindows10Version21H1OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC_EX(bool) MinIsWindows10Version21H2OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    EXPORT_FUNC_EX(bool) MinIsWindows11OrLater(uint MajorVer, uint MinorVer, uint BuildNumber);

    //See:https://docs.microsoft.com/en-us/windows/win32/sysinfo/operating-system-version
    //Windows 10 Version:https://en.wikipedia.org/wiki/Windows_10_version_history
    //Windows 11 Version:https://en.wikipedia.org/wiki/Windows_11_version_history
    class WinVersion
    {
    public:
        static Singleton<WinVersion> Global;

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

        std::wstring ToString();

        bool IsWindows2000();

        bool IsWindowsXP();

        bool IsWindowsVista();

        bool IsWindows7();

        bool IsWindows8();

        bool IsWindows8point1();

        bool IsWindows8Or8point1();

        bool IsWindows10();

        bool IsWindows11();

        //==========================================

        bool IsWindows2000OrLater();

        bool IsWindowsXPOrLater();

        bool IsWindowsVistaOrLater();

        bool IsWindows7OrLater();

        bool IsWindows8Or8point1OrLater();

        //(Version:1507)
        bool IsWindows10OrLater();

        bool IsWindows10Version1511OrLater();

        bool IsWindows10Version1607OrLater();

        //VT Support
        //(Version:1703) See:https://devblogs.microsoft.com/commandline/windows-10-creators-update-whats-new-in-bashwsl-windows-console/
        bool IsWindows10CreatorsOrLater();

        //(Version:1709)
        bool IsWindows10FallCreatorsOrLater();

        bool IsWindows10Version1803OrLater();

        bool IsWindows10Version1809OrLater();

        bool IsWindows10Version1903OrLater();

        bool IsWindows10Version1909OrLater();

        bool IsWindows10Version2004OrLater();

        bool IsWindows10Version20H2OrLater();

        bool IsWindows10Version21H1OrLater();

        bool IsWindows10Version21H2OrLater();

        bool IsWindows11OrLater();

        WinVersion();
    };

    extern WinVersion& winVersion;
}