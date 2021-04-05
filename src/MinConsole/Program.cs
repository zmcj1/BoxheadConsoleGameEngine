using System;

using static MinConsole.MinConsoleNativeStructs;

namespace MinConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            string data = MinConsoleNativeWrapper.ReadFromClipboard();
            Console.WriteLine(data);

            bool legacy = MinConsoleNativeWrapper.IsUsingLegacyConsole();
            Console.WriteLine(legacy);

            ConsoleSession session = MinConsoleNativeWrapper.InitConsoleSession();
            bool s = MinConsoleNativeWrapper.EnableConsoleVT(session.consoleInput, session.consoleOutput);

            MinConsoleNativeFuncs.MinSetConsoleCursorPos(session.consoleOutput, new COORD(20, 10));

            CharWidth charWidth = CharWidth.Unknown;
            MinConsoleNativeFuncs.MinGetCharWidth(session.consoleWindow, session.consoleOutput, '吊', ref charWidth);

            Console.ReadKey();
        }
    }
}
