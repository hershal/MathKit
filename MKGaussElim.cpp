/* MathKit Gaussian Elimination Implemenation */

#include <cmath>

#include "MKGaussElim.hpp"
#include "MKFloatLib.hpp"

/*! \brief Searches for an appropriate pivot for Gaussian Elimination
*/
auto MKGaussPivotIndex(MKMatrix_p A, int k, int n) -> int {
    std::size_t i = k;
    while ((i<n) && MFAlmostEqualRelative((*A)[i][k], 0.0)) {
        ++i;
    }

    return i;
}

auto MKGaussRowExchange(MKMatrix_p A, MKVector_p b, int k, int p, int n) -> void {

}

auto MKGaussFwdElimination(MKMatrix_p A, MKVector_p b, int k, int n) -> void {

}

auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x, int n) -> void {

}

auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> int {
    return 0;
}

