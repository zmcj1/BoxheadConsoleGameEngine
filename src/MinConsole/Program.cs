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
            string test = null;

            test = MinVTForeColor(new Color24() { r = 255, g = 33, b = 22 });
            Console.Write(test);

            test = MinVTGetDeviceAttributes();
            Console.WriteLine(test);

            MinSetTitle("nihao");
            Console.WriteLine(MinGetTitle());

            test = MinVTResetStyle();
            Console.Write(test);

            IntPtr inputHandle = MinGetStdHandle(StdHandleType.Input);

            string content = MinReadConsole(inputHandle);
            Console.WriteLine(content);

            Console.ReadLine();
        }
    }
}
