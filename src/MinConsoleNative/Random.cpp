#include "Random.h"
#include <cstdlib>

namespace MinConsoleNative
{
    extern uint counter = 0;

    EXPORT_FUNC MinGetRandomValue(uint minimum, uint maximum, uint* value)
    {
        if (minimum >= maximum)
        {
            return minimum;
        }

        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);
        //Use data type overflow to get completely different values
        uint base = (uint)large_int.QuadPart;

        ::srand(base + counter);
        counter++;

        *value = (uint)(::rand() % (maximum - minimum + 1) + minimum);
        return true;
    }

    uint Random::Range(uint minimum, uint maximum)
    {
        uint value;
        MinGetRandomValue(minimum, maximum, &value);
        return value;
    }
}