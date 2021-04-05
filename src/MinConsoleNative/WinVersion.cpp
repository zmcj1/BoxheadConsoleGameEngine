#include "WinVersion.h"
#include "UnusualMethods.h"

namespace MinConsoleNative
{
    EXPORT_FUNC MinGetWinVersion(uint* MajorVer, uint* MinorVer, uint* BuildNumber)
    {
        FARPROC func;
        bool suc = MinGetFuncFromDll(L"ntdll.dll", "RtlGetNtVersionNumbers", &func);
        if (!suc) return false;

        typedef void (WINAPI* pfRTLGETNTVERSIONNUMBERS)(DWORD*, DWORD*, DWORD*);

        DWORD dwMajorVer{}, dwMinorVer{}, dwBuildNumber{};

        ((pfRTLGETNTVERSIONNUMBERS)func)(&dwMajorVer, &dwMinorVer, &dwBuildNumber);
        dwBuildNumber &= 0x0ffff;

        *MajorVer = dwMajorVer;
        *MinorVer = dwMinorVer;
        *BuildNumber = dwBuildNumber;

        return true;
    }

    WinVersion::WinVersion()
    {
        majorVer = 0;
        minorVer = 0;
        buildNumber = 0;

        MinGetWinVersion(&majorVer, &minorVer, &buildNumber);
    }

    bool WinVersion::IsWindows2000()
    {
        return MajorVer() == 5 && MinorVer() == 0;
    }

    bool WinVersion::IsWindowsXP()
    {
        return MajorVer() == 5 && MinorVer() == 1;
    }

    bool WinVersion::IsWindowsVista()
    {
        return MajorVer() == 6 && MinorVer() == 0;
    }

    bool WinVersion::IsWindows7()
    {
        return MajorVer() == 6 && MinorVer() == 1;
    }

    bool WinVersion::IsWindows8()
    {
        return MajorVer() == 6 && MinorVer() == 2;
    }

    bool WinVersion::IsWindows8point1()
    {
        return MajorVer() == 6 && MinorVer() == 3;
    }

    bool WinVersion::IsWindows8Or8point1()
    {
        return IsWindows8() || IsWindows8point1();
    }

    bool WinVersion::IsWindows10()
    {
        return MajorVer() == 10;
    }

    bool WinVersion::IsWindows2000OrLater()
    {
        return MajorVer() >= 5;
    }

    bool WinVersion::IsWindowsXPOrLater()
    {
        if (MajorVer() > 5)
            return true;
        else if (MajorVer() == 5 && MinorVer() >= 1)
            return true;
        else return false;
    }

    bool WinVersion::IsWindowsVistaOrLater()
    {
        return MajorVer() >= 6;
    }

    bool WinVersion::IsWindows7OrLater()
    {
        if (MajorVer() > 6)
            return true;
        else if (MajorVer() == 6 && MinorVer() >= 1)
            return true;
        else return false;
    }

    bool WinVersion::IsWindows8Or8point1OrLater()
    {
        if (MajorVer() > 6)
            return true;
        else if (MajorVer() == 6 && MinorVer() > 1)
            return true;
        else return false;
    }

    bool WinVersion::IsWindows10OrLater()
    {
        return MajorVer() >= 10;
    }

    bool WinVersion::IsWindows10CreatorsOrLater()
    {
        if (MajorVer() > 10)
            return true;
        else if (MajorVer() == 10 && MinorVer() > 0)
            return true;
        else if (MajorVer() == 10 && MinorVer() == 0 && BuildNumber() >= 15063)
            return true;
        else return false;
    }

    bool WinVersion::IsWindows10FallCreatorsOrLater()
    {
        if (MajorVer() > 10)
            return true;
        else if (MajorVer() == 10 && MinorVer() > 0)
            return true;
        else if (MajorVer() == 10 && MinorVer() == 0 && BuildNumber() >= 16299)
            return true;
        else return false;
    }

    bool WinVersion::IsWindows10Version1809OrLater()
    {
        if (MajorVer() > 10)
            return true;
        else if (MajorVer() == 10 && MinorVer() > 0)
            return true;
        else if (MajorVer() == 10 && MinorVer() == 0 && BuildNumber() >= 17763)
            return true;
        else return false;
    }

    Singleton<WinVersion> winVersionInstance;
}