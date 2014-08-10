/* FloatLib Functions Header */

#ifndef FL_FUNCTIONS_HPP
#define FL_FUNCTIONS_HPP

auto FLAlmostEqualRelative(float a, float b, float epsilon) -> bool;
auto inline FLAbsoluteError(float a, float b) -> float;
auto inline FLRelativeError(float a, float b) -> float;
auto inline FLSwapXOR(float &a, float &b) -> void;
auto inline FLSwap(float &a, float &b) -> void;

#endif /* FL_FUNCTIONS_HPP */
