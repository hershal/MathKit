/* MathKit MKVector Test Header */

#ifndef MK_VECTOR_TEST_HPP
#define MK_VECTOR_TEST_HPP

const std::string k_num_misses = "k_num_misses";
const std::string k_num_hits = "k_num_hits";
const std::string k_num_total = "k_num_total";

auto random_insertion_test(std::size_t vector_len,
                           std::size_t num_insertions,
                           float percentage_out_of_bounds)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> >;

auto arithmetic_test(std::size_t vector_len)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> >;

auto fused_arithmetic_assignment_test(std::size_t vector_len)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> >;

auto fill_test(std::size_t vector_len)
    -> std::shared_ptr<TKNumberedAttribute<std::size_t> >;

#endif /* MK_VECTOR_TEST_HPP */
