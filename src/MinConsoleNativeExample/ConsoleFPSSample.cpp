#include "..\MinConsoleNative\MinConsoleNative.h"

using namespace std;

#define light_shade     0x2591
#define medium_shade    0x2592
#define dark_shade      0x2593
#define full_shade      0x2588

class ConsoleFPS : public ConsoleEngine
{
private:
    int consoleWidth = 0;
    int consoleHeight = 0;
    Audio* lobbyAudio = nullptr;
    CellRenderer* crenderer = nullptr;

private:
    wstring map;
    int mapWidth = 17;
    int mapHeight = 17;

    float playerX = 6.0f;
    float playerY = 12.0f;
    float playerAngle = 0.0f;

    float rotateSpeed = 3.14159f; //1 ms rotate half circle(180 degrees)
    float moveSpeed = 5.0f;

    const float FOV = 3.14159f / 4;
    const float depth = 16.0f;

    bool mouseSupport = false;
    bool mouseLockMode = true;

public:
    void Init(int consoleWidth, int consoleHeight, bool useMaze = false, bool mouseSupport = true)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        //first we search music from the current dir
        wstring lobbyAudioPath = File::Combine(File::GetDirectoryPath(), L"[CSO] Lobby Theme.mp3");
        if (File::Exists(lobbyAudioPath))
        {
            this->lobbyAudio = new Audio(lobbyAudioPath);
        }
        else
        {
            this->lobbyAudio = new Audio(File::Combine(File::GetDirectoryPath(), L"..\\..\\res\\[CSO] Lobby Theme.mp3"));
        }

        this->crenderer = new CellRenderer(consoleWidth, consoleHeight, CellRendererMode::Fast);
        this->mouseSupport = mouseSupport;
        //create the map!
        CreateMap(useMaze);
    }

    void CreateMap(bool useMaze)
    {
        if (useMaze)
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
        else
        {
            map += L"#################";
            map += L"#...............#";
            map += L"#........########";
            map += L"#...............#";
            map += L"#.......##......#";
            map += L"#.......##......#";
            map += L"#...............#";
            map += L"###.............#";
            map += L"###.............#";
            map += L"#.......####..###";
            map += L"#.......#.......#";
            map += L"#...............#";
            map += L"#.......#.......#";
            map += L"#.......####..###";
            map += L"#...............#";
            map += L"#...............#";
            map += L"#################";
        }
    }

    void ClampMouseInClient()
    {
        POINT mousePosInClient = window.GetMappedMousePos();
        POINT clientSize = window.GetClientSize();
        POINT windowCenterPos = window.GetCenterPosOfWindow();

        RECT rect;
        ::GetWindowRect(window.windowHandle, &rect);
        rect.left += 10;
        rect.right -= 10;
        rect.top = windowCenterPos.y;
        rect.bottom = windowCenterPos.y;
        ::ClipCursor(&rect);

        if (mousePosInClient.x < 10)
        {
            mousePosInClient.x = clientSize.x - 10;
            ::SetCursorPos(mousePosInClient.x, windowCenterPos.y);
            Input::ResetMouseAxis();
        }
        else if (mousePosInClient.x > clientSize.x - 10)
        {
            mousePosInClient.x = 10;
            ::SetCursorPos(mousePosInClient.x, windowCenterPos.y);
            Input::ResetMouseAxis();
        }
    }

    void OnStart() override
    {
        this->lobbyAudio->SetVolume(MCI_MAX_VOLUME / 5);
        this->lobbyAudio->Play(true, false);
    }

    void OnUpdate(float deltaTime) override
    {
        ConsoleEngine::OnUpdate(deltaTime);

        if (!mouseSupport)
        {
            if (Input::GetKey(VK_ESCAPE))
            {
                StopLoop();
            }
            //rotation
            if (Input::GetKey('A'))
            {
                playerAngle -= rotateSpeed * deltaTime;
            }
            if (Input::GetKey('D'))
            {
                playerAngle += rotateSpeed * deltaTime;
            }
        }
        else
        {
            if (Input::GetKey(VK_ESCAPE))
            {
                mouseLockMode = false;
                //free cursor
                ::ClipCursor(nullptr);
            }
            //movement left
            if (Input::GetKey('A'))
            {
                float x = ::cosf(playerAngle) * moveSpeed * deltaTime;
                float y = ::sinf(playerAngle) * moveSpeed * deltaTime;
                playerX += y;
                playerY -= x;
                if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
                {
                    playerX -= y;
                    playerY += x;
                }
            }
            //movement right
            if (Input::GetKey('D'))
            {
                float x = ::cosf(playerAngle) * moveSpeed * deltaTime;
                float y = ::sinf(playerAngle) * moveSpeed * deltaTime;
                playerX -= y;
                playerY += x;
                if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
                {
                    playerX += y;
                    playerY -= x;
                }
            }
            //mouse support
            Input::CheckMouseAxis();
            //get diff
            int diffX = Input::GetMouseAxis(MouseAxis::MOUSE_X);
            if (mouseLockMode)
            {
                //clamp mouse
                ClampMouseInClient();
            }
            //rotate
            playerAngle += diffX * rotateSpeed * deltaTime * 0.1f;
        }
        //movement forward
        if (Input::GetKey('W'))
        {
            float x = ::cosf(playerAngle) * moveSpeed * deltaTime;
            float y = ::sinf(playerAngle) * moveSpeed * deltaTime;
            playerX += x;
            playerY += y;
            if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
            {
                playerX -= x;
                playerY -= y;
            }
        }
        //movement backward
        if (Input::GetKey('S'))
        {
            float x = ::cosf(playerAngle) * moveSpeed * deltaTime;
            float y = ::sinf(playerAngle) * moveSpeed * deltaTime;
            playerX -= x;
            playerY -= y;
            if (this->map.c_str()[(int)playerY * mapWidth + (int)playerX] == L'#')
            {
                playerX += x;
                playerY += y;
            }
        }

        crenderer->Clear();

        //draw raycast
        for (int x = 0; x < consoleWidth; x++)
        {
            float rayAngle = (playerAngle - FOV / 2.0f) + ((float)x / consoleWidth) * FOV;

            float distanceToWall = 0.0f;
            bool hitWall = false;

            float eyeX = ::cosf(rayAngle);
            float eyeY = ::sinf(rayAngle);

            while (!hitWall && distanceToWall < depth)
            {
                distanceToWall += 0.1f;

                int testX = (int)(playerX + eyeX * distanceToWall);
                int testY = (int)(playerY + eyeY * distanceToWall);

                if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight)
                {
                    hitWall = true;
                    distanceToWall = depth;
                }
                else if (map[testY * mapWidth + testX] == L'#')
                {
                    hitWall = true;
                }
            }

            int ceiling = (int)(consoleHeight / 2.0f - consoleHeight / distanceToWall);
            int floor = consoleHeight - ceiling;

            for (int y = 0; y < consoleHeight; y++)
            {
                //draw ceiling
                if (y <= ceiling)
                {
                    crenderer->Draw({ x, y }, Cell(L' ', { 0,0,0 }, { 0, 0, 255 }));
                }
                //draw wall
                else if (y > ceiling && y <= floor)
                {
                    //shade the wall
                    wchar wallShade = L' ';
                    if (distanceToWall <= depth / 4.0f) wallShade = full_shade;
                    else if (distanceToWall <= depth / 3.0f) wallShade = dark_shade;
                    else if (distanceToWall <= depth / 2.0f) wallShade = medium_shade;
                    else if (distanceToWall < depth) wallShade = light_shade;
                    else wallShade = L' ';

                    crenderer->Draw({ x, y }, Cell(wallShade, { 255,0,0 }, { 0, 0, 0 }));
                }
                //draw floor
                else
                {
                    //shade the floor
                    wchar floorShade = L' ';
                    float floorDistance = 1.0f - ((float)y - (float)consoleHeight / 2) /
                        ((float)consoleHeight / 2);
                    if (floorDistance <= 0.25f) floorShade = L'#';
                    else if (floorDistance <= 0.5f) floorShade = L'x';
                    else if (floorDistance <= 0.75f) floorShade = L'.';
                    else if (floorDistance <= 0.9f) floorShade = L'-';
                    else floorShade = L' ';

                    crenderer->Draw({ x, y }, Cell(floorShade, { 128, 0, 0 }, { 0, 0, 0 }));
                }
            }
        }
        //draw status
        wstring status = L"X:" + to_wstring(playerX) + L", Y:" + to_wstring(playerY) + L", A:" + to_wstring(playerAngle);
        for (int i = 0; i < status.size(); i++)
        {
            crenderer->Draw({ i,0 }, Cell(status[i], { 255,0,0 }));
        }
        //draw map
        for (int y = 0; y < mapHeight; y++)
        {
            for (int x = 0; x < mapWidth; x++)
            {
                crenderer->Draw({ x, y + 1 }, Cell(map.c_str()[y * mapWidth + x], { 255, 0, 0 }));
            }
        }
        //draw player
        crenderer->Draw({ (int)playerX, (int)playerY + 1 }, Cell(L'P', { 0, 255, 0 }));

        crenderer->Render();
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
    POINT fontSize = GetFontSize(FontSize::_6x12);
    wstring fontName = GetFontName(FontName::Consolas);

    ConsoleFPS consoleFPS;
    COORD size = consoleFPS.ConstructConsole(L"Console FPS", PaletteType::Legacy, consoleWidth, consoleHeight, fontSize.x, fontSize.y, fontName, FW_NORMAL, true);
    consoleFPS.Init(size.X, size.Y, false, true);
    consoleFPS.StartLoop();

    return 0;
}