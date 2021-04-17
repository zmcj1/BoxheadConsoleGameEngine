#include "../MinConsoleNative/MinConsoleNative.h"
using namespace MinConsoleNative;

int main()
{
    ConsoleEngine consoleEngine;
    consoleEngine.ConstructConsole(L"my console program", PaletteType::Legacy, 120, 30, 8, 16);
    consoleEngine.StartLoop();
    return 0;
}