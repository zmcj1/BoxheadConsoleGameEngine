using System;
using System.IO;
using System.Threading;

using static MinConsole.MinConsoleNativeFuncs;
using static MinConsole.MinConsoleNativeStructs;
using static MinConsole.MinConsoleNativeWrapper;

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
            IntPtr intPtr = MinGetConsoleWindow();
            Console.ReadKey();
        }
    }
}
