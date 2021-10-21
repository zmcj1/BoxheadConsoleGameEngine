#include "..\MinConsoleNative\MinConsoleNative.h"
using namespace std;

//made a random method
#include <ctime>
#include <cstdlib>

//generate predso random value between min(inclusive) and max(excusive)
int RANDOM(int min, int max)
{
    srand(time(nullptr));
    int rvalue = rand() % (max - min) + min;
    return rvalue;
}

constexpr int WIDTH = 60;
constexpr int HEIGHT = 30;

enum class MonsterType
{
    Zombie = 1,
    Ghost = 2,
};

class MonsterBase
{
public:
    Vector2 position;
    MonsterType  type;

    float HP;
    float Speed;
    float Attack;
    float Armor;
};

class Zombie : public MonsterBase
{
public:

};

class Ghost : public MonsterBase
{
public:


};

enum class GameState
{
    None = 0,
    Menu = 1,
    Game = 2,
    Result = 3,
};

class Corn : public ConsoleEngine
{
private:
    GameState state = GameState::Menu;
    CharacterController* playerController;
    CellRenderer* renderer;
    vector<Vector2> maze;
    vector<Vector2> empty;

    vector<MonsterBase> monsters;

public:
    void OnStart() override
    {
        //initialization
        renderer = new CellRenderer(WIDTH, HEIGHT, CellRendererMode::TrueColor);
        //start game by default
        maze = MazeGenerator::GenerateMaze(WIDTH - 1, HEIGHT - 1);
        state = GameState::Game;

        //generate empty
        GenerateEmpty();

        //generate player
        //playerController = new CharacterController({ 1, 1 }, 10);
        playerController = new CharacterController({ WIDTH - 4, HEIGHT - 4 }, 10);

        //test:generate 10 monsters once
        for (size_t i = 0; i < 10; i++)
        {
            GenerateMonster(Vector2(), MonsterType::Zombie);
        }
    }

    void GenerateEmpty()
    {
        for (size_t i = 0; i < HEIGHT; i++)
        {
            for (size_t j = 0; j < WIDTH; j++)
            {
                bool add = true;
                Vector2 pos(j, i);

                for (const Vector2& item : maze)
                {
                    if (item == pos)
                    {
                        add = false;
                        break;
                    }
                }

                if (add)
                {
                    empty.push_back(pos);
                }
            }
        }
    }

    void GenerateMonster(Vector2 position, MonsterType type)
    {

    }

    void OnUpdate(float deltaTime) override
    {
        if (state == GameState::Game)
        {
            //store beforePos here, later we shall deal with collision with maze.
            Vector2 beforePos = playerController->position;

            playerController->Move4(deltaTime);

            //border check
            if (playerController->position.x < 0 || playerController->position.x > WIDTH - 1 ||
                playerController->position.y < 0 || playerController->position.y > HEIGHT - 1)
            {
                playerController->position = beforePos;
            }

            //collision check
            for (size_t i = 0; i < maze.size(); i++)
            {
                if (playerController->position == maze[i])
                {
                    playerController->position = beforePos;
                    break;
                }
            }

            //win check
            if (playerController->position == Vector2(WIDTH - 3, HEIGHT - 3))
            {
                //you win!
                state = GameState::Result;
                //redraw scene
                DrawScene();
                //show you win
                renderer->DrawString(Vector2(WIDTH / 2, HEIGHT / 2), L"you win!", { 255,0,0 }, { 18,133,166 }, false);
                renderer->Render();
            }
        }

        //draw scene
        if (state == GameState::Game)
        {
            DrawScene();
        }
    }

    void DrawScene()
    {
        renderer->Clear();

        for (size_t i = 0; i < maze.size(); i++)
        {
            renderer->Draw(maze[i], Cell(L'X', { 0,0,0 }, { 0,255,33 }));
        }

        for (size_t i = 0; i < empty.size(); i++)
        {
            renderer->Draw(empty[i], Cell(L'L', { 0,0,0 }, { 255,0,33 }));
        }

        renderer->Draw(playerController->position, Cell(L'K', { 255,33,33 }, { 0,0,0 }));

        renderer->Render();
    }

    void OnDestroy() override
    {
        delete playerController;
        delete renderer;
    }
};

int main()
{
    Corn corn;

    console.SetConsoleCursorVisible(false);

    corn.ConstructConsole(L"Mr. Kukin(Corn)", PaletteType::Legacy, WIDTH, HEIGHT);
    corn.StartLoop();

    return 0;
}