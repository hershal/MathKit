/* MathKit MKMatirx Testing */

#include <sstream>
#include <iostream>
#include <random>
#include <ctime>

#include <boost/assert.hpp>

#include "MKMatrix.hpp"
#include "TKCumulableAttribute.hpp"

#include "T_MKVector.hpp"

auto fill_test(std::size_t mat_xy)
    -> std::shared_ptr<TKCumulableAttribute<std::size_t> >;

int main () {
    std::size_t len = 100;
    std::size_t mat_xy = (float)(pow(10000.0, 0.5));

    std::size_t insertion_num_insertions = (float)(pow(100000.0, 0.5));
    float insertion_percentage_out_of_bounds = 0.25;

    /* Fill Test */
    auto fill_test_results = TKCumulableAttribute<std::size_t>();
    for (auto i=0; i<len; ++i) {
        fill_test_results += *(fill_test(mat_xy));
    }
    /* std::cout << "fill test\n" << */
    /*     fill_test_results.to_string() << "\n" << std::endl; */

}

auto fill_test(std::size_t mat_xy)
    -> std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    /* Create the matrix */
    MKMatrix<float> m1(mat_xy);
    MKMatrix<float> m2(mat_xy);
    std::vector<float> fill_value(mat_xy);

    /* Populate the matrix values */
    for (auto i=0; i<mat_xy; ++i) {
        fill_value[i] = (float)(rand());
        m1[i] = fill_value[i];
        for (auto j=0; j<mat_xy; ++j) {
            m2[i][j] = fill_value[i];
            ++num_total;
        }
    }

    /* Verify output */
    for (auto i=0; i<mat_xy; ++i) {
        for (auto j=0; j<mat_xy; ++j) {
            BOOST_ASSERT_MSG(((m1[i][j] == m2[i][j]) &&
                              (m1[i][j] == fill_value[i])),
                             (std::stringstream()
                              << fill_value[i] << "!="
                              << m1[i][j]<< "!="
                              << m2[i][j])
                             .str().c_str());
        }
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}
