#include "MinConsoleNative.hpp"

//参考:
//FPS:https://www.youtube.com/watch?v=xW8skO7MFYw
//FPS2:https://www.youtube.com/watch?v=HEb2akswCcw

using namespace std;

#define light_shade     0x2591
#define medium_shade    0x2592
#define dark_shade      0x2593
#define full_shade      0x2588

//Inspired by olcConsoleGameEngine.
class olcSprite
{
public:
    int nWidth = 0;
    int nHeight = 0;

    olcSprite()
    {

    }

    olcSprite(int w, int h)
    {
        Create(w, h);
    }

    olcSprite(const std::wstring& sFile)
    {
        if (!Load(sFile))
            Create(8, 8);
    }

private:
    short* m_Glyphs = nullptr;
    short* m_Colours = nullptr;

    void Create(int w, int h)
    {
        nWidth = w;
        nHeight = h;
        m_Glyphs = new short[w * h];
        m_Colours = new short[w * h];
        for (int i = 0; i < w * h; i++)
        {
            m_Glyphs[i] = L' ';
            m_Colours[i] = FG_BLACK;
        }
    }

public:
    void SetGlyph(int x, int y, short c)
    {
        if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
            return;
        else
            m_Glyphs[y * nWidth + x] = c;
    }

    void SetColour(int x, int y, short c)
    {
        if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
            return;
        else
            m_Colours[y * nWidth + x] = c;
    }

    short GetGlyph(int x, int y)
    {
        if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
            return L' ';
        else
            return m_Glyphs[y * nWidth + x];
    }

    short GetColour(int x, int y)
    {
        if (x < 0 || x >= nWidth || y < 0 || y >= nHeight)
            return FG_BLACK;
        else
            return m_Colours[y * nWidth + x];
    }

    short SampleGlyph(float x, float y)
    {
        int sx = (int)(x * (float)nWidth);
        int sy = (int)(y * (float)nHeight - 1.0f);
        if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
            return L' ';
        else
            return m_Glyphs[sy * nWidth + sx];
    }

    short SampleColour(float x, float y)
    {
        int sx = (int)(x * (float)nWidth);
        int sy = (int)(y * (float)nHeight - 1.0f);
        if (sx < 0 || sx >= nWidth || sy < 0 || sy >= nHeight)
            return FG_BLACK;
        else
            return m_Colours[sy * nWidth + sx];
    }

    bool Save(std::wstring sFile)
    {
        FILE* f = nullptr;
        _wfopen_s(&f, sFile.c_str(), L"wb");
        if (f == nullptr)
            return false;

        fwrite(&nWidth, sizeof(int), 1, f);
        fwrite(&nHeight, sizeof(int), 1, f);
        fwrite(m_Colours, sizeof(short), nWidth * nHeight, f);
        fwrite(m_Glyphs, sizeof(short), nWidth * nHeight, f);

        fclose(f);

        return true;
    }

    bool Load(const std::wstring& sFile)
    {
        delete[] m_Glyphs;
        delete[] m_Colours;
        nWidth = 0;
        nHeight = 0;

        FILE* f = nullptr;
        _wfopen_s(&f, sFile.c_str(), L"rb");
        if (f == nullptr)
            return false;

        std::fread(&nWidth, sizeof(int), 1, f);
        std::fread(&nHeight, sizeof(int), 1, f);

        Create(nWidth, nHeight);

        std::fread(m_Colours, sizeof(short), nWidth * nHeight, f);
        std::fread(m_Glyphs, sizeof(short), nWidth * nHeight, f);

        std::fclose(f);
        return true;
    }
};

class ConsoleFPS2 : public ConsoleEngine
{
private:
    int consoleWidth = 0;
    int consoleHeight = 0;
    CellRenderer* crenderer = nullptr;
    Audio* lobbyAudio = nullptr;

private:
    //map:
    wstring map;
    int mapWidth = 32;
    int mapHeight = 32;

    //player:
    float playerX = 6.0f;           // Player Start Position
    float playerY = 12.0f;
    float playerAngle = 0.0f;       // Player Start Rotation
    float moveSpeed = 5.0f;         // Walking Speed
    float rotateSpeed = Math::PI;   // Rotating Speed (1 sec 180 degrees)

    //camera:
    const float FOV = Math::PI / 4; // Field of view
    const float depth = 16.0f;      // Maximum rendering distance

    //mouse support:
    bool mouseSupport = true;
    bool mouseLockMode = true;

public:
    void Init(int consoleWidth, int consoleHeight)
    {
        this->consoleWidth = consoleWidth;
        this->consoleHeight = consoleHeight;
        this->crenderer = new CellRenderer(consoleWidth, consoleHeight, CellRendererMode::Fast);
        //we search .mp3 file in current dir and res dir.
        wstring lobbyAudioPath = File::Combine(File::GetDirectoryPath(), L"[CSO] Lobby Theme.mp3");
        if (File::Exists(lobbyAudioPath))
        {
            this->lobbyAudio = new Audio(lobbyAudioPath);
        }
        else
        {
            this->lobbyAudio = new Audio(File::Combine(File::GetDirectoryPath(), L"..\\res\\[CSO] Lobby Theme.mp3"));
        }
        //this->lobbyAudio->Play(true, false);
        //create map:
        map += L"#########.......#########.......";
        map += L"#...............#...............";
        map += L"#.......#########.......########";
        map += L"#..............##..............#";
        map += L"#......##......##......##......#";
        map += L"#......##..............##......#";
        map += L"#..............##..............#";
        map += L"###............####............#";
        map += L"##.............###.............#";
        map += L"#............####............###";
        map += L"#..............................#";
        map += L"#..............##..............#";
        map += L"#..............##..............#";
        map += L"#...........#####...........####";
        map += L"#..............................#";
        map += L"###..####....########....#######";
        map += L"####.####.......######..........";
        map += L"#...............#...............";
        map += L"#.......#########.......##..####";
        map += L"#..............##..............#";
        map += L"#......##......##.......#......#";
        map += L"#......##......##......##......#";
        map += L"#..............##..............#";
        map += L"###............####............#";
        map += L"##.............###.............#";
        map += L"#............####............###";
        map += L"#..............................#";
        map += L"#..............................#";
        map += L"#..............##..............#";
        map += L"#...........##..............####";
        map += L"#..............##..............#";
        map += L"################################";
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
    ConsoleFPS2 consoleFPS;
    COORD realSize = consoleFPS.ConstructConsole(L"ConsoleFPS2", PaletteType::Legacy, 0, 0, 8, 8, L"Consolas", FW_NORMAL, true);
    consoleFPS.Init(realSize.X, realSize.Y);
    consoleFPS.StartLoop();
    return 0;
}