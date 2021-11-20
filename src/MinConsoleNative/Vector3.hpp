#pragma once

#include "MinDefines.hpp"
#include <math.h>

//参考《3D数学基础：图形与游戏开发》中第6章的C++Vector3类

namespace MinConsoleNative
{
    class Vector3
    {
    public:
        static const Vector3 Zero;

    public:
        float x, y, z;

        Vector3()
        {
        }

        Vector3(const Vector3& vec3) : x(vec3.x), y(vec3.y), z(vec3.z)
        {
        }

        Vector3(float x, float y, float z) : x(x), y(y), z(z)
        {
        }

        Vector3& operator=(const Vector3& vec3)
        {
            this->x = vec3.x;
            this->y = vec3.y;
            this->z = vec3.z;
            return *this;
        }

        void Reset()
        {
            x = y = z = 0.0f;
        }

        bool operator==(const Vector3& vec3) const
        {
            return x == vec3.x && y == vec3.y && z == vec3.z;
        }

        bool operator!=(const Vector3& vec3) const
        {
            return x != vec3.x || y != vec3.y || z != vec3.z;
        }

        Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }

        Vector3 operator+(const Vector3& vec3) const
        {
            return Vector3(x + vec3.x, y + vec3.y, z + vec3.z);
        }

        Vector3 operator-(const Vector3& vec3) const
        {
            return Vector3(x - vec3.x, y - vec3.y, z - vec3.z);
        }

        Vector3 operator*(float a) const
        {
            return Vector3(x * a, y * a, z * a);
        }

        Vector3 operator/(float a) const
        {
            return Vector3(x / a, y / a, z / a);
        }

        Vector3& operator+=(const Vector3& vec3)
        {
            x += vec3.x;
            y += vec3.y;
            z += vec3.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& vec3)
        {
            x -= vec3.x;
            y -= vec3.y;
            z -= vec3.z;
            return *this;
        }

        Vector3& operator*=(float a)
        {
            x *= a;
            y *= a;
            z *= a;
            return *this;
        }

        Vector3& operator/=(float a)
        {
            float oneOverA = 1.0f / a;
            x *= oneOverA;
            y *= oneOverA;
            z *= oneOverA;
            return *this;
        }

        void Normalize()
        {
            float magSq = x * x + y * y + z * z;
            if (magSq > 0.0f)
            {
                float oneOverMag = 1.0f / sqrt(magSq);
                x *= oneOverMag;
                y *= oneOverMag;
                z *= oneOverMag;
            }
        }

        Vector3 Normalized() const
        {
            float magSq = x * x + y * y + z * z;
            if (magSq > 0.0f)
            {
                float oneOverMag = 1.0f / sqrt(magSq);
                return Vector3(x * oneOverMag, y * oneOverMag, z * oneOverMag);
            }
            throw "Vector3:divide by 0 error";
        }

        float Magnitude() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        //Dot
        float operator*(const Vector3& vec3) const
        {
            return x * vec3.x + y * vec3.y + z * vec3.z;
        }

        //Cross
        static Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return Vector3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }

        static float Distance(const Vector3& a, const Vector3& b)
        {
            float dx = a.x - b.x;
            float dy = a.y - b.y;
            float dz = a.z - b.z;
            return sqrt(dx * dx + dy * dy + dz * dz);
        }
    };
}