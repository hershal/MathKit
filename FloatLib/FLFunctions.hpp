/* FloatLib Functions Header */

#ifndef FL_FUNCTIONS_HPP
#define FL_FUNCTIONS_HPP

auto inline FLAbsoluteError(float a, float b) -> float;
auto inline FLRelativeError(float a, float b) -> float;
auto FLAlmostEqualRelative(float a, float b, float epsilon) -> bool;

#endif /* FL_FUNCTIONS_HPP */
