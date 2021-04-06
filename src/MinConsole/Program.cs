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
