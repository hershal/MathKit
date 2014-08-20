#include <cmath>
#include <cfloat>

#include "FLFunctions.hpp"

/* Non-optimal: Not recommended */
auto FLAlmostEqualRelative(float a, float b, float epsilon) -> bool {

    const auto fa = fabs(a);
    const auto fb = fabs(b);
    const auto fdiff = FLAbsoluteError(a, b);

    /* Remove a division-by-zero possibility */
    if (a == b) {
        return true;
    }

    /* We want to divide by the largest number to minimize roundoff error */
    float relative_error;
    if (a == 0 || b == 0 || fdiff < FLT_MIN ) {
        relative_error = fdiff * epsilon;
    } else if (fa > fb) {
        relative_error = FLRelativeError(b, a);
    } else {
        relative_error = FLRelativeError(a, b);
    }

    if (relative_error <= epsilon) {
        return true;
    }

    return false;
}

auto inline FLRelativeError(float a, float b) -> float {
    return fabs((a - b)/b);
}

auto inline FLAbsoluteError(float a, float b) -> float {
    return fabs(a - b);
}

/* Test if this is faster than FLSwap */
auto inline FLSwapXOR(float &a, float &b) -> void {

    unsigned char *c = reinterpret_cast<unsigned char *>(&a);
    unsigned char *d = reinterpret_cast<unsigned char *>(&b);
    for (auto i=0; i<sizeof(float); ++i) {
        (((c[i]) ^ (d[i])) && ((d[i]) ^= (c[i]) ^= (d[i]), (c[i]) ^= (d[i])));
    }
}

auto inline FLSwap(float &a, float &b) -> void {
    const float c = a;
    a = b;
    b = c;
}
