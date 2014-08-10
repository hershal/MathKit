/* FloatLib Functions Header */

#ifndef FL_FUNCTIONS_HPP
#define FL_FUNCTIONS_HPP

static const float FLEpsilon = pow(10, -6);

auto FLAlmostEqualRelative(float a, float b, float epsilon=FLEpsilon) -> bool;
auto inline FLRelativeError(float a, float b) -> float;
auto inline FLAbsoluteError(float a, float b) -> float;
auto inline FLSwapXOR(float &a, float &b) -> void;
auto inline FLSwap(float &a, float &b) -> void;

#endif /* FL_FUNCTIONS_HPP */
