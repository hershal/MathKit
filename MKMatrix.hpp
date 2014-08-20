/*! MathKit Matrix Class */

#ifndef MK_MATRIX
#define MK_MATRIX

#include <set>
#include <vector>

#include "MKVector.hpp"

#include <iostream>

template <class F> struct abs_compare {
    bool operator() (const F &one, const F &two) const {
        return fabs(one) < fabs(two);
    }
};

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

    /*! MKMatrix set-value operator */
    auto operator() (const std::size_t i, const std::size_t j)
        -> T& { return (*this)(i)(j); }

    /*! MKMatrix get-value operator */
    auto operator() (const std::size_t i, const std::size_t j) const
        -> const T { return (*this)(i)(j); }

    auto operator* (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKMatrix operator* index is invalid");

        /* Should reduce roundoff errors by adding sequentially from
           smallest to largest */
        auto addition_set = std::vector<std::set<T, abs_compare<T> > >();
        addition_set.resize(v.size());
        MKVector<T> result(v.size());

        /* To ensure that the solution is numerically stable, we add
           the numbers in order of increasing magnitude */
        for (std::size_t i=0; i<size(); ++i) {
            for (std::size_t j=0; j<size(); ++j) {
                addition_set[i].insert((*this)(i,j)*v(j));
            }
        }

        /* Here we actually add the numbers into the MKVector */
        for (std::size_t i=0; i<result.size(); ++i) {
            /* num should be sorted since it's in a set */
            for (const auto num : addition_set[i]) {
                result(i) += num;
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
