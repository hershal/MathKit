/* MathKit Gaussian Elimination Implemenation */

#include <cmath>

#include "MKGaussElim.hpp"
#include "FLFunctions.hpp"

const float epsilon = pow(10, -6);

/*! \brief Searches for an appropriate pivot for Gaussian Elimination
*/
auto MKGaussPivotIndex(MKMatrix_p A, std::size_t k) -> std::size_t {
    std::size_t i = k;
    std::size_t n = A->size();
    while ((i<n) && FLAlmostEqualRelative((*A)[i][k], 0.0, epsilon)) {
        ++i;
    }

    return i;
}

auto MKGaussRowExchange(MKMatrix_p A, MKVector_p b, std::size_t k, std::size_t p) -> void {
    MKVector<float> tmp_A_val = (*A)[k];
    float tmp_b_val = (*b)[k];

    (*b)[k] = (*b)[p];
    (*b)[p] = tmp_b_val;

    (*A)[k] = (*A)[p];
    (*A)[p] = tmp_A_val;
}
/*! \brief Utilizes forward-elimination techniques to create an
  upper-triangular matrix.

  /param k the row index at which to start the forward elimination
 */
auto MKGaussFwdElimination(MKMatrix_p A, MKVector_p b, std::size_t k) -> void {
    float scaling_coef;
    std::size_t n = A->size();

    for (auto i=k+1; i<n; ++i) {
        scaling_coef = ((*A)[i][k])/((*A)[k][k]);
        (*b)[i] = (*b)[i] - ((*b)[k] * scaling_coef);

        for (auto j=k+1; j<n; ++j) {
            (*A)[i][j] -= scaling_coef*(*A)[k][j];
        }
    }
}

auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x, std::size_t n) -> void {

}

auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> std::size_t {
    return 0;
}

