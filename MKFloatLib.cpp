#include <cmath>

#include "MKFloatLib.hpp"

auto inline MFAbsoluteError(float a, float b) -> float {
    return fabs(a - b);
}

auto inline MFRelativeError(float a, float b) -> float {
    return fabs((a - b)/b);
}

/* Non-optimal: Not recommended */
auto MFAlmostEqualRelative(float a, float b, float epsilon) -> bool {

    /* Remove a division-by-zero possibility */
    if (a == b) {
        return true;
    }

    float relative_error;
    if (fabs(a) > fabs(b)) {
        relative_error = MFRelativeError(a, b);
    } else {
        relative_error = MFRelativeError(b, a);
    }

    if (relative_error <= epsilon) {
        return true;
    }

    return false;
}
