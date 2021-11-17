#pragma once

#include "MinDefines.hpp"
#include <string>

namespace MinConsoleNative
{
    enum class Direction8
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

    class Vector2
    {
    public:
        static const Vector2 zero;
        static const Vector2 up;
        static const Vector2 down;
        static const Vector2 left;
        static const Vector2 right;

        static int Distance(const Vector2& a, const Vector2& b);

        static Vector2 Direction8ToVector2(Direction8 dir);

        static Direction8 Vector2ToDirection8(Vector2 vector);

    public:
        int x;
        int y;

    public:
        Vector2();

        Vector2(int x, int y);

        Vector2(COORD coord);

        Vector2(POINT point);

        Vector2 operator-() const;

        bool operator ==(const Vector2& other) const;

        bool operator !=(const Vector2& other) const;

        Vector2 operator+(const Vector2& other) const;

        Vector2 operator-(const Vector2& other) const;

        Vector2 operator*(int s) const;

        Vector2 operator/(int s) const;

        std::wstring ToString() const;
    };
}