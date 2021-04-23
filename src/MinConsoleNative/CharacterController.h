#pragma once

#include "MinDefines.h"
#include "Vector2.h"

namespace MinConsoleNative
{
    enum class MoveDirection
    {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4,
        LEFT_UP = 5,
        RIGHT_UP = 6,
        LEFT_DOWN = 7,
        RIGHT_DOWN = 8,
    };

    class CharacterController
    {
    private:
        bool moved = false;
        float moveTimer = 0.0f;
        bool moveSlash = false;

    public:
        static int LeftKey;
        static int RightKey;
        static int UpKey;
        static int DownKey;

    public:
        Vector2 position;   //This coordinate is screen coordinate
        float speed;        //Moving speed per second

        CharacterController(Vector2 position, float speed);

        void Reset()
        {
            this->moved = false;
            this->moveTimer = 0.0f;
            this->moveSlash = false;
        }

        MoveDirection Move4(float deltaTime);

        MoveDirection Move8(float deltaTime);
    };
}