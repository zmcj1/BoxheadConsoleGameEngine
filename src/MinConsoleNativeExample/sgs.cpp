#include "..\MinConsoleNative\MinConsoleNative.h"
#include <string>

using namespace std;

int main()
{
    ConsoleEngine ce;
    ce.ConstructConsole(L"三国杀抽卡", PaletteType::Legacy, 60, 30, FontSize::_10x20);

    wstring configPath = L"../../res/sgs.txt";
    if (!File::Exists(configPath))
    {
        console.WriteLine(L"找不到sgs.txt的路径！", ConsoleColor::RED);
        console.ReadLine();
        return -1;
    }

    console.ReadKey();
    return 0;
}