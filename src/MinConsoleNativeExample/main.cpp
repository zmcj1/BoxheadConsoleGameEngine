#include "../MinConsoleNative/MinConsoleNative.h"
using namespace MinConsoleNative;

class Example : public ConsoleEngine
{
    void OnUpdate(float deltaTime)
    {
        ConsoleEngine::OnUpdate(deltaTime);
        if (Input::GetKey('C'))
        {
            Console::Global.GetInstance().Clear();
        }
    }
};

int main()
{
    Example consoleEngine;
    if (consoleEngine.consoleType == ConsoleType::WindowsConsole)
    {
        consoleEngine.ConstructConsole(L"my console program", PaletteType::Legacy, 120, 30, 8, 16, L"Consolas", 400);
    }
    else if (consoleEngine.consoleType == ConsoleType::WindowsTerminal)
    {
        consoleEngine.ConstructTerminal(L"my terminal program");
    }
    consoleEngine.StartLoop();
    return 0;
}