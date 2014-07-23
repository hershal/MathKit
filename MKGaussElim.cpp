/* MathKit Gaussian Elimination Implemenation */

#include <cmath>

#include "MKGaussElim.hpp"
#include "FLFunctions.hpp"

const float epsilon = pow(10, -6);

/*! \brief Searches for an appropriate pivot for Gaussian Elimination
*/
auto MKGaussPivotIndex(MKMatrix_p A, int k) -> int {
    std::size_t i = k;
    std::size_t n = (*A).size();
    while ((i<n) && FLAlmostEqualRelative((*A)[i][k], 0.0, epsilon)) {
        ++i;
    }

    return i;
}

auto MKGaussRowExchange(MKMatrix_p A, MKVector_p b, int k, int p) -> void {
    MKVector<float> tmp_A_val = (*A)[k];
    float tmp_b_val = (*b)[k];
    
    (*b)[k] = (*b)[p];
    (*b)[p] = tmp_b_val;

    (*A)[k] = (*A)[p];
    (*A)[p] = tmp_A_val;
}

auto MKGaussFwdElimination(MKMatrix_p A, MKVector_p b, int k, int n) -> void {

}

auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x, int n) -> void {

}

auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> int {
    return 0;
}

