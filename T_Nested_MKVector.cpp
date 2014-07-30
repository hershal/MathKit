/* MathKit Nested MKVector Testing */

#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>
#include <cmath>

#include "MKVector.hpp"
#include "TKCumulableAttribute.hpp"

#include "TKAttributeContainer.hpp"

#include "T_MKVector.hpp"

auto fused_multiply_add_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> >;

int main() {

    std::size_t len = 100;
    std::size_t vector_len = (float)(pow(10000.0, 0.5));

    std::size_t insertion_num_insertions = (float)(pow(100000.0, 0.5));
    float insertion_percentage_out_of_bounds = 0.25;

    auto container = TKAttributeContainer();

    /* Fill Test */
    auto fill_test_results =
        std::make_shared<TKCumulableAttribute<std::size_t> >
        ("Fill Test");
    for (auto i=0; i<len; ++i) {
        *(fill_test_results) += *(fill_test(vector_len));
    }
    container.add(fill_test_results);

    /* Insertion Test */
    auto insertion_test_results =
        std::make_shared<TKCumulableAttribute<std::size_t> >
        ("Insertion Test");
    for (auto i=0; i<len; ++i) {
        *(insertion_test_results) +=
            *random_insertion_test(vector_len, insertion_num_insertions,
                                   insertion_percentage_out_of_bounds);
    }
    container.add(insertion_test_results);

    /* Arithmetic Test */
    auto arithmetic_test_results =
        std::make_shared<TKCumulableAttribute<std::size_t> >
        ("Arithmetic Test");
    for (auto i=0; i<len; ++i) {
        *(arithmetic_test_results) += *(arithmetic_test(vector_len));
    }
    container.add(arithmetic_test_results);

    /* Fused Arithmetic-Assignment Test */
    auto fused_arithmetic_assignment_test_results =
        std::make_shared<TKCumulableAttribute<std::size_t> >
        ("Fused Arithmetic-Assignment Test");
    for (auto i=0; i<len; ++i) {
        *(fused_arithmetic_assignment_test_results) +=
            *(fused_arithmetic_assignment_test(vector_len));
    }
    container.add(fused_arithmetic_assignment_test_results);

    /* Fused Multiply-Add Test */
    auto fused_multiply_add_test_results =
        std::make_shared<TKCumulableAttribute<std::size_t> >
        ("Fused Multiply-Add Test");
    for (auto i=0; i<len; ++i) {
        *(fused_multiply_add_test_results) +=
            *(fused_multiply_add_test(vector_len));
    }
    container.add(fused_multiply_add_test_results);

    std::cout << container.to_string() << std::endl;
}

auto random_insertion_test(const std::size_t vector_len,
                           const std::size_t num_insertions,
                           const float percentage_out_of_bounds)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

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
                                 (std::stringstream() << i_loc << ">=" << vector_len << " && " << j_loc << ">=" << vector_len)
                                 .str().c_str());
                num_misses++;
            }
        }
    }

    /* std::printf("%s\n", mat.to_string("\n").c_str()); */

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_misses] = num_misses;
    (*m)[k_num_hits] = num_hits;
    (*m)[k_num_total] = num_total;
    return m;
}

auto arithmetic_test(std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    MKVector < MKVector<float> > v1(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v2(vector_len, MKVector<float>(vector_len));

    /* Populate the vectors here */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            v1(i)(j) = (float)(rand()%vector_len);
            v2(i)(j) = (float)(rand()%vector_len);
            ++num_total;
        }
    }

    /* Perform the arithmetic */
    MKVector < MKVector<float> > v_add = v1 + v2;
    MKVector < MKVector<float> > v_sub = v1 - v2;
    MKVector < MKVector<float> > v_mul = v1 * v2;
    MKVector < MKVector<float> > v_div = v1 / v2;

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            BOOST_ASSERT_MSG
                ((v_add(i)(j) != v_add(i)(j)) || v_add(i)(j) == v1(i)(j) + v2(i)(j),
                 (std::stringstream() << v_add(i)(j) << "!=" << v1(i)(j) << " + " << v2(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                ((v_sub(i)(j) != v_sub(i)(j)) || v_sub(i)(j) == v1(i)(j) - v2(i)(j),
                 (std::stringstream() << v_sub(i)(j) << "!=" << v1(i)(j) << " - " << v2(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                ((v_mul(i)(j) != v_mul(i)(j)) || v_mul(i)(j) == v1(i)(j) * v2(i)(j),
                 (std::stringstream() << v_mul(i)(j) << "!=" << v1(i)(j) << " * " << v2(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                ((v_div(i)(j) != v_div(i)(j)) || v_div(i)(j) == v1(i)(j) / v2(i)(j),
                 (std::stringstream() << v_div(i)(j) << "!=" << v1(i)(j) << " / " << v2(i)(j))
                 .str().c_str());
        }
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}

auto fused_arithmetic_assignment_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    MKVector < MKVector<float> > v_const(vector_len, MKVector<float>(vector_len));

    MKVector < MKVector<float> > v_add(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_sub(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_mul(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_div(vector_len, MKVector<float>(vector_len));

    MKVector < MKVector<float> > v_test_add(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_test_sub(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_test_mul(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_test_div(vector_len, MKVector<float>(vector_len));

    /* Populate the test vectors' data and the verification vectors' data */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            v_const(i)(j) = (float)(rand());

            v_add(i)(j) = (float)(rand());
            v_sub(i)(j) = (float)(rand());
            v_mul(i)(j) = (float)(rand());
            v_div(i)(j) = (float)(rand());

            v_test_add(i)(j) = v_add(i)(j) + v_const(i)(j);
            v_test_sub(i)(j) = v_sub(i)(j) - v_const(i)(j);
            v_test_mul(i)(j) = v_mul(i)(j) * v_const(i)(j);
            v_test_div(i)(j) = v_div(i)(j) / v_const(i)(j);

            ++num_total;
        }
    }

    /* Perform the addition */
    v_add += v_const;
    v_sub -= v_const;
    v_mul *= v_const;
    v_div /= v_const;

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            BOOST_ASSERT_MSG
                (v_test_add(i)(j) == v_add(i)(j),
                 (std::stringstream() << v_test_add(i)(j) << "!=" << v_add(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                (v_test_sub(i)(j) == v_sub(i)(j),
                 (std::stringstream() << v_test_sub(i)(j) << "!=" << v_sub(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                (v_test_mul(i)(j) == v_mul(i)(j),
                 (std::stringstream() << v_test_mul(i)(j) << "!=" << v_mul(i)(j))
                 .str().c_str());
            BOOST_ASSERT_MSG
                (v_test_div(i)(j) == v_div(i)(j),
                 (std::stringstream() << v_test_div(i)(j) << "!=" << v_div(i)(j))
                 .str().c_str());
        }
    }
    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}

auto fill_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    /* Create the vectors */
    MKVector < MKVector<float> > v1(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v2(vector_len, MKVector<float>(vector_len));
    std::vector<float> fill_value(vector_len);

    /* Populate the vector values */
    for (auto i=0; i<vector_len; ++i) {
        fill_value[i] = (float)(rand());
        v1[i] = fill_value[i];
        for (auto j=0; j<vector_len; ++j) {
            v2[i][j] = fill_value[i];
            ++num_total;
        }
    }

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            BOOST_ASSERT_MSG(((v1[i][j] == v2[i][j]) && (v1[i][j] == fill_value[i])),
                             (std::stringstream() << fill_value[i] << "!="<< v1[i][j] << "!=" << v2[i][j])
                             .str().c_str());
        }
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}

auto fused_multiply_add_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    MKVector < MKVector<float> > v_x(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_y(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_z(vector_len, MKVector<float>(vector_len));

    MKVector < MKVector<float> > v_test_fma(vector_len, MKVector<float>(vector_len));
    MKVector < MKVector<float> > v_fma(vector_len, MKVector<float>(vector_len));

    /* Populate the test vectors' data and the verification vectors' data */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            v_x(i)(j) = (float)(rand());
            v_y(i)(j) = (float)(rand());
            v_z(i)(j) = (float)(rand());

            v_test_fma(i)(j) = fma(v_x(i)(j), v_y(i)(j), v_z(i)(j));

            ++num_total;
        }
        v_fma(i) = *(fma(v_x(i), v_y(i), v_z(i)));
    }

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        for (auto j=0; j<vector_len; ++j) {
            BOOST_ASSERT_MSG
                (v_test_fma(i)(j) == v_fma(i)(j),
                 (std::stringstream() << v_test_fma(i)(j) << "!=" << v_fma(i)(j))
                 .str().c_str());
        }
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}
