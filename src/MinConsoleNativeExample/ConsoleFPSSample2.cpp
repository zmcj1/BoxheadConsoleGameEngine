#include "MinConsoleNative.hpp"

using namespace std;

class ConsoleFPS2 : public ConsoleEngine
{
public:
    //map:
    wstring map;
    int mapWidth = 30;
    int mapHeight = 30;

    //player:
    Vector2 playerPos;      // Player Start Position
    float playerAngle = 0;  // Player Start Rotation
    float walkSpeed = 5;    // Walking Speed

    //camera:
    float FOV = Math::PI / 4.0f;    // Field of view
    float depth = 30.0f;            // Maximum rendering distance

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
    ConsoleFPS2 game;
    game.ConstructConsole(L"ConsoleFPS2", PaletteType::Legacy, 0, 0,
        8, 8, L"Consolas", 400, true);
    game.StartLoop();
    return 0;
}