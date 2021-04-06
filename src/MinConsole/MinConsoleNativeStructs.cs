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

        public enum CtrlEvent : uint
        {
            CTRL_C_EVENT = 0,
            CTRL_BREAK_EVENT = 1,
            CTRL_CLOSE_EVENT = 2,
            CTRL_LOGOFF_EVENT = 5,
            CTRL_SHUTDOWN_EVENT = 6,
        }

        public enum MouseWheelDirection : int
        {
            None = 0,
            Up = 1,
            Down = 2,
        };

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

            public ConsoleInputMode(bool __default)
            {
                this._ENABLE_PROCESSED_INPUT = true;
                this._ENABLE_LINE_INPUT = true;
                this._ENABLE_ECHO_INPUT = true;
                this._ENABLE_WINDOW_INPUT = false;
                this._ENABLE_MOUSE_INPUT = true;
                this._ENABLE_INSERT_MODE = true;
                this._ENABLE_QUICK_EDIT_MODE = true;
                this._ENABLE_EXTENDED_FLAGS = true;
                this._ENABLE_AUTO_POSITION = true;
                this._ENABLE_VIRTUAL_TERMINAL_INPUT = false;
                if (!__default)
                {
                    //Use Standard
                    this._ENABLE_PROCESSED_INPUT = false;
                    this._ENABLE_WINDOW_INPUT = true;
                    this._ENABLE_QUICK_EDIT_MODE = false;
                }
            }
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleOutputMode
        {
            public bool _ENABLE_PROCESSED_OUTPUT;              //default is TRUE
            public bool _ENABLE_WRAP_AT_EOL_OUTPUT;            //default is TRUE
            public bool _ENABLE_VIRTUAL_TERMINAL_PROCESSING;   //default is FALSE(recommend to TRUE, If want to use the VT100 sequence)
            public bool _DISABLE_NEWLINE_AUTO_RETURN;          //default is FALSE
            public bool _ENABLE_LVB_GRID_WORLDWIDE;            //default is FALSE

            public ConsoleOutputMode(bool __default)
            {
                this._ENABLE_PROCESSED_OUTPUT = true;
                this._ENABLE_WRAP_AT_EOL_OUTPUT = true;
                this._ENABLE_VIRTUAL_TERMINAL_PROCESSING = false;
                this._DISABLE_NEWLINE_AUTO_RETURN = false;
                this._ENABLE_LVB_GRID_WORLDWIDE = false;
                if (!__default)
                {
                    //Use Standard
                    this._ENABLE_VIRTUAL_TERMINAL_PROCESSING = true;
                }
            }
        };

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleMode
        {
            public ConsoleInputMode inputMode;
            public ConsoleOutputMode outputMode;

            public ConsoleMode(bool __default)
            {
                inputMode = new ConsoleInputMode(__default);
                outputMode = new ConsoleOutputMode(__default);
            }
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

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct CHAR_INFO
        {
            public char UnicodeChar;
            public ushort Attributes;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct ConsoleMouseInputRecord
        {
            public bool moved;                         //Whether the mouse is moving
            public bool doubleClick;                   //Double click
            public COORD position;                     //The unit is cell
            public MouseWheelDirection mouseWheelDir;  //Mouse wheel direction
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct ConsoleKeyboardInputRecord
        {
            public char KeyChar;
            public ushort VirualKey;
            public bool _RIGHT_ALT_PRESSED;        // the right alt key is pressed.
            public bool _LEFT_ALT_PRESSED;         // the left alt key is pressed.
            public bool _RIGHT_CTRL_PRESSED;       // the right ctrl key is pressed.
            public bool _LEFT_CTRL_PRESSED;        // the left ctrl key is pressed.
            public bool _SHIFT_PRESSED;            // the shift key is pressed.
            public bool _NUMLOCK_ON;               // the numlock light is on.
            public bool _SCROLLLOCK_ON;            // the scrolllock light is on.
            public bool _CAPSLOCK_ON;              // the capslock light is on.
            public bool _ENHANCED_KEY;             // the key is enhanced.
        };

        //enum CtrlEvent
        public delegate bool PHANDLER_ROUTINE(uint ctrlType);

        public delegate void OnReadConsoleMouseInputRecord(ConsoleMouseInputRecord mouseInput);

        public delegate void OnReadConsoleKeyboardInputRecord(ConsoleKeyboardInputRecord keyboardInput);
    }
}