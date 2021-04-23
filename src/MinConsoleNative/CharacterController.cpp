#include "CharacterController.h"
#include "Input.h"

namespace MinConsoleNative
{
    constexpr float R2 = 1.4142135;

    int CharacterController::LeftKey = 'A';
    int CharacterController::RightKey = 'D';
    int CharacterController::UpKey = 'W';
    int CharacterController::DownKey = 'S';

    CharacterController::CharacterController(Vector2 position, float speed)
    {
        this->position = position;
        this->speed = speed;
    }

    MoveDirection CharacterController::Move4(float deltaTime)
    {
        if (!this->moved)
        {
            if (Input::GetKey(LeftKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return MoveDirection::LEFT;
            }
            else if (Input::GetKey(RightKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return MoveDirection::RIGHT;
            }
            else if (Input::GetKey(UpKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return MoveDirection::UP;
            }
            else if (Input::GetKey(DownKey))
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

    MoveDirection CharacterController::Move8(float deltaTime)
    {
        if (!this->moved)
        {
            if (Input::GetKey(LeftKey) && Input::GetKey(UpKey))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, -1);
                return MoveDirection::LEFT_UP;
            }
            else if (Input::GetKey(RightKey) && Input::GetKey(UpKey))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, -1);
                return MoveDirection::RIGHT_UP;
            }
            else if (Input::GetKey(LeftKey) && Input::GetKey(DownKey))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, 1);
                return MoveDirection::LEFT_DOWN;
            }
            else if (Input::GetKey(RightKey) && Input::GetKey(DownKey))
            {
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, 1);
                return MoveDirection::RIGHT_DOWN;
            }
            else if (Input::GetKey(LeftKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return MoveDirection::LEFT;
            }
            else if (Input::GetKey(RightKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return MoveDirection::RIGHT;
            }
            else if (Input::GetKey(UpKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return MoveDirection::UP;
            }
            else if (Input::GetKey(DownKey))
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