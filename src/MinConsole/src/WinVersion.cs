using System;
using static MinConsole.MinConsoleNativeFuncs;

namespace MinConsole
{
    public static class WinVersion
    {
        public static uint MajorVer;
        public static uint MinorVer;
        public static uint BuildNumber;

        static WinVersion()
        {
            bool suc = MinGetWinVersion(out MajorVer, out MinorVer, out BuildNumber);
            if (!suc)
            {
                throw new Exception("MinGetWinVersion failed.");
            }
        }

        public static new string ToString()
        {
            return MajorVer.ToString() + "." + MinorVer.ToString() + "." + BuildNumber.ToString();
        }

        public static bool IsWindows2000()
        {
            return MinIsWindows2000(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindowsXP()
        {
            return MinIsWindowsXP(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindowsVista()
        {
            return MinIsWindowsVista(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows7()
        {
            return MinIsWindows7(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows8()
        {
            return MinIsWindows8(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows8point1()
        {
            return MinIsWindows8point1(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows8Or8point1()
        {
            return MinIsWindows8Or8point1(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10()
        {
            return MinIsWindows10(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows11()
        {
            return MinIsWindows11(MajorVer, MinorVer, BuildNumber);
        }

        //==========================================

        public static bool IsWindows2000OrLater()
        {
            return MinIsWindows2000OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindowsXPOrLater()
        {
            return MinIsWindowsXPOrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindowsVistaOrLater()
        {
            return MinIsWindowsVistaOrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows7OrLater()
        {
            return MinIsWindows7OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows8Or8point1OrLater()
        {
            return MinIsWindows8Or8point1OrLater(MajorVer, MinorVer, BuildNumber);
        }

        //(Version:1507)
        public static bool IsWindows10OrLater()
        {
            return MinIsWindows10OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1511OrLater()
        {
            return MinIsWindows10Version1511OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1607OrLater()
        {
            return MinIsWindows10Version1607OrLater(MajorVer, MinorVer, BuildNumber);
        }

        //VT Support
        //(Version:1703) See:https://devblogs.microsoft.com/commandline/windows-10-creators-update-whats-new-in-bashwsl-windows-console/
        public static bool IsWindows10CreatorsOrLater()
        {
            return MinIsWindows10CreatorsOrLater(MajorVer, MinorVer, BuildNumber);
        }

        //(Version:1709)
        public static bool IsWindows10FallCreatorsOrLater()
        {
            return MinIsWindows10FallCreatorsOrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1803OrLater()
        {
            return MinIsWindows10Version1803OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1809OrLater()
        {
            return MinIsWindows10Version1809OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1903OrLater()
        {
            return MinIsWindows10Version1903OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version1909OrLater()
        {
            return MinIsWindows10Version1909OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version2004OrLater()
        {
            return MinIsWindows10Version2004OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version20H2OrLater()
        {
            return MinIsWindows10Version20H2OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version21H1OrLater()
        {
            return MinIsWindows10Version21H1OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows10Version21H2OrLater()
        {
            return MinIsWindows10Version21H2OrLater(MajorVer, MinorVer, BuildNumber);
        }

        public static bool IsWindows11OrLater()
        {
            return MinIsWindows11OrLater(MajorVer, MinorVer, BuildNumber);
        }
    }
}