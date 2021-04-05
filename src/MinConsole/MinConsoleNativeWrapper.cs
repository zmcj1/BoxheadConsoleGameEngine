using System;

using static MinConsole.MinConsoleNativeFuncs;
using static MinConsole.MinConsoleNativeStructs;

namespace MinConsole
{
    public static class MinConsoleNativeWrapper
    {
        public static string ReadFromClipboard()
        {
            string tempData = null;
            MinReadFromClipboard(ref tempData);
            string data = new string(tempData);
            //free tempData
            FreeClipboardData(tempData);
            return data;
        }

        //Dont use this function!
        public static bool FreeClipboardData(string data)
        {
            return MinFreeClipboardData(data);
        }

        public static bool WriteToClipboard(string data)
        {
            return MinWriteToClipboard(data, data.Length);
        }

        public static bool IsUsingLegacyConsole()
        {
            bool yes = false;
            MinIsUsingLegacyConsole(ref yes);
            return yes;
        }

        public static bool UseLegacyConsole(bool yes)
        {
            return MinUseLegacyConsole(yes);
        }

        public static ConsoleSession InitConsoleSession()
        {
            ConsoleSession session = new ConsoleSession();
            MinInitConsoleSession(ref session);
            return session;
        }

        public static bool EnableConsoleVT(IntPtr consoleInput, IntPtr consoleOutput)
        {
            return MinEnableConsoleVT(consoleInput, consoleOutput);
        }

        //public static bool MinGetConsolePalette(ref ConsoleSession cons, uint index, ref Color24 color);

        //public static bool MinSetConsolePalette(ref ConsoleSession cons, uint index, Color24 color);

        //public static bool MinGetConsoleMode(ref ConsoleSession cons, ref ConsoleMode consoleMode);

        //public static bool MinSetConsoleMode(ref ConsoleSession cons, ConsoleMode consoleMode);

        //public static bool MinGetConsoleFont(ref ConsoleSession cons, ref ConsoleFont consoleFont);

        //public static bool MinSetConsoleFont(ref ConsoleSession cons, ConsoleFont consoleFont);

        //public static bool MinGetKey(int virtualKey, ref bool yes);

        //public static bool MinGetKeyDown(int virtualKey, ref bool yes);

        //public static bool MinGetKeyUp(int virtualKey, ref bool yes);

        //public static bool MinGetKeyPressed(int virtualKey, ref bool yes);

        //public static bool MinGetKeyState(int virtualKey, ref bool yes);

        //public static bool MinCheckMouseAxis();

        //public static bool MinResetMouseAxis();

        //public static bool MinGetMouseAxis(MouseAxis axis, ref int diff);

        //public static bool MinGetRandomValue(uint minimum, uint maximum, ref uint value);

        //public static bool MinInitTimer(ref MinTimer timer);

        //public static bool MinStartTimer(ref MinTimer timer);

        //public static bool MinStopTimer(ref MinTimer timer);

        //public static bool MinTimeTimer(ref MinTimer timer, ref double deltaTime, int iterations);

        //public static bool MinGetFuncFromDll(string dllName, ref char funcName, ref object funcPtr);

        //public static bool MinSetConsoleIcon(ref ICON hIcon);

        //public static bool MinGetForegroundWindow(IntPtr windowHandle);

        //public static bool MinGetConsoleWindow(IntPtr windowHandle);

        //public static bool MinGetWindowPos(IntPtr windowHandle, ref POINT pos);

        //public static bool MinSetWindowPos(IntPtr windowHandle, POINT pos);

        //public static bool MinGetWindowSize(IntPtr windowHandle, ref POINT size);

        //public static bool MinSetWindowSize(IntPtr windowHandle, POINT size);

        //public static bool MinGetDesktopSize(ref POINT size);

        //public static bool MinGetClientSize(IntPtr windowHandle, ref POINT size);

        //public static bool MinGetMousePos(ref POINT pos);

        //public static bool MinGetMappedMousePos(IntPtr windowHandle, ref POINT pos);

        //public static bool MinGetMouseInClient(IntPtr windowHandle, ref bool yes);

        //public static bool MinGetWindowInFocus(IntPtr windowHandle, ref bool yes);

        //public static bool MinGetCenterPosOfWindowInDesktop(IntPtr windowHandle, ref POINT pos);

        //public static bool MinGetCenterPosOfWindow(IntPtr windowHandle, ref POINT pos);

        //public static bool MinSetWindowMenuVisibility(IntPtr windowHandle, bool visible);

        //public static bool MinMaximizeWindow(IntPtr windowHandle, bool maximize);

        //public static bool MinGetWindowAlpha(IntPtr windowHandle, ref byte alpha);

        //public static bool MinSetWindowAlpha(IntPtr windowHandle, byte alpha);

        //public static bool MinGetWinVersion(ref uint MajorVer, ref uint MinorVer, ref uint BuildNumber);
    }
}