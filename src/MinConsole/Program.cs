using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

using ConsoleColor = MinConsole.MinConsoleNativeStructs.ConsoleColor;
using ConsoleKeyInfo = MinConsole.MinConsoleNativeStructs.ConsoleKeyInfo;

using static MinConsole.MinConsoleNativeFuncs;
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

        //必须添加该特性保证能够正常使用MCI接口
        [STAThread]
        static void Main(string[] args)
        {
            IntPtr audioPool = MinCreatAudioPool("C:\\Users\\16692\\source\\repos\\MinConsole\\res\\562_Weapon.UZI.Fire.mp3", 10);

            while (true)
            {
                if (MinGetKey('A'))
                {
                    MinPlayOneShot(audioPool, 1.0);
                }
                if (MinGetKey((int)ConsoleKey.Escape))
                {
                    break;
                }
                MinCleanAudioPool(audioPool);
                Thread.Sleep(100);
            }

            MinDestroyAudioPool(audioPool);
            return;

            bool win11 = WinVersion.IsWindows11OrLater();

            string shortPathName = MinToShortPathName("C:\\Users\\16692\\source\\repos\\MinConsole\\res\\[CSO] Lobby Theme.mp3");
            bool ok1 = MinMCISendString($"open {shortPathName}");
            bool ok2 = MinMCISendStringEx($"status {shortPathName} length", out string rs);

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
            IntPtr outputHandle = MinGetStdHandle(StdHandleType.Output);

            CHAR_INFO[] infos = new CHAR_INFO[20];
            for (int i = 0; i < 20; i++)
            {
                infos[i] = new CHAR_INFO('1', MinConsoleColorToUshort(ConsoleColor.BLACK, ConsoleColor.GRAY));
            }
            MinWriteConsoleOutput(outputHandle, infos, 0,0, 10, 2);
            ushort[] colors = new ushort[20];
            for (int i = 0; i < 20; i++)
            {
                colors[i] = MinConsoleColorToUshort(ConsoleColor.GRAY, ConsoleColor.BLACK);
            }
            MinWriteConsoleOutputAttribute(outputHandle, colors, 20, new COORD(0, 0));

            MinWriteFile(outputHandle, "nihaoma123");
            string str = MinReadFile(inputHandle);

            //string content = MinReadConsole(inputHandle);
            //Console.WriteLine(content);

            MinStructTest(out MCIAudio s1);
            IntPtr s2_pointer = MinStructTest2();
            MCIAudio s2 = Marshal.PtrToStructure<MCIAudio>(s2_pointer);
            MCIAudio s3 = MinStructTest3();

            MinWriteToClipboard("你好世界");
            string data = MinReadFromClipboard();

            bool enableVTSuccess = MinEnableConsoleVT(outputHandle);
            ConsoleFont font = MinGetConsoleFont(outputHandle);

            //audio test:
            Audio audio = new Audio("C:\\Users\\16692\\source\\repos\\MinConsole\\res\\[CSO] Lobby Theme.mp3");
            audio.Play(true, false);

            //MinReadConsoleInput test:
            int size = Marshal.SizeOf<ConsoleInputMode>();
            ConsoleInputMode cim = MinGetConsoleInputMode(inputHandle);
            cim._ENABLE_QUICK_EDIT_MODE = false;
            cim._ENABLE_WINDOW_INPUT = true;
            MinSetConsoleInputMode(inputHandle, cim);
            while (true)
            {
                MinReadConsoleInput(inputHandle,
                    OnReadConsoleMouseInputRecordCallback,
                    OnReadConsoleKeyboardInputRecordCallback, null);
                //COORD pos = MinGetConsoleCursorPos(outputHandle);
                //Console.WriteLine($"{pos.X } {pos.Y}");
                Thread.Sleep(100);
            }

            Win32.QueryPerformanceFrequency(out long f);
            Win32.QueryPerformanceCounter(out long c);
            while (true)
            {
                if ((Win32.GetAsyncKeyState('A') & 0x8000) != 0)
                {
                    //Console.WriteLine("1"); //现在此API会自动改变屏幕缓冲区左上角
                    MinWriteLine1(outputHandle, "1");
                }
                Thread.Sleep(100);
            }

            Console.ReadLine();
        }
    }
}
