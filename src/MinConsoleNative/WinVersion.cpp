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

    EXPORT_FUNC MinIsWindows2000(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 5 && MinorVer == 0;
    }

    EXPORT_FUNC MinIsWindowsXP(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 5 && MinorVer == 1;
    }

    EXPORT_FUNC MinIsWindowsVista(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 6 && MinorVer == 0;
    }

    EXPORT_FUNC MinIsWindows7(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 6 && MinorVer == 1;
    }

    EXPORT_FUNC MinIsWindows8(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 6 && MinorVer == 2;
    }

    EXPORT_FUNC MinIsWindows8point1(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 6 && MinorVer == 3;
    }

    EXPORT_FUNC MinIsWindows8Or8point1(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MinIsWindows8(MajorVer, MinorVer, BuildNumber) ||
            MinIsWindows8point1(MajorVer, MinorVer, BuildNumber);
    }

    EXPORT_FUNC MinIsWindows10(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer == 10;
    }

    EXPORT_FUNC MinIsWindows2000OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer >= 5;
    }

    EXPORT_FUNC MinIsWindowsXPOrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 5)
            return true;
        else if (MajorVer == 5 && MinorVer >= 1)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindowsVistaOrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer >= 6;
    }

    EXPORT_FUNC MinIsWindows7OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 6)
            return true;
        else if (MajorVer == 6 && MinorVer >= 1)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows8Or8point1OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 6)
            return true;
        else if (MajorVer == 6 && MinorVer > 1)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        return MajorVer >= 10;
    }

    EXPORT_FUNC MinIsWindows10Version1511OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 10586)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version1607OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 14393)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10CreatorsOrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 15063)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10FallCreatorsOrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 16299)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version1803OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 17134)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version1809OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 17763)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version1903OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 18362)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version1909OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 18363)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version2004OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 19041)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version20H2OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 19042)
            return true;
        else return false;
    }

    EXPORT_FUNC MinIsWindows10Version21H1OrLater(uint MajorVer, uint MinorVer, uint BuildNumber)
    {
        if (MajorVer > 10)
            return true;
        else if (MajorVer == 10 && MinorVer > 0)
            return true;
        else if (MajorVer == 10 && MinorVer == 0 && BuildNumber >= 19043)
            return true;
        else return false;
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