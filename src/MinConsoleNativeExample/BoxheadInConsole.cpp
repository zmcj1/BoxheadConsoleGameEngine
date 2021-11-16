#include "MinConsoleNative.hpp"

using namespace std;

class Character
{
public:
    Grid grid;
    GridRenderer* grenderer;

private:
    CharacterController* controller;

public:
    Character(Vector2 position, int speed, Grid grid, GridRenderer* grenderer)
    {
        this->grid = grid;
        this->grenderer = grenderer;
        this->controller = new CharacterController(position, speed, CharacterControllerKeyboardLayout::WASD);
    }

    ~Character()
    {
        delete this->controller;
    }

    void Update(float deltaTime)
    {
        this->controller->Move4(deltaTime);
        this->grenderer->Draw(this->controller->position, grid);
    }
};

class BaseGame : public ConsoleEngine
{
private:
    int consoleWidth;
    int consoleHeight;
    int logicalWidth;
    int logicalHeight;
    Character* mainChar;
    GridRenderer* grenderer;
    Audio* lobbyAudio;

public:
    void Init(int consoleWidth, int consoleHeight)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->logicalWidth = consoleWidth / 2;
        this->logicalHeight = consoleHeight;
    }

    void OnStart() override
    {
        wstring dirPath = File::GetDirectoryPath();
        wstring lobbyAudioPath = File::Combine(dirPath, L"..\\..\\res\\[CSO] Lobby Theme.mp3");
        lobbyAudio = new Audio(lobbyAudioPath);
        lobbyAudio->Play(true, false);
        grenderer = new GridRenderer(logicalWidth, logicalHeight, GridRendererMode::TrueColor);
        mainChar = new Character(Vector2::zero, 20, Grid(L"吊", { 255,0,0 }, { 0,0,0 }, false), grenderer);
    }

    void OnUpdate(float deltaTime) override
    {
        Input::CheckKeyboardEx();

        if (Input::GetKeyEx(VK_ESCAPE))
        {
            StopLoop();
        }

        grenderer->Clear();

        mainChar->Update(deltaTime);

        grenderer->Render();
    }

    void OnDestroy() override
    {
        delete lobbyAudio;
        delete grenderer;
        delete mainChar;
    }
};

int main()
{
    int consoleWidth = 120;
    int consoleHeight = 30;

    BaseGame baseGame;
    if (baseGame.consoleType == ConsoleType::WindowsConsole)
    {
        baseGame.ConstructConsole(L"Boxhead", PaletteType::Legacy, consoleWidth, consoleHeight, 10, 20, L"黑体", FW_NORMAL);
    }
    else if (baseGame.consoleType == ConsoleType::WindowsTerminal)
    {
        baseGame.ConstructTerminal(L"Boxhead");
    }
    baseGame.Init(consoleWidth, consoleHeight);
    baseGame.StartLoop();
    return 0;
}