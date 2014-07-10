// MathKit Vector Testing

#include <iostream>
#include <memory>
#include <vector>

#include "MKVector.hpp"

int main() {
    
    // std::shared_ptr<MKVector<double> > v(std::make_shared<MKVector<double> >(3));
    MKVector<double> v(3);
    v(0) = 0;
    v(1) = 1;
    v(2) = 2;
    
    std::cout << v.to_string() << std::endl;
}
