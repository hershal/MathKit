/* MathKit Gaussian Elimination Implemenation */

#include <cmath>

#include "MKGaussElim.hpp"
#include "MKFloatLib.hpp"

const float epsilon = pow(10, -6);

/*! \brief Searches for an appropriate pivot for Gaussian Elimination
*/
auto MKGaussPivotIndex(MKMatrix_p A, int k) -> int {
    std::size_t i = k;
    std::size_t n = (*A).size();
    while ((i<n) && MFAlmostEqualRelative((*A)[i][k], 0.0, epsilon)) {
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

