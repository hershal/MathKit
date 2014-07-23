#include <cmath>

#include "FLFunctions.hpp"

auto inline FLAbsoluteError(float a, float b) -> float {
    return fabs(a - b);
}

auto inline FLRelativeError(float a, float b) -> float {
    return fabs((a - b)/b);
}

/* Non-optimal: Not recommended */
auto FLAlmostEqualRelative(float a, float b, float epsilon) -> bool {

    /* Remove a division-by-zero possibility */
    if (a == b) {
        return true;
    }

    /* We want to divide by the largest number to minimize roundoff error */
    float relative_error;
    if (fabs(a) > fabs(b)) {
        relative_error = FLRelativeError(b, a);
    } else {
        relative_error = FLRelativeError(a, b);
    }

    if (relative_error <= epsilon) {
        return true;
    }

    return false;
}
