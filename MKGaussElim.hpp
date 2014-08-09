/* MathKit Gaussian Elimination Algorithm Header */

#ifndef MK_GAUSS_ELIM_HPP
#define MK_GAUSS_ELIM_HPP

#include <memory>
#include "MKMatrix.hpp"

typedef MKVector <float> MKVector_t;
typedef MKMatrix <float> MKMatrix_t;

auto MKGaussPivotIndex(MKMatrix_t &A, std::size_t k) -> std::size_t;
auto MKGaussRowExchange(MKMatrix_t &A, MKVector_t &b, std::size_t k, std::size_t p) -> void;
auto MKGaussFwdElimination(MKMatrix_t &A, MKVector_t &b, std::size_t k) -> void;
auto MKGaussBwdSubstitution(MKMatrix_t &A, MKVector_t &b, MKVector_t &x) -> void;
auto MKGaussElim(MKMatrix_t &A, MKVector_t &b, MKVector_t &x) -> void;

#endif // MK_GAUSS_ELIM_HPP
