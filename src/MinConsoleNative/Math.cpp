#include "Math.hpp"
using namespace std;

namespace MinConsoleNative
{
    const int Math::PrimeNumbers[29] =
    {
        7,
        17,
        37,
        79,
        163,
        331,
        673,
        1361,
        2729,
        5471,
        10949,
        21911,
        43853,
        87719,
        175447,
        350899,
        701819,
        1403641,
        2807303,
        5614657,
        11229331,
        22458671,
        44917381,
        89834777,
        179669557,
        359339171,
        718678369,
        1437356741,
        2147483647
    };

    const float Math::PI = 3.14159f;

    const float Math::Rad2Deg = 180 / PI;

    const float Math::Deg2Rad = PI / 180;

    const float Math::R2 = 1.4142135;
}