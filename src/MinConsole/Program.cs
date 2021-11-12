using System;
using System.IO;
using System.Runtime.InteropServices;
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

        //必须添加该特性保证能够正常使用MCI接口
        [STAThread]
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

            //string content = MinReadConsole(inputHandle);
            //Console.WriteLine(content);

            string rrr = MinMCIGetErrorString();
            //MCIAudio* audio = MinInitMCIAudio("C:\\Users\\16692\\source\\repos\\MinConsole\\res\\[CSO] Lobby Theme.mp3");

            MinStructTest(out MCIAudio s1);
            IntPtr s2_pointer = MinStructTest2();
            MCIAudio s2 = Marshal.PtrToStructure<MCIAudio>(s2_pointer);
            MCIAudio s3 = MinStructTest3();

            //final test:
            IntPtr pointer = MinInitMCIAudio("C:\\Users\\16692\\source\\repos\\MinConsole\\res\\[CSO] Lobby Theme.mp3");
            MCIAudio audio = Marshal.PtrToStructure<MCIAudio>(pointer);

            Console.ReadLine();
        }
    }
}
