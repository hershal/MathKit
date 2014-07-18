/* MathKit Argument Testing */
/* This is without using MKBaseAlgorithm */

#include <iostream>
#include "MKArgument.hpp"

int main() {
    float x_max = 1.0;
    float x_min = 0.0;
    auto mk_x_max = MKArgument<float>(&x_max, "x_max", "maximum value for x");
    auto mk_x_min = MKArgument<float>(&x_min, "x_min", "minimum value for x");

    std::cout << mk_x_max.to_long_string() << std::endl;
    std::cout << mk_x_min.to_long_string() << std::endl;
}
