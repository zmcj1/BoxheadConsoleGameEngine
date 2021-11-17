#include "Vector2.hpp"

using namespace std;

namespace MinConsoleNative
{
    const Vector2 Vector2::zero = { 0, 0 };
    const Vector2 Vector2::up = Vector2(0, 1);
    const Vector2 Vector2::down = Vector2(0, -1);
    const Vector2 Vector2::left = Vector2(-1, 0);
    const Vector2 Vector2::right = Vector2(1, 0);

    int Vector2::Distance(const Vector2& a, const Vector2& b)
    {
        return ::abs(a.x - b.x) + ::abs(a.y - b.y);
    }

    Vector2 Vector2::Direction8ToVector2(Direction8 dir)
    {
        switch (dir)
        {
        case Direction8::UNKNOWN:
            return Vector2::zero;
        case Direction8::UP:
            return Vector2(0, -1);
        case Direction8::DOWN:
            return Vector2(0, 1);
        case Direction8::LEFT:
            return Vector2(-1, 0);
        case Direction8::RIGHT:
            return Vector2(1, 0);
        case Direction8::LEFT_UP:
            return Vector2(-1, -1);
        case Direction8::RIGHT_UP:
            return Vector2(1, -1);
        case Direction8::LEFT_DOWN:
            return Vector2(-1, 1);
        case Direction8::RIGHT_DOWN:
            return Vector2(1, 1);
        default:
            return Vector2::zero;
        }
    }

    Direction8 Vector2::Vector2ToDirection8(Vector2 vector)
    {
        if (vector.x > 0 && vector.y == 0)
        {
            return Direction8::RIGHT;
        }
        if (vector.x < 0 && vector.y == 0)
        {
            return Direction8::LEFT;
        }
        if (vector.x == 0 && vector.y > 0)
        {
            return Direction8::DOWN;
        }
        if (vector.x == 0 && vector.y < 0)
        {
            return Direction8::UP;
        }
        if (vector.x < 0 && vector.y < 0)
        {
            return Direction8::LEFT_UP;
        }
        if (vector.x > 0 && vector.y < 0)
        {
            return Direction8::RIGHT_UP;
        }
        if (vector.x < 0 && vector.y > 0)
        {
            return Direction8::LEFT_DOWN;
        }
        if (vector.x > 0 && vector.y > 0)
        {
            return Direction8::RIGHT_DOWN;
        }
        return Direction8::UNKNOWN;
    }

    Vector2::Vector2() :x(0), y(0)
    {
    }

    Vector2::Vector2(int x, int y) : x(x), y(y)
    {
    }

    Vector2::Vector2(COORD coord) : x((int)coord.X), y((int)coord.Y)
    {
    }

    Vector2::Vector2(POINT point) : x((int)point.x), y((int)point.y)
    {
    }

    Vector2 Vector2::operator-() const
    {
        return Vector2(-x, -y);
    }

    bool Vector2::operator==(const Vector2& other) const
    {
        if (x == other.x && y == other.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Vector2::operator!=(const Vector2& other) const
    {
        if (x != other.x || y != other.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        Vector2 vector;
        vector.x = x + other.x;
        vector.y = y + other.y;
        return vector;
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        Vector2 vector;
        vector.x = x - other.x;
        vector.y = y - other.y;
        return vector;
    }

    Vector2 Vector2::operator*(int s) const
    {
        Vector2 vector;
        vector.x = x * s;
        vector.y = y * s;
        return vector;
    }

    Vector2 Vector2::operator/(int s) const
    {
        Vector2 vector;
        if (s == 0)
        {
            throw "Divide by zero exception";
        }
        vector.x = x / s;
        vector.y = y / s;
        return vector;
    }

    wstring Vector2::ToString() const
    {
        wstring wstr;
        wstr += _T("[X:");
        wstr += to_wstring(x);
        wstr += _T(" Y:");
        wstr += to_wstring(y);
        wstr += _T("]");
        return wstr;
    }
}