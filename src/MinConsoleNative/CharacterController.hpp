#pragma once

#include "MinDefines.hpp"
#include "Vector2.hpp"

namespace MinConsoleNative
{
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

        Direction8 Move4(float deltaTime);

        Direction8 Move8(float deltaTime);
    };
}