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
    MKVector_p sol = std::make_shared<MKVector <float> >(vector_len);

    (*vec)[0] = 5;
    (*vec)[1] = 17;
    (*vec)[2] = 20;

    (*mat)[0][0] = 1;  (*mat)[0][1] = 2;  (*mat)[0][2] = 1;
    (*mat)[1][0] = 3;  (*mat)[1][1] = 10; (*mat)[1][2] = 6;
    (*mat)[2][0] = 0;  (*mat)[2][1] = 8;  (*mat)[2][2] = 14;

    std::cout << "original matrix" << std::endl;
    std::cout << (*mat).to_string("\n") << std::endl;
    std::cout << "original vector" << std::endl;
    std::cout << (*vec).to_string(", ") << std::endl;
    std::cout << "original sol" << std::endl;
    std::cout << (*sol).to_string(", ") << std::endl;

    std::cout << "gaussian elim" << std::endl;
    MKGaussElim(mat, vec, sol);
    std::cout << "elim'd sol" << std::endl;
    std::cout << (*sol).to_string(", ") << std::endl;

    std::cout << "test completed" << std::endl;
    return 0;
}
