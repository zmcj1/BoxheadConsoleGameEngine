#pragma once

#include "MinDefines.hpp"
#include "Vector2.hpp"

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

    enum class CharacterControllerKeyboardLayout
    {
        WASD = 1,
        ArrowKeys = 2,
    };

    class CharacterController
    {
    private:
        bool moved = false;
        float moveTimer = 0.0f;
        bool moveSlash = false;

    public:
        int LeftKey = 'A';
        int RightKey = 'D';
        int UpKey = 'W';
        int DownKey = 'S';

    public:
        Vector2 position;   //This coordinate is screen coordinate
        float speed;        //Moving speed per second
        CharacterControllerKeyboardLayout layout;

        CharacterController(Vector2 position, float speed, CharacterControllerKeyboardLayout layout = CharacterControllerKeyboardLayout::WASD);

        void Reset();

        MoveDirection Move4(float deltaTime);

        MoveDirection Move8(float deltaTime);
    };
}