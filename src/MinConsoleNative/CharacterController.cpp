#include "CharacterController.h"
#include "Input.h"

namespace MinConsoleNative
{
    constexpr float R2 = 1.4142135;

    CharacterController::CharacterController(Vector2 position, float speed)
    {
        this->position = position;
        this->speed = speed;
    }

    MoveDirection CharacterController::Update(float deltaTime)
    {
        if (!this->moved)
        {
            if (Input::GetKey('A'))
            {
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return MoveDirection::LEFT;
            }
            else if (Input::GetKey('D'))
            {
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return MoveDirection::RIGHT;
            }
            else if (Input::GetKey('W'))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return MoveDirection::UP;
            }
            else if (Input::GetKey('S'))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, 1);
                return MoveDirection::DOWN;
            }
            else
            {
                return MoveDirection::NONE;
            }
        }
        else
        {
            this->moveTimer += deltaTime;
            if (this->moveTimer >= 1.0f / speed)
            {
                this->moveTimer = 0.0f;
                this->moved = false;
            }
            return MoveDirection::NONE;
        }
    }

    MoveDirection CharacterController::Update2(float deltaTime)
    {
        if (!this->moved)
        {
            if (Input::GetKey('A') && Input::GetKey('W'))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, -1);
                return MoveDirection::LEFT_UP;
            }
            else if (Input::GetKey('D') && Input::GetKey('W'))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, -1);
                return MoveDirection::RIGHT_UP;
            }
            else if (Input::GetKey('A') && Input::GetKey('S'))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, 1);
                return MoveDirection::LEFT_DOWN;
            }
            else if (Input::GetKey('D') && Input::GetKey('S'))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, 1);
                return MoveDirection::RIGHT_DOWN;
            }
            else if (Input::GetKey('A'))
            {
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return MoveDirection::LEFT;
            }
            else if (Input::GetKey('D'))
            {
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return MoveDirection::RIGHT;
            }
            else if (Input::GetKey('W'))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return MoveDirection::UP;
            }
            else if (Input::GetKey('S'))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, 1);
                return MoveDirection::DOWN;
            }
            else
            {
                return MoveDirection::NONE;
            }
        }
        else
        {
            this->moveTimer += deltaTime;
            if (this->moveSlash)
            {
                if (this->moveTimer >= 1.0f / speed * R2)
                {
                    this->moveTimer = 0.0f;
                    this->moved = false;
                    this->moveSlash = false;
                }
            }
            else
            {
                if (this->moveTimer >= 1.0f / speed)
                {
                    this->moveTimer = 0.0f;
                    this->moved = false;
                }
            }
            return MoveDirection::NONE;
        }
    }
}