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
            bool s = MinConsoleNativeWrapper.EnableConsoleVT(ref session);

            MinConsoleNativeFuncs.MinSetConsoleCursorPos(ref session, new COORD(20, 10));

            Console.ReadKey();
        }
    }
}
