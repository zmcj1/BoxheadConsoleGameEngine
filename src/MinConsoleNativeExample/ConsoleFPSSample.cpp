#include "..\MinConsoleNative\MinConsoleNative.h"

class ConsoleFPS : public ConsoleEngine
{
public:
    void OnStart() override
    {

    }

    void OnUpdate(float deltaTime) override
    {

    }

    void OnDestroy() override
    {

    }
};

int main()
{
    ConsoleFPS consoleFPS;
    consoleFPS.ConstructConsole(L"Console FPS", PaletteType::Legacy, 120, 40, 6, 12, L"Consolas", FW_NORMAL);
    consoleFPS.StartLoop();
    return 0;
}