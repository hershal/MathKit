/*! MathKit Matrix Class */

#ifndef MK_MATRIX
#define MK_MATRIX

#include <set>
#include <vector>

#include "MKVector.hpp"

#include <iostream>

template <class T>
class MKMatrix : public MKVector<MKVector<T> > {
public:
    MKMatrix(std::size_t n = 0) : MKVector<MKVector<T> >(n, MKVector<T>(n)) { }

    auto operator= (const MKMatrix<T>& v) -> MKMatrix<T>& {
        /* Not sure which is faster */
        MKVector<MKVector<T> >::array = v.array;
        /* this->array = v.array; */
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

    auto operator() (const std::size_t i, const std::size_t j) const
        -> const T { return (*this)(i)(j); }

    auto operator* (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKMatrix operator* index is invalid");
        MKVector<T> result(v.size());
        for(std::size_t i=0; i<size(); ++i) {
            for (std::size_t j=0; j<size(); ++j) {
                result(i) += (*this)(i,j)*v(j);
            }
        }
        return result;
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
