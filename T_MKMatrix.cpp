/* MathKit MKMatirx Testing */

#include <sstream>
#include <iostream>
#include <random>
#include <ctime>

#include <boost/assert.hpp>

#include "MKMatrix.hpp"
#include "TKCumulableAttribute.hpp"

#include "T_MKVector.hpp"

typedef float float_data_type_t;

int main () {
    std::size_t len = 100;
    std::size_t mat_xy = pow(10000.0, 0.5);

    /* Fill Test */
    auto fill_test_results = TKCumulableAttribute<std::size_t>();
    for (auto i=0; i<len; ++i) {
        fill_test_results += *(fill_test(mat_xy));
    }
    std::cout << "fill test\n" <<
        fill_test_results.to_string() << "\n" << std::endl;

}

auto fill_test(const std::size_t mat_xy)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    /* Create the matrix */
    MKMatrix<float_data_type_t> m1(mat_xy);
    MKMatrix<float_data_type_t> m2(mat_xy);
    std::vector<float_data_type_t> fill_value(mat_xy);

    /* Populate the matrix values */
    for (auto i=0; i<mat_xy; ++i) {
        fill_value[i] = (float_data_type_t)(rand()%mat_xy);
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
