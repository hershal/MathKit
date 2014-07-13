// MathKit Vector Testing

#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>

#include "MKVector.hpp"

const std::string k_num_misses = "k_num_misses";
const std::string k_num_hits = "k_num_hits";
const std::string k_num_total = "k_num_total";

typedef std::map<std::string, std::size_t> attribute_t;
typedef std::shared_ptr< std::map<std::string, std::size_t> > attribute_t_ptr;

attribute_t_ptr accumulate_results(attribute_t_ptr augend,
                                   attribute_t_ptr addend);
attribute_t_ptr assemble_test_results(std::size_t hits,
                                      std::size_t misses,
                                      std::size_t total);
attribute_t_ptr addition_test(std::size_t vector_len);
attribute_t_ptr random_insertion_test(std::size_t vector_len,
                                      std::size_t num_insertions,
                                      float percentage_out_of_bounds);

std::string string_results(std::string sep1,
                           std::string sep2,
                           attribute_t_ptr attrib);

int main() {
    std::size_t len = 100;

    auto insertion_test_results = std::make_shared<attribute_t>();
    for (auto i=0; i<len; ++i) {
        insertion_test_results = accumulate_results
            (random_insertion_test(10000, 100000, 0.25), insertion_test_results);
    }
    std::cout << string_results("=", "\n", insertion_test_results) << "\n" << std::endl;

    auto addition_test_results = std::make_shared<attribute_t>();
    for (auto i=0; i<len; ++i) {
        addition_test_results = accumulate_results
            (addition_test(10000), addition_test_results);
    }
    std::cout << string_results("=", "\n", addition_test_results) << "\n" << std::endl;
}

attribute_t_ptr addition_test(std::size_t vector_len) {
    std::srand(std::time(0));

    MKVector <float> v1(vector_len);
    MKVector <float> v2(vector_len);

    /* Populate the vector here */
    for (auto i=0; i<vector_len; ++i) {
        v1(i) = (float)(rand());
        v2(i) = (float)(rand());
    }

    /* Perform the addition */
    MKVector <float> v3 = v1 + v2;

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        BOOST_ASSERT_MSG
            (v3(i) == v1(i) + v2(i),
             (std::stringstream() << v3(i) << "!=" << v1(i) << " + " << v2(i))
             .str().c_str());
    }

    /* Generate result receipt */
    auto m = std::make_shared<attribute_t>();
    (*m)[k_num_total] = vector_len;
    return m;
}

attribute_t_ptr random_insertion_test(std::size_t vector_len,
                                      std::size_t num_insertions,
                                      float percentage_out_of_bounds) {
    std::srand(std::time(0));
    std::size_t num_hits = 0;
    std::size_t num_misses = 0;

    MKVector<float> v(vector_len);

    /* Perform the test */
    for (std::size_t i=0; i<num_insertions; ++i) {

        /* Randomize insertion location */
        std::size_t loc =
            (std::size_t)((rand()%vector_len)
                          + (vector_len*percentage_out_of_bounds));

        /* Randomize insertion data */
        float value = (float)(rand());

        /* Verify insertion mechanisms */
        try {
            v(loc) = value;
            BOOST_ASSERT_MSG(v(loc) == value,
                             (std::stringstream() << value << "!=" << v(i))
                             .str().c_str());
            num_hits++;
        } catch (std::out_of_range e) {
            BOOST_ASSERT_MSG(loc >= vector_len,
                             (std::stringstream() << loc << ">=" << vector_len)
                             .str().c_str());
            num_misses++;
        }
    }

    /* Generate result receipt */
    auto m = std::make_shared<attribute_t>();
    (*m)[k_num_misses] = num_misses;
    (*m)[k_num_hits] = num_hits;
    (*m)[k_num_total] = num_insertions;
    return m;
}

attribute_t_ptr accumulate_results(attribute_t_ptr augend,
                                   attribute_t_ptr addend) {
    auto accum = std::make_shared<attribute_t>();
    for (auto at : *augend) {
        (*accum)[at.first] = at.second + (*addend)[at.first];
    }
    return accum;
}

std::string string_results(std::string sep1,
                           std::string sep2,
                           attribute_t_ptr attrib) {
    auto stream = std::stringstream();

    for (auto iter = attrib->begin(); iter != attrib->end(); ++iter) {
        if (iter != attrib->begin()) {
            stream << sep2;
        }
        stream << iter->first << sep1 << iter->second;
    }
    return stream.str();
}
