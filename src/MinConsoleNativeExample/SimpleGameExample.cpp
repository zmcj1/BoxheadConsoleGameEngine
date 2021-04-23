#include "../MinConsoleNative/MinConsoleNative.h"

class SimpleGame : public ConsoleEngine
{
    CharacterController* cc;

    void OnStart()
    {
        cc = new CharacterController(Vector2::zero, 10);
    }

    void OnUpdate(float deltaTime)
    {
        cc->Move8(deltaTime);

        Debug::OutputLine(
            std::to_wstring(cc->position.x) + L" " + std::to_wstring(cc->position.y));

        //render start
        console.SetConsoleCursorPos({ (short)cc->position.x, (short)cc->position.y });
        console.Write(L"a");
        //render end
    }

    void OnDestroy()
    {
        delete cc;
    }
};

int main()
{
    SimpleGame simpleGame;
    simpleGame.ConstructConsole(L"SimpleGame", PaletteType::Legacy, 120, 40, 6, 12);
    simpleGame.StartLoop(60, true);

    return 0;
}