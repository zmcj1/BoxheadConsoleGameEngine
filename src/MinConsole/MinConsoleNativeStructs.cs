using System;
using System.Runtime.InteropServices;

namespace MinConsole
{
    public static class MinConsoleNativeStructs
    {
        public enum MouseAxis : int
        {
            MOUSE_X = 1,
            MOUSE_Y = 2,
        }

        public enum CharWidth : int
        {
            Unknown = 0,
            Half = 1,
            Full = 2,
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int x;
            public int y;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct MinTimer
        {
            public long start;
            public long stop;
            public long frequency;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct ICON
        {
            public int unused;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleSession
        {
            public IntPtr consoleWindow;
            public IntPtr consoleInput;
            public IntPtr consoleOutput;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct Color24
        {
            public uint r;
            public uint g;
            public uint b;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleInputMode
        {
            public bool _ENABLE_PROCESSED_INPUT;               //default is TRUE(recommend to FALSE to avoid pressing CTRL+C to close the console program)
            public bool _ENABLE_LINE_INPUT;                    //default is TRUE
            public bool _ENABLE_ECHO_INPUT;                    //default is TRUE
            public bool _ENABLE_WINDOW_INPUT;                  //default is FALSE(recommend to TRUE)
            public bool _ENABLE_MOUSE_INPUT;                   //default is TRUE
            public bool _ENABLE_INSERT_MODE;                   //default is TRUE
            public bool _ENABLE_QUICK_EDIT_MODE;               //default is TRUE(recommend to FALSE)
            public bool _ENABLE_EXTENDED_FLAGS;                //default is TRUE
            public bool _ENABLE_AUTO_POSITION;                 //default is TRUE
            public bool _ENABLE_VIRTUAL_TERMINAL_INPUT;        //default is FALSE
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleOutputMode
        {
            public bool _ENABLE_PROCESSED_OUTPUT;              //default is TRUE
            public bool _ENABLE_WRAP_AT_EOL_OUTPUT;            //default is TRUE
            public bool _ENABLE_VIRTUAL_TERMINAL_PROCESSING;   //default is FALSE(recommend to TRUE, If want to use the VT100 sequence)
            public bool _DISABLE_NEWLINE_AUTO_RETURN;          //default is FALSE
            public bool _ENABLE_LVB_GRID_WORLDWIDE;            //default is FALSE
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleMode
        {
            public ConsoleInputMode inputMode;
            public ConsoleOutputMode outputMode;
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct COORD
        {
            public short X;
            public short Y;

            public COORD(short x, short y)
            {
                this.X = x;
                this.Y = y;
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct ConsoleFont
        {
            public uint FontIndex;
            public COORD FontSize;
            public uint FontFamily;
            public uint FontWeight;
            public string FaceName;
        };
    }
}