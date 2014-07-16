#include <iostream>
#include <vector>
#include <sstream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>
#include <cmath>

#include "MKVector.hpp"
#include "TKNumberedAttribute.hpp"

const std::string k_num_misses = "k_num_misses";
const std::string k_num_hits = "k_num_hits";
const std::string k_num_total = "k_num_total";

auto random_insertion_test(std::size_t vector_len,
                           std::size_t num_insertions,
                           float percentage_out_of_bounds)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> >;

int main() {

    std::size_t len = 100;
    std::size_t vector_len = (float)(pow(10000.0, 0.5));
    /* std::size_t len = 10; */
    /* std::size_t vector_len = 10000; */

    std::size_t insertion_num_insertions = (float)(pow(100000.0, 0.5));
    float insertion_percentage_out_of_bounds = 0.25;

    /* Insertion Test */
    auto insertion_test_results = TKNumberedAttribute<std::size_t>();
    for (auto i=0; i<len; ++i) {
        insertion_test_results += *random_insertion_test(vector_len,
                                                         insertion_num_insertions,
                                                         insertion_percentage_out_of_bounds);
    }
    std::cout << "insertion test\n" <<
        insertion_test_results.to_string() << "\n" << std::endl;
}

auto random_insertion_test(std::size_t vector_len, std::size_t num_insertions,
                           float percentage_out_of_bounds)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_hits = 0;
    std::size_t num_misses = 0;
    std::size_t num_total = 0;

    MKVector<MKVector<float> > mat(vector_len, MKVector<float>(vector_len));

    /* Perform the test */
    for (std::size_t i=0; i<num_insertions; ++i) {
        std::size_t i_loc =
            (std::size_t)((rand()%vector_len)
                          + (vector_len*percentage_out_of_bounds/2));
        for (std::size_t j=0; j<num_insertions; ++j) {
            /* Randomize insertion location */
            std::size_t j_loc =
                (std::size_t)((rand()%vector_len)
                              + (vector_len*percentage_out_of_bounds/2));
            num_total++;

            /* Randomize insertion data */
            float value = (float)(rand());
    
            /* Verify insertion mechanisms */
            try {
                mat[i_loc][j_loc] = value;
                BOOST_ASSERT_MSG(mat[i_loc][j_loc] == value,
                                 (std::stringstream() << value << "!=" << mat[i_loc][j_loc])
                                 .str().c_str());
                num_hits++;
            } catch (std::out_of_range e) {
                BOOST_ASSERT_MSG(i_loc >= vector_len || j_loc >= vector_len,
                                 (std::stringstream() << i_loc << ">=" << vector_len << " && " << i_loc << ">=" << vector_len)
                                 .str().c_str());
                num_misses++;
            }
        }
    }

    /* std::printf("%s\n", mat.to_string("\n").c_str()); */

    /* Generate result receipt */
    auto m = std::make_shared<TKNumberedAttribute<std::size_t> >();
    (*m)[k_num_misses] = num_misses;
    (*m)[k_num_hits] = num_hits;
    (*m)[k_num_total] = num_total;
    return m;
}