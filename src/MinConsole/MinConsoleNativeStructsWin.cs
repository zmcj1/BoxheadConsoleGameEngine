using System;
using System.Runtime.InteropServices;

namespace MinConsole
{
    //This class is hand-written by Min.
    public static partial class MinConsoleNativeStructs
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int x;
            public int y;

            public POINT(int x, int y)
            {
                this.x = x;
                this.y = y;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct COORD
        {
            public short X;
            public short Y;

            public COORD(short X, short Y)
            {
                this.X = X;
                this.Y = Y;
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct CHAR_INFO
        {
            public char UnicodeChar;
            public ushort Attributes;

            public CHAR_INFO(char UnicodeChar, ushort Attributes)
            {
                this.UnicodeChar = UnicodeChar;
                this.Attributes = Attributes;
            }
        }
    }
}