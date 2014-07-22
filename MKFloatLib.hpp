/* MathKit Float Library Header */

#ifndef MK_FLOAT_LIB_HPP
#define MK_FLOAT_LIB_HPP

auto inline MFAbsoluteError(float a, float b) -> float;
auto inline MFRelativeError(float a, float b) -> float;
auto MFAlmostEqualRelative(float a, float b, float epsilon) -> bool;

#endif /* MK_FLOAT_LIB_HPP */
