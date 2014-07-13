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

attribute_t_ptr accumulate_results(attribute_t_ptr addend, attribute_t_ptr augend);
attribute_t_ptr assemble_test_results(std::size_t hits, std::size_t misses, std::size_t total);
attribute_t_ptr run_random_insertion_test_out_of_bounds(std::size_t vector_len,
                                                        std::size_t num_insertions,
                                                        float percentage_out_of_bounds);

std::string string_results(std::string sep1, std::string sep2, attribute_t_ptr attrib);

int main() {
    std::size_t len = 100;
    auto tot = std::make_shared<attribute_t>();

    for (auto i=0; i<len; ++i) {
        tot = accumulate_results(run_random_insertion_test_out_of_bounds(10000,
                                                                         100000,
                                                                         0.25),
                                 tot);
    }

    std::cout << string_results("=", "\n", tot) << std::endl;
}

attribute_t_ptr run_random_insertion_test_out_of_bounds(std::size_t vector_len,
                                                        std::size_t num_insertions,
                                                        float percentage_out_of_bounds) {

    std::srand(std::time(0));
    std::size_t num_hits = 0;
    std::size_t num_misses = 0;

    MKVector<float> v(vector_len);

    for (std::size_t i=0; i<num_insertions; ++i) {
        std::size_t loc = (std::size_t)((rand()%vector_len) + (vector_len*percentage_out_of_bounds));
        float value = (float)(rand());
        try {
            v(loc) = value;
            BOOST_ASSERT_MSG(v(loc) == value,
                             (std::stringstream() << value << "!=" << v(i)).str().c_str());
            num_hits++;
        } catch (std::out_of_range e) {
            BOOST_ASSERT_MSG(loc >= vector_len,
                             (std::stringstream() << loc << ">=" << vector_len).str().c_str());
            num_misses++;
        }
    }
    return assemble_test_results(num_hits, num_misses, num_insertions);
}

void run_random_insertion_test_in_bounds() {

    std::srand(std::time(0));

    std::size_t len = (rand()%10000);
    std::size_t num_insertions = (rand()%100000);

    MKVector<double> v(len);

    for (std::size_t i=0; i<num_insertions; ++i) {
        std::size_t loc = (rand()%len);
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

attribute_t_ptr assemble_test_results(std::size_t hits, std::size_t misses, std::size_t total) {
    auto m = std::make_shared<attribute_t>();
    (*m)[k_num_misses] = misses;
    (*m)[k_num_hits] = hits;
    (*m)[k_num_total] = total;
    return m;
}

attribute_t_ptr accumulate_results(attribute_t_ptr addend, attribute_t_ptr augend) {
    auto accum = std::make_shared<attribute_t>();
    for (auto at : *addend) {
        (*accum)[at.first] = at.second + (*augend)[at.first];
    }
    return accum;
}

std::string string_results(std::string sep1, std::string sep2, attribute_t_ptr attrib) {
    auto stream = std::stringstream();

    for (auto iter = attrib->begin(); iter != attrib->end(); ++iter) {
        if (iter != attrib->begin()) {
            stream << sep2;
        }
        stream << iter->first << sep1 << iter->second;
    }
    return stream.str();
}
