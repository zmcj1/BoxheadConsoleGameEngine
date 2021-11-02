#include "Random.h"
#include <cstdlib>

namespace MinConsoleNative
{
    extern uint counter = 0;

    EXPORT_FUNC_EX(uint) MinGetRandomValue(uint minimum, uint maximum)
    {
        if (minimum >= maximum)
        {
            return minimum;
        }

        LARGE_INTEGER large_int;
        ::QueryPerformanceCounter(&large_int);
        //Use data type overflow to get completely different values
        uint base = (uint)large_int.QuadPart;

        //::srand(base + counter);
        //counter++;
        ::srand(base);

        return (uint)(::rand() % (maximum - minimum + 1) + minimum);
    }

    uint Random::Range(uint minimum, uint maximum)
    {
        return MinGetRandomValue(minimum, maximum);
    }
}