#include "../MinConsoleNative/MinConsoleNative.h"
using namespace MinConsoleNative;

class Example : public ConsoleEngine
{
    void OnUpdate(float deltaTime)
    {
        ConsoleEngine::OnUpdate(deltaTime);
    }
};

int main()
{
    Example consoleEngine;
    consoleEngine.ConstructConsole(L"my console program", PaletteType::Legacy, 120, 30, 8, 16);
    consoleEngine.StartLoop();
    return 0;
}