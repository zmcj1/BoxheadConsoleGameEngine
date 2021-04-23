﻿#pragma once

#include "MinDefines.h"
#include "Vector2.h"

namespace MinConsoleNative
{
    constexpr float R2 = 1.4142135;

    enum class MoveDirection
    {
        UNKNOWN = 0,
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

    public:
        Vector2 position;
        float speed;

        CharacterController(Vector2 position, float speed);

        MoveDirection Update(float deltaTime);
    };
}