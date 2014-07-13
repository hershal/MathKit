// MathKit Vector Testing

#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <ctime>

#include <boost/assert.hpp>

#include "MKVector.hpp"

void run_random_insertion_test();

int main() {
    std::size_t len = 10;
    for (auto i=0; i<len; ++i) {
        run_random_insertion_test();
    }
}

void run_random_insertion_test() {
    std::srand(std::time(0));

    std::size_t len = (rand()%10000);
    std::size_t num_insertions = (rand()%100000);

    MKVector<double> v(len);

    for (std::size_t i=0; i<num_insertions; ++i) {
        std::size_t loc = (rand()%len + len/2);
        double value = (double)(rand());
        try {
            v(loc) = value;
            BOOST_ASSERT_MSG(v(loc) == value,
                             (std::stringstream() << value << "!=" << v(i)).str().c_str());
        } catch (std::out_of_range e) {
            BOOST_ASSERT_MSG(loc >= len,
                             (std::stringstream() << loc << ">=" << len).str().c_str());
        }
    }
}
