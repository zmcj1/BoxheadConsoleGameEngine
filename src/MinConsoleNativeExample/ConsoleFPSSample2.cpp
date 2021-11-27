#include "MinConsoleNative.hpp"
#include <cmath>
#include <list>

//参考:
//FPS:https://www.youtube.com/watch?v=xW8skO7MFYw
//FPS2:https://www.youtube.com/watch?v=HEb2akswCcw

using namespace std;

#define light_shade     0x2591
#define medium_shade    0x2592
#define dark_shade      0x2593
#define full_shade      0x2588

struct sObject
{
public:
    float x;
    float y;
    OLCSprite* sprite;

    sObject(float x, float y, OLCSprite* sprite)
    {
        this->x = x;
        this->y = y;
        this->sprite = sprite;
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
    float playerX = 8.5f;           // Player Start Position
    float playerY = 14.7f;
    float playerAngle = 0.0f;       // Player Start Rotation
    float moveSpeed = 5.0f;         // Walking Speed
    float rotateSpeed = Math::PI;   // Rotating Speed (1 sec 180 degrees)

    //camera:
    const float FOV = Math::PI / 4; // Field of view
    const float depth = 16.0f;      // Maximum rendering distance

    //mouse support:
    bool mouseSupport = false;
    bool mouseLockMode = true;

    //sprites:
    OLCSprite* spriteWall;
    OLCSprite* spriteLamp;
    OLCSprite* spriteFireBall;

    //palette:
    ConsolePalette legacyPalette = paletteSystem.palettes[PaletteType::Legacy];

    //objects:
    list<sObject> listObjects;

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

        this->spriteWall = new OLCSprite(L"../../res/olcSprites/fps_wall1.spr");
        this->spriteLamp = new OLCSprite(L"../../res/olcSprites/fps_lamp1.spr");
        this->spriteFireBall = new OLCSprite(L"../../res/olcSprites/fps_fireball1.spr");

        listObjects =
        {
            sObject(8.5f, 8.5f, this->spriteLamp),
            //sObject(7.5f, 7.5f, this->spriteLamp),
            //sObject(10.5f, 3.5f, this->spriteLamp),
        };
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
            playerAngle += diffX * rotateSpeed * deltaTime * 0.05f;
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

            float stepSize = 0.01f;
            float distanceToWall = 0.0f;

            bool hitWall = false;

            float eyeX = ::cosf(rayAngle);
            float eyeY = ::sinf(rayAngle);

            float sampleX = 0.0f;

            while (!hitWall && distanceToWall < depth)
            {
                distanceToWall += stepSize;

                int testX = (int)(playerX + eyeX * distanceToWall);
                int testY = (int)(playerY + eyeY * distanceToWall);

                if (testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight)
                {
                    hitWall = true;
                    distanceToWall = depth;
                }
                //与墙壁发生了碰撞
                else if (map[testY * mapWidth + testX] == L'#')
                {
                    hitWall = true;

                    // 确定射线击中墙壁的位置:

                    //墙壁中心点(假设每一堵墙壁都是1X1大小)
                    float blockMidX = (float)testX + 0.5f;
                    float blockMidY = (float)testY + 0.5f;
                    //射线命中点
                    float testPointX = playerX + eyeX * distanceToWall;
                    float testPointY = playerY + eyeY * distanceToWall;

                    //testAngle为从block中点出发, 射向射线命中点的向量与X轴的夹角
                    float testAngle = atan2f(testPointY - blockMidY, testPointX - blockMidX);

                    //命中右方
                    if (testAngle >= -3.14159f * 0.25f && testAngle < 3.14159f * 0.25f)
                        sampleX = testPointY - (float)testY;
                    //命中上方
                    if (testAngle >= 3.14159f * 0.25f && testAngle < 3.14159f * 0.75f)
                        sampleX = testPointX - (float)testX;
                    //命中下方
                    if (testAngle < -3.14159f * 0.25f && testAngle >= -3.14159f * 0.75f)
                        sampleX = testPointX - (float)testX;
                    //命中左方
                    if (testAngle >= 3.14159f * 0.75f || testAngle < -3.14159f * 0.75f)
                        sampleX = testPointY - (float)testY;
                }
            }

            int ceiling = (int)(consoleHeight / 2.0f - consoleHeight / distanceToWall);
            int floor = consoleHeight - ceiling;

#ifdef OLD_SHADER
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
#else
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
                    if (distanceToWall < depth)
                    {
                        float sampleY = ((float)y - (float)ceiling) / ((float)floor - (float)ceiling);
                        ConsoleColorPair pair = MinUshortToConsoleColor(spriteWall->SampleColour(sampleX, sampleY));
                        Color24 _foreColor24 = legacyPalette.consolePalette[pair.foreColor];
                        Color24 _backColor24 = legacyPalette.consolePalette[pair.backColor];
                        crenderer->Draw({ x, y }, Cell(spriteWall->SampleGlyph(sampleX, sampleY), _foreColor24, _backColor24));
                    }
                    else
                    {
                        crenderer->Draw({ x, y }, Cell(L' ', { 0,0,0 }, { 0,0,0 }));
                    }
                }
                //draw floor
                else
                {
                    crenderer->Draw({ x, y }, Cell(L' ', { 0, 0, 0 }, { 0, 128, 0 }));
                }
            }
#endif
        }

        //draw objects:
        for (const auto& object : listObjects)
        {
            // Can object be seen?
            float vecX = object.x - playerX;
            float vecY = object.y - playerY;
            float distanceFromPlayer = sqrtf(vecX * vecX + vecY * vecY);

            float eyeX = cosf(playerAngle);
            float eyeY = sinf(playerAngle);

            //float objectAngle = atan2f(eyeX, eyeY) - atan2f(vecX, vecY);
            float __x = atan2f(vecY, vecX);
            float __y = atan2f(eyeY, eyeX);
            //Debug::OutputLine(to_wstring(__x * Math::Rad2Deg) + L" " + to_wstring(__y * Math::Rad2Deg));

            float objectAngle = atan2f(vecY, vecX) - atan2f(eyeY, eyeX);
            Debug::OutputLine(to_wstring(objectAngle * Math::Rad2Deg));

            //限制取值范围在+PI与-PI之间
            if (objectAngle < -3.14159f)
                objectAngle += 2.0f * 3.14159f;
            if (objectAngle > 3.14159f)
                objectAngle -= 2.0f * 3.14159f;

            //cal start
            float ox = object.x - playerX;
            float oy = object.y - playerY;
            float L1 = sqrtf(ox * ox + oy * oy);

            float x = cosf(playerAngle);
            float y = sinf(playerAngle);
            float L2 = sqrtf(x * x + y * y);

            float dot = x * ox + y * oy;
            float _rad = acosf(dot / (L1 * L2));
            float _angle = _rad * Math::Rad2Deg;
            //cal end

            //debug
            //Debug::OutputLine(to_wstring(_angle) + L" " + to_wstring(objectAngle * Math::Rad2Deg));

            bool inPlayerFOV = fabs(objectAngle) < FOV / 2.0f;

            //画在视野范围之内但是不要太近的物体, 不画超过视距的物体
            if (inPlayerFOV && distanceFromPlayer >= 0.5f && distanceFromPlayer < depth)
            {
                float objectCeiling = (float)(consoleHeight / 2.0) - consoleHeight / ((float)distanceFromPlayer);
                float objectFloor = consoleHeight - objectCeiling;
                float objectHeight = objectFloor - objectCeiling;

                float objectAspectRatio = (float)object.sprite->Height / (float)object.sprite->Width;
                float objectWidth = objectHeight / objectAspectRatio;
                float middleOfObject = (0.5f * (objectAngle / (FOV / 2.0f)) + 0.5f) * (float)consoleWidth;

                //Debug::OutputLine(to_wstring(objectAngle * Math::Rad2Deg) + L" " + to_wstring(middleOfObject));

                // Draw Lamp
                for (float lx = 0; lx < objectWidth; lx++)
                {
                    for (float ly = 0; ly < objectHeight; ly++)
                    {
                        float sampleX = lx / objectWidth;
                        float sampleY = ly / objectHeight;
                        wchar c = object.sprite->SampleGlyph(sampleX, sampleY);

                        int nObjectColumn = (int)(middleOfObject + lx - (objectWidth / 2.0f));

                        if (nObjectColumn >= 0 && nObjectColumn < consoleWidth)
                        {
                            //if (c != L' ' && fDepthBuffer[nObjectColumn] >= distanceFromPlayer)
                            //{
                            //    ConsoleColorPair pair = MinUshortToConsoleColor(spriteWall->SampleColour(sampleX, sampleY));
                            //    Color24 _foreColor24 = legacyPalette.consolePalette[pair.foreColor];
                            //    Color24 _backColor24 = legacyPalette.consolePalette[pair.backColor];
                            //    crenderer->Draw({ nObjectColumn, objectCeiling + ly }, Cell(c, _foreColor24, _backColor24));
                            //    fDepthBuffer[nObjectColumn] = fDistanceFromPlayer;
                            //}

                            {
                                ConsoleColorPair pair = MinUshortToConsoleColor(object.sprite->SampleColour(sampleX, sampleY));
                                Color24 _foreColor24 = legacyPalette.consolePalette[pair.foreColor];
                                Color24 _backColor24 = legacyPalette.consolePalette[pair.backColor];
                                crenderer->Draw({ nObjectColumn, (int)(objectCeiling + ly) }, Cell(c, _foreColor24, _backColor24));
                            }
                        }
                    }
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
    COORD realSize;

    //#define FULL_SCREEN
#ifdef FULL_SCREEN
    realSize = consoleFPS.ConstructConsole(L"ConsoleFPS2", PaletteType::Legacy, 0, 0, 4, 4, L"Consolas", FW_NORMAL, true);
#else
    realSize = { 320, 180 };
    consoleFPS.ConstructConsole(L"ConsoleFPS2", PaletteType::Legacy, realSize.X, realSize.Y, 4, 4, L"Consolas", FW_NORMAL);
    //realSize = { 120, 30 };
    //consoleFPS.ConstructTerminal(L"ConsoleFPS2");
#endif

    consoleFPS.Init(realSize.X, realSize.Y);
    consoleFPS.StartLoop();
    return 0;
}