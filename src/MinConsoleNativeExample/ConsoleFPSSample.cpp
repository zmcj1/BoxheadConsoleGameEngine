#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

class ConsoleFPS : public ConsoleEngine
{
private:
    int consoleWidth;
    int consoleHeight;
    Audio* lobbyAudio;
    CellRenderer* crenderer;

private:
    wstring map;
    int mapWidth = 25;
    int mapHeight = 25;

    float playerX = 0;
    float playerY = 0;
    float playerAngle = 0.0f;
    float FOV = 3.14159f / 4;
    float depth = 16.0f;
    float rotateSpeed = 3.0f;
    float moveSpeed = 5.0f;

public:
    void Init(int consoleWidth, int consoleHeight)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->lobbyAudio = new Audio(File::Combine(File::GetDirectoryPath(), L"..\\..\\res\\[CSO] Lobby Theme.mp3"));
        this->crenderer = new CellRenderer(consoleWidth, consoleHeight, CellRendererMode::TrueColor);
        CreateMap();
    }

    void CreateMap()
    {
        for (int i = 0; i < mapWidth * mapHeight; i++)
        {
            this->map += L' ';
        }
        vector<Vector2> obstacles = MazeGenerator::GenerateMaze(mapWidth, mapHeight);
        for (int i = 0; i < obstacles.size(); i++)
        {
            this->map[obstacles[i].y * mapWidth + obstacles[i].x] = L'#';
        }
    }

    void OnStart() override
    {
        this->lobbyAudio->SetVolume(MCI_MAX_VOLUME / 10);
        this->lobbyAudio->Play(true, false);
    }

    void OnUpdate(float deltaTime) override
    {
        Input::CheckKeyboardEx();

        if (Input::GetKeyEx(VK_ESCAPE))
        {
            StopLoop();
        }

        if (Input::GetKeyEx('A'))
        {
            playerAngle -= rotateSpeed * deltaTime;
        }
        if (Input::GetKeyEx('D'))
        {
            playerAngle += rotateSpeed * deltaTime;
        }
        if (Input::GetKeyEx('W'))
        {
            playerX += ::cosf(playerAngle) * moveSpeed * deltaTime;
            playerY += ::sinf(playerAngle) * moveSpeed * deltaTime;
            if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
            {
                playerX -= ::cosf(playerAngle) * moveSpeed * deltaTime;
                playerY -= ::sinf(playerAngle) * moveSpeed * deltaTime;
            }
        }
        if (Input::GetKeyEx('S'))
        {
            playerX -= ::cosf(playerAngle) * moveSpeed * deltaTime;
            playerY -= ::sinf(playerAngle) * moveSpeed * deltaTime;
            if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
            {
                playerX += ::cosf(playerAngle) * moveSpeed * deltaTime;
                playerY += ::sinf(playerAngle) * moveSpeed * deltaTime;
            }
        }

    }

    void OnDestroy() override
    {
        delete this->lobbyAudio;
        delete this->crenderer;
    }
};

int main()
{
    int consoleWidth = 120;
    int consoleHeight = 40;

    ConsoleFPS consoleFPS;
    consoleFPS.ConstructConsole(L"Console FPS", PaletteType::Legacy, consoleWidth, consoleHeight, 6, 12, L"Consolas", FW_NORMAL);
    consoleFPS.Init(consoleWidth, consoleHeight);
    consoleFPS.StartLoop();
    return 0;
}