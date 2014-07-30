/* MathKit MKVector Test Header */

#ifndef MK_VECTOR_TEST_HPP
#define MK_VECTOR_TEST_HPP

const std::string k_num_misses = "k_num_misses";
const std::string k_num_hits = "k_num_hits";
const std::string k_num_total = "k_num_total";

auto random_insertion_test(const std::size_t vector_len,
                           const std::size_t num_insertions,
                           const float percentage_out_of_bounds)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> >;

auto arithmetic_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> >;

auto fused_arithmetic_assignment_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> >;

auto fill_test(const std::size_t vector_len)
    -> const std::shared_ptr<TKCumulableAttribute<std::size_t> >;

#endif /* MK_VECTOR_TEST_HPP */
