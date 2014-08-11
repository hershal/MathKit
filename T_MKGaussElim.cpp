/* MathKit MKVector Testing */

#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>

#include "MKGaussElim.hpp"
#include "TKCumulableAttribute.hpp"
#include "FLFunctions.hpp"

auto check_mat(MKMatrix_t &A, MKVector_t &b, MKVector_t &x) -> bool;
auto generate_data(MKMatrix_t &A, MKVector_t &b) -> void;
auto generate_float(float low, float high, float zero_cutoff_low, float zero_cutoff_high) -> float;

int main() {

    std::size_t btor_len = 3;
    MKMatrix_t A(btor_len);
    MKVector_t b(btor_len);
    MKVector_t x(btor_len);

    // generate_data(A, b);

    A(0,0) = 0.0;   A(0,1) = -2.0;  A(0,2) = 16.0;
    A(1,0) = 16.0;  A(1,1) = 0.0;   A(1,2) = -5.0;
    A(2,0) = 16.0;  A(2,1) = -13.0; A(2,2) = 15.0;
    b(0) = -20;     b(1) = 1;       b(2) = 0;

    MKGaussElim(A, b, x);

    MKVector_t b_approx = A*x;
    std::cout << "b_actual " <<  b << "\nb_approx " << b_approx << std::endl;

    if (check_mat(A, b, b_approx)) {
        std::cout << "correct" << std::endl;
    }
    else {
        std::cout << "incorrect" << std::endl;
        std::cout << "A\n" << A.to_string("\n") << std::endl;
        std::cout << "x\n" << x.to_string() << std::endl;
    }

    return 0;
}

auto generate_data(MKMatrix_t &A, MKVector_t &b) -> void {

    std::srand(std::time(0));

    static const float k_low = -20;
    static const float k_high = 40;
    static const float k_zero_abs_range_low = 20;
    static const float k_zero_abs_range_high = 40;
    const auto len = A.size() < b.size() ? A.size() : b.size();

    for (std::size_t i=0; i<len; ++i) {
        for (std::size_t j=0; j<len; ++j) {
            A(i,j) = generate_float(k_low, k_high, k_zero_abs_range_low, k_zero_abs_range_high);
        }
    }

    for (std::size_t i=0; i<len; ++i) {
        b(i) = generate_float(k_low, k_high, k_zero_abs_range_low, k_zero_abs_range_high);
    }
}

auto generate_float(float low, float high,
                    float zero_cutoff_low, float zero_cutoff_high)
    -> float {

    float r = low + fmod(rand(), (high-low));
    r = r<zero_cutoff_high && r>zero_cutoff_low ? 0.0 : r;
    return r;
}

auto check_mat(MKMatrix_t &A, MKVector_t &b, MKVector_t &b_approx) -> bool {

    for (std::size_t i=0; i<b.size(); ++i) {
        if (!FLAlmostEqualRelative(b_approx(i), b(i))) {
            return false;
        }
    }
    return true;
}
