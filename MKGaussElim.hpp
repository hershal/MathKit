/* MathKit Gaussian Elimination Algorithm Header */

#ifndef MK_GAUSS_ELIM_HPP
#define MK_GAUSS_ELIM_HPP

#include <memory>
#include "MKMatrix.hpp"

typedef std::shared_ptr<MKVector <float> > MKVector_p;

auto MKGaussPivotIndex(MKMatrix_p A, int k) -> int;
auto MKGaussRowExchange(MKMatrix_p A, MKVector_p b, int k, int p, int n) -> void;
auto MKGaussFwdElimination(MKMatrix_p A, MKVector_p b, int k, int n) -> void;
auto MKGaussBwdSubstitution(MKMatrix_p A, MKVector_p b, MKVector_p x, int n) -> void;
auto MKGaussElim(MKMatrix_p A, MKVector_p b, MKVector_p x) -> int;

#endif // MK_GAUSS_ELIM_HPP
