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

    /* Possible speedup: Use an FLSwap method */
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

        for (auto j=k; j<n; ++j) {
            (*A)[i][j] -= scaling_coef*(*A)[k][j];
        }
    }
}

auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x) -> void {
    std::size_t n = A->size();
    float tmp;

    (*x)[n-1] = (*b)[n-1] / (*A)[n-1][n-1];

    /* Due to the unsigned nature of k, I can't compare against --0 (-1) */
    for (auto k=n-2; k<n-1; --k) {
        /* Possible speedup: cast to char* and use xor from
           char*[0]..char*[sizeof(float)-1] */
        tmp = 0.0;

        for (auto j=k+1; j<n; ++j) {
            tmp += (*A)[k][j] * (*x)[j];
        }

        (*x)[k] = ((*b)[k] - tmp) / (*A)[k][k];
    }
}

auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> void {
    std::size_t n = A->size();
    std::size_t p;

    if (n != b->size() || n != x->size()) {
        throw std::length_error("Matrix-Vector-Vector lengths did not match");
    }

    for (auto k=0; k<n-1; ++k) {
        p = MKGaussPivotIndex(A, k);

        /* If we find a pivot here which is greater than the current
           index, exchange rows */
        if ((p>k) && (p<n)) {
            MKGaussRowExchange(A, b, k, p);
        }
        MKGaussFwdElimination(A, b, k);
    }

    if (FLAlmostEqualRelative((*A)[n-1][n-1], 0.0, epsilon)) {
        throw std::runtime_error("Infinitely Many Solutions");
    }

    MKGaussBwdSubstitution(A, b, x);
}

