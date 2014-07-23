/*! MathKit Matrix Class */

#ifndef MK_MATRIX
#define MK_MATRIX

#include "MKVector.hpp"

typedef MKVector< MKVector<float> > MKMatrix;
typedef std::shared_ptr< MKMatrix > MKMatrix_p;

#endif /* MK_MATRIX */
