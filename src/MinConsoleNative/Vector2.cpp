#include "Vector2.h"

using namespace std;

namespace MinConsoleNative
{
    const Vector2 Vector2::zero = { 0, 0 };

    int Vector2::Distance(const Vector2& a, const Vector2& b)
    {
        return ::abs(a.x - b.x) + ::abs(a.y - b.y);
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

    Vector2 Vector2::operator-()
    {
        return Vector2(-x, -y);
    }

    bool Vector2::operator==(const Vector2& other)
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

    bool Vector2::operator!=(const Vector2& other)
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

    Vector2 Vector2::operator+(const Vector2& other)
    {
        Vector2 vector;
        vector.x = x + other.x;
        vector.y = y + other.y;
        return vector;
    }

    Vector2 Vector2::operator-(const Vector2& other)
    {
        Vector2 vector;
        vector.x = x - other.x;
        vector.y = y - other.y;
        return vector;
    }

    Vector2 Vector2::operator*(int s)
    {
        Vector2 vector;
        vector.x = x * s;
        vector.y = y * s;
        return vector;
    }

    Vector2 Vector2::operator/(int s)
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

    wstring Vector2::ToString()
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