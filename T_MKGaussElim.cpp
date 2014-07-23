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

    (*vec)[0] = 0;
    (*vec)[1] = 1;
    (*vec)[2] = 2;

    (*mat)[0][0] = 11;
    (*mat)[0][1] = 12;
    (*mat)[0][2] = 13;

    (*mat)[1][0] = 0.0;
    (*mat)[1][1] = 0.0;
    (*mat)[1][2] = 23;

    (*mat)[2][0] = 31;
    (*mat)[2][1] = 32;
    (*mat)[2][2] = 33;

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
    MKGaussRowExchange(mat, vec, row_exchange_1, row_exchange_2);
    std::cout << "after exchanging row " << row_exchange_1
              << " and " << row_exchange_2 << std::endl;
    
    std::cout << "exchanged matrix" << std::endl;
    std::cout << (*mat).to_string("\n") << std::endl;
    std::cout << "exchanged vector" << std::endl;
    std::cout << (*vec).to_string(", ") << std::endl;

    std::cout << "test completed" << std::endl;
    return 0;
}
