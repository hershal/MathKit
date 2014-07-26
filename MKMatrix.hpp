/*! MathKit Matrix Class */

#ifndef MK_MATRIX
#define MK_MATRIX

#include "MKVector.hpp"

typedef MKVector< MKVector<float> > MKMatrix_t;
typedef std::shared_ptr< MKMatrix_t > MKMatrix_p;
typedef std::unique_ptr< MKMatrix_t > MKMatrix_u;

template <class T>
class MKMatrix : public MKVector<MKVector<T> > {
public:
    MKMatrix(std::size_t n = 0) {
        /* this->array = std::vector<MKVector<MKVector<T> > >(); */
        /* this->array.resize(n); */
        MKVector<MKVector<T> >(n, MKVector<float>(n));
        std::cout << "MAT INST: " << n
                  << " VEC INST: " << MKVector<MKVector<T> >::size() 
                  << " THISINST: " << size()
                  << std::endl;
    }

    auto operator= (const MKMatrix<T>& v) -> MKMatrix<T>& {
        /* std::cout << "MAT: PRE: THIS: " << size() << "  THAT: " << v.size() << std::endl; */
        /* this->array = MKVector<MKVector<T> >::v.array; */
        MKVector<MKVector<T> >::array = v.array;
        /* std::cout << "MAT: POST: THIS: " << size() << "  THAT: " << v.size() << std::endl; */
        return *this;
    }

    auto print_out() -> const std::string {
        std::stringstream stream;
        stream << "TEST" << this->array.to_string();
        return stream.str();
    }

    auto repr() -> const MKMatrix {
        return this->array;
    }

    using MKVector<MKVector<T> >::MKVector;
    using MKVector<MKVector<T> >::operator=;
    using MKVector<MKVector<T> >::operator();
    using MKVector<MKVector<T> >::operator[];
    using MKVector<MKVector<T> >::to_string;
    using MKVector<MKVector<T> >::size;

private:

};

#endif /* MK_MATRIX */
