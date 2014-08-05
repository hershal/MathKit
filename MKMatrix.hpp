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
    MKMatrix(std::size_t n = 0) : MKVector<MKVector<T> >(n, MKVector<T>(n)) {
        /* this->array = std::vector<MKVector<MKVector<T> > >(); */
        /* this->array.resize(n); */
        /* MKVector<MKVector<T> >(n, MKVector<float>(n)); */
        std::cout << "mat inst: " << n
                  << " vec inst: " << MKVector<MKVector<T> >::size()
                  << " this inst: " << size()
                  << " this_prt inst: " << this->array.size()
                  << std::endl;
    }

    auto operator= (const MKMatrix<T>& v) -> MKMatrix<T>& {
        std::cout << "mat: pre: this: " << size() << "  that: " << v.size() << std::endl;

        /* Not sure which is faster */
        MKVector<MKVector<T> >::array = v.array;
        /* this->array = v.array; */

        std::cout << "mat: post: this: " << size() << "  that: " << v.size() << std::endl;
        return *this;
    }

    auto operator= (const T c) -> MKMatrix<T>& {
        /* MKVector<MKVector<T> >::array = v.array; */
        for (auto i=0 ; i<size(); ++i) {

            /* Not sure which is faster */
            MKVector<MKVector<T> >::array[i] = c;
            /* this->array[i] = c; */
        }
        return *this;
    }

    auto print_out() -> const std::string {
        std::stringstream stream;
        stream << "test" << this->array.to_string();
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
