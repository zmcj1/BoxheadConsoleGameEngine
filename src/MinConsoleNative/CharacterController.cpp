#include "CharacterController.hpp"
#include "Input.hpp"
#include "Math.hpp"

namespace MinConsoleNative
{
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

    Direction8 CharacterController::Move4(float deltaTime)
    {
        if (!this->moved)
        {
            if (Input::GetKey(LeftKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return Direction8::LEFT;
            }
            else if (Input::GetKey(RightKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return Direction8::RIGHT;
            }
            else if (Input::GetKey(UpKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return Direction8::UP;
            }
            else if (Input::GetKey(DownKey))
            {
                this->moved = true;
                this->position = this->position + Vector2(0, 1);
                return Direction8::DOWN;
            }
            else
            {
                return Direction8::UNKNOWN;
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
            return Direction8::UNKNOWN;
        }
    }

    Direction8 CharacterController::Move8(float deltaTime)
    {
        if (!this->moved)
        {
            Vector2 moveDir = Vector2::zero;

            if (Input::GetKey(LeftKey))
            {
                moveDir.x--;
            }
            if (Input::GetKey(RightKey))
            {
                moveDir.x++;
            }
            if (Input::GetKey(UpKey))
            {
                moveDir.y--;
            }
            if (Input::GetKey(DownKey))
            {
                moveDir.y++;
            }

            Direction8 dir = Vector2::Vector2ToDirection8(moveDir);

            switch (dir)
            {
            case Direction8::LEFT_UP:
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, -1);
                return Direction8::LEFT_UP;

            case Direction8::RIGHT_UP:
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, -1);
                return Direction8::RIGHT_UP;

            case Direction8::LEFT_DOWN:
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(-1, 1);
                return Direction8::LEFT_DOWN;

            case Direction8::RIGHT_DOWN:
                this->moved = true;
                this->moveSlash = true;
                this->position = this->position + Vector2(1, 1);
                return Direction8::RIGHT_DOWN;

            case Direction8::LEFT:
                this->moved = true;
                this->position = this->position + Vector2(-1, 0);
                return Direction8::LEFT;

            case Direction8::RIGHT:
                this->moved = true;
                this->position = this->position + Vector2(1, 0);
                return Direction8::RIGHT;

            case Direction8::UP:
                this->moved = true;
                this->position = this->position + Vector2(0, -1);
                return Direction8::UP;

            case Direction8::DOWN:
                this->moved = true;
                this->position = this->position + Vector2(0, 1);
                return Direction8::DOWN;

            default:
                return Direction8::UNKNOWN;
            }
        }
        else
        {
            this->moveTimer += deltaTime;
            if (this->moveSlash)
            {
                if (this->moveTimer >= 1.0f / speed * Math::R2)
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
            return Direction8::UNKNOWN;
        }
    }
}