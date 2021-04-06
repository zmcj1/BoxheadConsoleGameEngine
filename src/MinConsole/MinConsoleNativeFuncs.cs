﻿using System;
using System.Runtime.InteropServices;
using static MinConsole.MinConsoleNativeStructs;

namespace MinConsole
{
    //This class is auto generated by NativeFunctionTranslator.
    internal static class MinConsoleNativeFuncs
    {
        //>>>insert_here<<<
        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinReadFromClipboard(ref string data);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinFreeClipboardData(string data);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinWriteToClipboard(string data, int charCount);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinIsUsingLegacyConsole(ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinUseLegacyConsole(bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinInitConsoleSession(ref ConsoleSession cons);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinEnableConsoleVT(IntPtr consoleInput, IntPtr consoleOutput);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsolePalette(IntPtr consoleOutput, uint index, ref Color24 color);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsolePalette(IntPtr consoleOutput, uint index, Color24 color);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleMode(IntPtr consoleInput, IntPtr consoleOutput, ref ConsoleMode consoleMode);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleMode(IntPtr consoleInput, IntPtr consoleOutput, ConsoleMode consoleMode);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleFont(IntPtr consoleOutput, ref ConsoleFont consoleFont);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleFont(IntPtr consoleOutput, ConsoleFont consoleFont);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleWindowSize(IntPtr consoleOutput, ref POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleWindowSize(IntPtr consoleOutput, POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleBufferSize(IntPtr consoleOutput, ref POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleBufferSize(IntPtr consoleOutput, POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleForeColor(IntPtr consoleOutput, ref ConsoleColor foreColor);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleBackColor(IntPtr consoleOutput, ref ConsoleColor backColor);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleForeColor(IntPtr consoleOutput, ConsoleColor foreColor);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleBackColor(IntPtr consoleOutput, ConsoleColor backColor);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleCursorPos(IntPtr consoleOutput, ref COORD pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleCursorPos(IntPtr consoleOutput, COORD pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinReadConsole(IntPtr consoleInput, string buffer, int charCount);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinReadConsoleInput(IntPtr consoleInput, OnReadConsoleMouseInputRecord callback1, OnReadConsoleKeyboardInputRecord callback2);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinWriteConsole(IntPtr consoleOutput, string buffer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinWriteConsoleOutput(IntPtr consoleOutput, ref CHAR_INFO charInfos, short x, short y, short width, short height);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinWriteConsoleOutputCharacter(IntPtr consoleOutput, string str, int charCount, COORD pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinCreateConsoleScreenBuffer(ref IntPtr consoleOutput);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleActiveScreenBuffer(IntPtr consoleOutput);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinCloseConsoleScreenBuffer(IntPtr consoleOutput);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinCreateFile( );

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinWriteFile( );

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinReadFile( );

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetCharWidth(IntPtr consoleWindow, IntPtr consoleOutput, char c, ref CharWidth cw);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetTitle(string titleBuffer, int sizeOfBuffer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetTitle(string titleBuffer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleCursorVisible(IntPtr consoleOutput, ref bool visible);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleCursorVisible(IntPtr consoleOutput, bool visible);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinClear(IntPtr consoleOutput);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleCtrlHandler(PHANDLER_ROUTINE handler, bool add);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetKey(int virtualKey, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetKeyDown(int virtualKey, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetKeyUp(int virtualKey, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetKeyPressed(int virtualKey, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetKeyState(int virtualKey, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinCheckMouseAxis( );

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinResetMouseAxis( );

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetMouseAxis(MouseAxis axis, ref int diff);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetRandomValue(uint minimum, uint maximum, ref uint value);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinInitTimer(ref MinTimer timer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinStartTimer(ref MinTimer timer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinStopTimer(ref MinTimer timer);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinTimeTimer(ref MinTimer timer, ref double deltaTime, int iterations);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetFuncFromDll(string dllName, ref char funcName, ref object funcPtr);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetConsoleIcon(ref ICON hIcon);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetForegroundWindow(IntPtr windowHandle);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetConsoleWindow(IntPtr windowHandle);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetWindowPos(IntPtr windowHandle, ref POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetWindowPos(IntPtr windowHandle, POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetWindowSize(IntPtr windowHandle, ref POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetWindowSize(IntPtr windowHandle, POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetDesktopSize(ref POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetClientSize(IntPtr windowHandle, ref POINT size);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetMousePos(ref POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetMappedMousePos(IntPtr windowHandle, ref POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetMouseInClient(IntPtr windowHandle, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetWindowInFocus(IntPtr windowHandle, ref bool yes);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetCenterPosOfWindowInDesktop(IntPtr windowHandle, ref POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetCenterPosOfWindow(IntPtr windowHandle, ref POINT pos);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetWindowMenuVisibility(IntPtr windowHandle, bool visible);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinMaximizeWindow(IntPtr windowHandle, bool maximize);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetWindowAlpha(IntPtr windowHandle, ref byte alpha);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinSetWindowAlpha(IntPtr windowHandle, byte alpha);

        [DllImport("MinConsoleNative.dll", CallingConvention = CallingConvention.StdCall, SetLastError = true, CharSet = CharSet.Unicode)]
        public extern static bool MinGetWinVersion(ref uint MajorVer, ref uint MinorVer, ref uint BuildNumber);

    }
}
