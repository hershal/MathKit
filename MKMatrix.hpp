/*! MathKit Matrix Class */

#ifndef MK_MATRIX
#define MK_MATRIX

#include "MKVector.hpp"

typedef MKVector< MKVector<float> > MKMatrix_t;
typedef std::shared_ptr< MKMatrix_t > MKMatrix_p;
typedef std::unique_ptr< MKMatrix_t > MKMatrix_u;

#endif /* MK_MATRIX */
