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

    (*mat)[0][0] = 11;
    (*mat)[0][1] = 12;
    (*mat)[0][2] = 13;

    (*mat)[1][0] = 0.0;
    (*mat)[1][1] = 0.0;
    (*mat)[1][2] = 23;

    (*mat)[2][0] = 31;
    (*mat)[2][1] = 32;
    (*mat)[2][2] = 33;

    std::cout << (*mat).to_string("\n") << std::endl;

    std::cout << MKGaussPivotIndex(mat, 0) << std::endl;
    std::cout << MKGaussPivotIndex(mat, 1) << std::endl;
    std::cout << MKGaussPivotIndex(mat, 2) << std::endl;

    std::cout << "test completed" << std::endl;
    return 0;
}
