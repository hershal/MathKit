/* MathKit Gaussian Elimination Algorithm Header */

#ifndef MK_GAUSS_ELIM_HPP
#define MK_GAUSS_ELIM_HPP

#include <memory>
#include "MKMatrix.hpp"

typedef std::shared_ptr<MKVector <float> > MKVector_p;

auto MKGaussPivotIndex(MKMatrix_p A, std::size_t k) -> std::size_t;
auto MKGaussRowExchange(MKMatrix_p A, MKVector_p b, std::size_t k, std::size_t p) -> void;
auto MKGaussFwdElimination(MKMatrix_p A, MKVector_p b, std::size_t k) -> void;
auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x, std::size_t n) -> void;
auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> std::size_t;

#endif // MK_GAUSS_ELIM_HPP
