namespace MinConsole
{
    using System;
    using System.Runtime.InteropServices;

    public static class Win32
    {
        public const string USER32 = "user32.dll";

        public const string KERNEL32 = "kernel32.dll";

        public const string WINMM = "winmm.dll";

        [DllImport(WINMM, SetLastError = true, CharSet = CharSet.Unicode)]
        public static extern uint mciSendString(string lpstrCommand, string lpstrReturnString, uint uReturnLength, IntPtr hwndCallback);

        [DllImport(USER32, SetLastError = true)]
        public static extern short GetAsyncKeyState(int vKey);

        [DllImport(KERNEL32, SetLastError = true)]
        public static extern bool QueryPerformanceFrequency(out long lpFrequency);

        [DllImport(KERNEL32, SetLastError = true)]
        public static extern bool QueryPerformanceCounter(out long lpPerformanceCount);
    }
}