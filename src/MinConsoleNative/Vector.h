#pragma once

#include "MinDefines.h"
#include <vector>

namespace MinConsoleNative
{
    template<typename T>
    class Vector
    {
    private:
        Vector()
        {
        }

    public:
        static bool Contains(const std::vector<T>& container, const T& element)
        {
            for (size_t i = 0; i < container.size(); i++)
            {
                if (container[i] == element) return true;
            }
            return false;
        }

        static void Remove(std::vector<T>& container, const T& element)
        {
            for (size_t i = 0; i < container.size(); i++)
            {
                if (container[i] == element)
                {
                    container.erase(container.begin() + i);
                    break;
                }
            }
        }
    };
}