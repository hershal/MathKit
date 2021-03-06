/* MathKit MKVector Testing */

#include <vector>
#include <sstream>
#include <iostream>
#include <random>
#include <ctime>
#include <map>

#include <boost/assert.hpp>

#include "MKVector.hpp"
#include "TKCumulableAttribute.hpp"

#include "TKAttributeContainer.hpp"

#include "T_MKVector.hpp"

int main() {
    std::size_t len = 100;
    std::size_t vector_len = 10000;

    std::size_t insertion_num_insertions = 100000;
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
            *(random_insertion_test
              (vector_len, insertion_num_insertions,
               insertion_percentage_out_of_bounds));
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

    std::cout << container.to_string() << std::endl;
}

auto fused_arithmetic_assignment_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));

    MKVector <float> v_const(vector_len);

    MKVector <float> v_add(vector_len);
    MKVector <float> v_sub(vector_len);
    MKVector <float> v_mul(vector_len);
    MKVector <float> v_div(vector_len);

    MKVector <float> v_test_add(vector_len);
    MKVector <float> v_test_sub(vector_len);
    MKVector <float> v_test_mul(vector_len);
    MKVector <float> v_test_div(vector_len);

    /* Populate the test vectors' data and the verification vectors' data */
    for (auto i=0; i<vector_len; ++i) {
        v_const(i) = (float)(rand());

        v_add(i) = (float)(rand());
        v_sub(i) = (float)(rand());
        v_mul(i) = (float)(rand());
        v_div(i) = (float)(rand());

        v_test_add(i) = v_add(i) + v_const(i);
        v_test_sub(i) = v_sub(i) - v_const(i);
        v_test_mul(i) = v_mul(i) * v_const(i);
        v_test_div(i) = v_div(i) / v_const(i);
    }

    /* Perform the addition */
    v_add += v_const;
    v_sub -= v_const;
    v_mul *= v_const;
    v_div /= v_const;

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        BOOST_ASSERT_MSG
            ((v_test_add(i) != v_test_add(i)) || v_test_add(i) == v_add(i),
             (std::stringstream() << v_test_add(i) << "!=" << v_add(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_test_sub(i) != v_test_sub(i)) || v_test_sub(i) == v_sub(i),
             (std::stringstream() << v_test_sub(i) << "!=" << v_sub(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_test_mul(i) != v_test_mul(i)) || v_test_mul(i) == v_mul(i),
             (std::stringstream() << v_test_mul(i) << "!=" << v_mul(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_test_div(i) != v_test_div(i)) || v_test_div(i) == v_div(i),
             (std::stringstream() << v_test_div(i) << "!=" << v_div(i))
             .str().c_str());
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = vector_len;
    return m;
}

auto arithmetic_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));

    MKVector <float> v1(vector_len);
    MKVector <float> v2(vector_len);

    /* Populate the vectors here */
    for (auto i=0; i<vector_len; ++i) {
        v1(i) = (float)(rand());
        v2(i) = (float)(rand());
    }

    /* Perform the arithmetic */
    MKVector <float> v_add = v1 + v2;
    MKVector <float> v_sub = v1 - v2;
    MKVector <float> v_mul = v1 * v2;
    MKVector <float> v_div = v1 / v2;

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        BOOST_ASSERT_MSG
            ((v_add(i) != v_add(i)) || v_add(i) == v1(i) + v2(i),
             (std::stringstream() << v_add(i) << "!=" << v1(i) << " + " << v2(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_sub(i) != v_sub(i)) || v_sub(i) == v1(i) - v2(i),
             (std::stringstream() << v_sub(i) << "!=" << v1(i) << " - " << v2(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_mul(i) != v_mul(i)) || v_mul(i) == v1(i) * v2(i),
             (std::stringstream() << v_mul(i) << "!=" << v1(i) << " * " << v2(i))
             .str().c_str());
        BOOST_ASSERT_MSG
            ((v_div(i) != v_div(i)) || v_div(i) == v1(i) / v2(i),
             (std::stringstream() << v_div(i) << "!=" << v1(i) << " / " << v2(i))
             .str().c_str());
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = vector_len;
    return m;
}

auto random_insertion_test(const std::size_t vector_len,
                           const std::size_t num_insertions,
                           const float percentage_out_of_bounds)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

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
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_misses] = num_misses;
    (*m)[k_num_hits] = num_hits;
    (*m)[k_num_total] = num_insertions;
    return m;
}

auto fill_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> > {

    std::srand(std::time(0));
    std::size_t num_total = 0;

    /* Create the vectors */
    MKVector <float> v1(vector_len);
    MKVector <float> v2(vector_len);

    /* Populate the vector values */
    float fill_value = (float)(rand());
    v1 = fill_value;
    for (auto i=0; i<vector_len; ++i) {
        v2[i] = fill_value;
        ++num_total;
    }

    /* Verify output */
    for (auto i=0; i<vector_len; ++i) {
        BOOST_ASSERT_MSG(((v1[i] == v2[i]) && (v1[i] == fill_value)),
                         (std::stringstream() << fill_value << "!=" << v1[i] << "!=" << v2[i])
                         .str().c_str());
    }

    /* Generate result receipt */
    auto m = std::make_shared<TKCumulableAttribute<std::size_t> >();
    (*m)[k_num_total] = num_total;
    return m;
}
