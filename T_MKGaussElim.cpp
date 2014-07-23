/* MathKit MKVector Testing */

#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>

#include "MKGaussElim.hpp"
#include "TKNumberedAttribute.hpp"

int main() {

    std::size_t vector_len = 3;
    MKMatrix_p mat = std::make_shared<MKVector<MKVector<float> > >
        (vector_len, MKVector<float>(vector_len));
    MKVector_p vec = std::make_shared<MKVector <float> >(vector_len);

    (*vec)[0] = 9;
    (*vec)[1] = 1;
    (*vec)[2] = 35;

    (*mat)[0][0] = 1;
    (*mat)[0][1] = 3;
    (*mat)[0][2] = 1;

    (*mat)[1][0] = 1;
    (*mat)[1][1] = 1;
    (*mat)[1][2] = -1;

    (*mat)[2][0] = 3;
    (*mat)[2][1] = 11;
    (*mat)[2][2] = 5;

    std::cout << "original matrix" << std::endl;
    std::cout << (*mat).to_string("\n") << std::endl;
    std::cout << "original vector" << std::endl;
    std::cout << (*vec).to_string(", ") << std::endl;

    std::cout << std::endl;

    std::cout << "pivots at each row" << std::endl;
    std::cout << MKGaussPivotIndex(mat, 0) << std::endl;
    std::cout << MKGaussPivotIndex(mat, 1) << std::endl;
    std::cout << MKGaussPivotIndex(mat, 2) << std::endl;

    std::cout << std::endl;

    auto row_exchange_1 = 1;
    auto row_exchange_2 = 2;
    auto mat_copy = mat;
    auto vec_copy = vec;
    std::cout << "exchanging row " << row_exchange_1 << " and "
              << row_exchange_2 << ":" << std::endl;
    MKGaussRowExchange(mat_copy, vec_copy, row_exchange_1, row_exchange_2);
    std::cout << "exchanged mat_copy" << std::endl;
    std::cout << (*mat_copy).to_string("\n") << std::endl;
    std::cout << "exchanged vec_copy" << std::endl;
    std::cout << (*vec_copy).to_string(", ") << std::endl;

    std::cout << std::endl;

    auto fwd_elim_start_idx = 0;
    mat_copy = mat;
    vec_copy = vec;
    std::cout << "fwd eliminating from row "
              << fwd_elim_start_idx << ":" << std::endl;
    MKGaussFwdElimination(mat_copy, vec_copy, fwd_elim_start_idx);
    std::cout << "exchanged mat_copy" << std::endl;
    std::cout << (*mat_copy).to_string("\n") << std::endl;
    std::cout << "exchanged vec_copy" << std::endl;
    std::cout << (*vec_copy).to_string(", ") << std::endl;

    std::cout << "test completed" << std::endl;
    return 0;
}
