using System;
using System.Threading;

using static MinConsole.MinConsoleNativeStructs;

namespace MinConsole
{
    class Program
    {
        public static void OnReadConsoleMouseInputRecordCallback(ConsoleMouseInputRecord mouseInput)
        {
            Console.WriteLine($"{mouseInput.position.X } {mouseInput.position.Y}");
        }

        public static void OnReadConsoleKeyboardInputRecordCallback(ConsoleKeyboardInputRecord keyboardInput)
        {

        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            ConsoleSession session = MinConsoleNativeWrapper.InitConsoleSession();
            bool s = MinConsoleNativeWrapper.EnableConsoleVT(session.consoleInput, session.consoleOutput);

            CharWidth charWidth = CharWidth.Unknown;
            MinConsoleNativeFuncs.MinGetCharWidth(session.consoleWindow, session.consoleOutput, '吊', ref charWidth);

            ConsoleMode mode = new ConsoleMode(false);

            MinConsoleNativeFuncs.MinSetConsoleMode(session.consoleInput,
                session.consoleOutput, mode);

            uint major = 0, minor = 0, build = 0;
            MinConsoleNativeFuncs.MinGetWinVersion(ref major, ref minor, ref build);
            bool isWindows8 = MinConsoleNativeFuncs.MinIsWindows8(major, minor, build);
            bool isWindows10 = MinConsoleNativeFuncs.MinIsWindows10(major, minor, build);

            while (true)
            {
                bool r = MinConsoleNativeFuncs.MinReadConsoleInput(session.consoleInput,
                    OnReadConsoleMouseInputRecordCallback,
                    OnReadConsoleKeyboardInputRecordCallback);

                Thread.Sleep(100);
            }
            
            Console.ReadKey();
        }
    }
}
