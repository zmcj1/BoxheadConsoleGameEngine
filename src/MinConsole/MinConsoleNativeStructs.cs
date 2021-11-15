﻿using System;
using System.Runtime.InteropServices;

namespace MinConsole
{
    //This class is auto generated by NativeFunctionTranslator.
    public static partial class MinConsoleNativeStructs
    {
        public const int MCI_MIN_VOLUME = 0;

        public const int MCI_MAX_VOLUME = 1000;

        public const int MCI_SLOW_SPEED = 500;

        public const int MCI_NORMAL_SPEED = 1000;

        public const int MCI_FAST_SPEED = 2000;

        public enum MCIAudioMode
        {
            Unknown = 0,    //unknown
            NotReady = 1,   //even I dont know when will return this value
            Paused = 2,     //paused
            Playing = 3,    //is playing
            Stopped = 4,    //when audio is not opened or finished.
        }

        public enum ConsoleType
        {
            Unknown = 0,
            WindowsLegacyConsole = 1,
            WindowsConsole = 2,
            WindowsTerminal = 4,
        }

        public enum StdHandleType
        {
            Input = 1,
            Output = 2,
        }

        public enum ConsoleFile
        {
            Read = 1,
            Write = 2,
        }

        public enum CharWidth
        {
            Unknown = 0,
            Half = 1,
            Full = 2,
        }

        public enum ConsoleColor
        {
            BLACK = 0,
            DARKBLUE = 1,
            DARKGREEN = 2,
            DARKCYAN = 3,
            DARKRED = 4,
            DARKMAGENTA = 5,
            DARKYELLOW = 6,
            GRAY = 7,
            DARKGRAY = 8,
            BLUE = 9,
            GREEN = 10,
            CYAN = 11,
            RED = 12,
            MAGENTA = 13,
            YELLOW = 14,
            WHITE = 15,
        }

        public enum MouseWheelDirection
        {
            None = 0,
            Up = 1,     //The mouse wheel turns away from the player
            Down = 2,   //The mouse wheel turns towards the player
        }

        public enum CheckSizeResult
        {
            OK = 1,
            X = 2,
            Y = 3,
        }

        public enum MouseAxis
        {
            MOUSE_X = 1,
            MOUSE_Y = 2,
        }

        public enum MessageBoxButtons
        {
            OK = 1,
            OKCANCEL,
            YESNO,
            YESNOCANCEL,
        }

        public enum MessageBoxDefaultButton
        {
            First = 1,
            Second,
            Third,
        }

        public enum MessageBoxIcon
        {
            Warning = 1,
            Information,
            Error,
        }

        public enum MessageBoxResult
        {
            OK = 1,
            YES,
            NO,
            CANCEL,
        }

        public enum TerminalColor
        {
            Black = 0,
            DarkBlue = 4,
            DarkGreen = 2,
            DarkCyan = 6,
            DarkRed = 1,
            DarkMagenta = 5,
            DarkYellow = 3,
            Gray = 7,
            DarkGray = 8,
            Blue = 12,
            Green = 10,
            Cyan = 14,
            Red = 9,
            Magenta = 13,
            Yellow = 11,
            White = 15,
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct MCIAudio
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)] public string Path;  //Absolute path
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)] public string Extension;   //File extension
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)] public string Alias;       //Similar to a unique ID
            public int TotalMilliSecond;  //total milliSecond of this audio
            public int Minute;            //minute part of this audio
            public int Second;            //second part of this audio
            public int MilliSecond;       //milliSecond part of this audio
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleColorPair
        {
            public ConsoleColor foreColor;
            public ConsoleColor backColor;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct Color24
        {
            public byte r;
            public byte g;
            public byte b;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct Color32
        {
            public byte r;
            public byte g;
            public byte b;
            public byte a;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleInputMode
        {
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_PROCESSED_INPUT;               //default is TRUE(recommend to FALSE to avoid pressing CTRL+C to close the console program)
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_LINE_INPUT;                    //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_ECHO_INPUT;                    //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_WINDOW_INPUT;                  //default is FALSE(recommend to TRUE)
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_MOUSE_INPUT;                   //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_INSERT_MODE;                   //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_QUICK_EDIT_MODE;               //default is TRUE(recommend to FALSE)
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_EXTENDED_FLAGS;                //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_AUTO_POSITION;                 //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_VIRTUAL_TERMINAL_INPUT;        //default is FALSE
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleOutputMode
        {
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_PROCESSED_OUTPUT;              //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_WRAP_AT_EOL_OUTPUT;            //default is TRUE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_VIRTUAL_TERMINAL_PROCESSING;   //default is FALSE(recommend to TRUE, If want to use the VT100 sequence)
            [MarshalAs(UnmanagedType.I1)] public bool _DISABLE_NEWLINE_AUTO_RETURN;          //default is FALSE
            [MarshalAs(UnmanagedType.I1)] public bool _ENABLE_LVB_GRID_WORLDWIDE;            //default is FALSE
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleMode
        {
            public ConsoleInputMode inputMode;
            public ConsoleOutputMode outputMode;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleSession
        {
            public IntPtr consoleWindow;
            public IntPtr consoleInput;
            public IntPtr consoleOutput;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleFont
        {
            public uint FontIndex;
            public COORD FontSize;
            public uint FontFamily;
            public uint FontWeight; //Over 400 is bold
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)] public string FaceName;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleMouseInputRecord
        {
            [MarshalAs(UnmanagedType.I1)] public bool moved;                         //Whether the mouse is moving
            [MarshalAs(UnmanagedType.I1)] public bool doubleClick;                   //Double click
            public COORD position;                     //The unit is cell
            public MouseWheelDirection mouseWheelDir;  //Mouse wheel direction
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleKeyboardInputRecord
        {
            public char KeyChar;
            public ushort VirtualKey;
            [MarshalAs(UnmanagedType.I1)] public bool _RIGHT_ALT_PRESSED;        // the right alt key is pressed.
            [MarshalAs(UnmanagedType.I1)] public bool _LEFT_ALT_PRESSED;         // the left alt key is pressed.
            [MarshalAs(UnmanagedType.I1)] public bool _RIGHT_CTRL_PRESSED;       // the right ctrl key is pressed.
            [MarshalAs(UnmanagedType.I1)] public bool _LEFT_CTRL_PRESSED;        // the left ctrl key is pressed.
            [MarshalAs(UnmanagedType.I1)] public bool _SHIFT_PRESSED;            // the shift key is pressed.
            [MarshalAs(UnmanagedType.I1)] public bool _NUMLOCK_ON;               // the numlock light is on.
            [MarshalAs(UnmanagedType.I1)] public bool _SCROLLLOCK_ON;            // the scrolllock light is on.
            [MarshalAs(UnmanagedType.I1)] public bool _CAPSLOCK_ON;              // the capslock light is on.
            [MarshalAs(UnmanagedType.I1)] public bool _ENHANCED_KEY;             // the key is enhanced.
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct ConsoleKeyInfo
        {
            public char KeyChar;         //character
            public ushort VirtualKey;     //virtual key code
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public partial struct MinTimer
        {
            public long start;
            public long stop;
            public long frequency;
        }

        public delegate void OnReadConsoleMouseInputRecord(ConsoleMouseInputRecord mouseInput);

        public delegate void OnReadConsoleKeyboardInputRecord(ConsoleKeyboardInputRecord keyboardInput);

        public delegate void OnConsoleOutputBufferChanged(COORD newSize);

    }
}
