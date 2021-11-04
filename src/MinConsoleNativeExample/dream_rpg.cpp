#include "..\MinConsoleNative\MinConsoleNative.h"
using namespace std;

class DreamRPG : public ConsoleEngine
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
    DreamRPG game;

    game.ConstructTerminal(L"造梦联盟");
    game.StartLoop(60);

    return 0;
}