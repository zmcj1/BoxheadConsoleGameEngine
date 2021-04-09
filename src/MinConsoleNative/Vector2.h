#pragma once

#include "MinDefines.h"
#include <string>

namespace MinConsoleNative
{
    class Vector2
    {
    public:
        static const Vector2 zero;

        static int Distance(const Vector2& a, const Vector2& b);

    public:
        int x;
        int y;

    public:
        Vector2();

        Vector2(int x, int y);

        Vector2 operator-();

        bool operator ==(const Vector2& other);

        bool operator !=(const Vector2& other);

        Vector2 operator+(const Vector2& other);

        Vector2 operator-(const Vector2& other);

        Vector2 operator*(int s);

        Vector2 operator/(int s);

        std::wstring ToString();
    };
}