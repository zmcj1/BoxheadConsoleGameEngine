#pragma once

#include "MinDefines.hpp"
#include <string>

namespace MinConsoleNative
{
    class Vector2
    {
    public:
        static const Vector2 zero;
        static const Vector2 up;
        static const Vector2 down;
        static const Vector2 left;
        static const Vector2 right;

        static int Distance(const Vector2& a, const Vector2& b);

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