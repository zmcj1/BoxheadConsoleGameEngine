#include "CharacterController.h"
#include "Input.h"

namespace MinConsoleNative
{
    constexpr float R2 = 1.4142135;

    CharacterController::CharacterController(Vector2 position, float speed, CharacterControllerKeyboardLayout layout)
    {
        this->position = position;
        this->speed = speed;
        this->layout = layout;
        switch (layout)
        {
        case CharacterControllerKeyboardLayout::WASD:
            this->LeftKey = 'A';
            this->RightKey = 'D';
            this->UpKey = 'W';
            this->DownKey = 'S';
            break;
        case CharacterControllerKeyboardLayout::ArrowKeys:
            this->LeftKey = VK_LEFT;
            this->RightKey = VK_RIGHT;
            this->UpKey = VK_UP;
            this->DownKey = VK_DOWN;
            break;
        }
    }

    void CharacterController::Reset()
    {
        this->moved = false;
        this->moveTimer = 0.0f;
        this->moveSlash = false;
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