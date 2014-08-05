/*! MathKit Vector Class */

#ifndef MK_VECTOR
#define MK_VECTOR

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

template <class T>
class MKVector {
public:
    /*! MKVector default constructor */
    MKVector() {
        /*!
          REMEMBER: you cannot resize an existing MKVector, so be aware this
          is not particularly useful, especially since MKVector does not know
          what kind of data you're putting into it. I.e., if you have a MKVector
          of a map (or something), the outer-most MKVector does not know this
          and thus cannot recursively resize the underlying data structures.

          That's just something you should be aware of before you use the
          default constructor.
        */
        std::cout << "IMPLICIT INSTANTIATION" << std::endl;

        array.clear();
    }

    /*! MKVector constructor with size */
    MKVector(const std::size_t n) {
        array.resize(n);
    }

    /*! MKVector constructor with size and inner argument constructor */
    MKVector(const std::size_t n, const T& t) {
        array.resize(n, t);
    }

    /*! MKVector destructor */
    ~MKVector() {
        /* Don't need to delete, everything is local */
    }

    /*! MKVector copy constructor */
    MKVector(const MKVector<T>& v) {
        array = v.to_vector();
    }

    /*! MKVector get-pure-std::vector method */
    auto to_vector() const -> const std::vector<T> {
        return array;
    }

    friend auto operator<< (std::ostream& os, const MKVector<T>& v) -> std::ostream& {
        os << v.to_string();
        return os;
    }

    /*! MKVector string printer */
    auto to_string(const std::string sep = ", ") const -> const std::string {
        std::stringstream out;
        out << "[";
        for (auto i=0; i<size(); ++i) {
            if (i != 0) { out << sep; }
            out << array[i];
        }
        out << "]";
        return out.str();
    }

    /*! MKVector get dimension (alias to size()) */
    auto dim() const -> const std::size_t { return array.size(); }

    /*! MKVector get size (alias to dim()) */
    auto size() const -> const std::size_t { return array.size(); }

    /*! MKVector get-value operator */
    auto operator[] (const std::size_t i) const -> const T {
        if(i<0 || i>=size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        return array[i];
    }

    /*! MKVector set-value operator */
    auto operator[] (const std::size_t i) -> T& {
        if(i<0 || i>=size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        return array[i];
    }

    /*! MKVector get-value operator */
    auto operator() (const std::size_t i) const -> const T { return (*this)[i]; }

    /*! MKVector set-value operator */
    auto operator() (const std::size_t i) -> T& { return (*this)[i]; }

    /*! MKVector assignment operator */
    auto operator= (const MKVector<T>& v) -> MKVector<T>& {
        std::cout << "VEC: PRE: THIS: " << size() << "  THAT: " << v.size() << std::endl;
        array = v.to_vector();
        std::cout << "VEC: " << to_string() << std::endl;
        std::cout << "VEC: POST: THIS: " << size() << "  THAT: " << v.size() << std::endl;
        return *this;
    }

    /*! MKVector fill-vector-with-scalar operator */
    auto operator= (const T x) -> MKVector<T>& {
        for(int i=0; i<size(); i++) {
            array[i] = x;
        }
        return *this;
    }

    /*! MKVector addition operator */
    auto operator+ (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        MKVector<T> result(*this);
        for(int i=0; i<size(); i++) result.array[i] += v.array[i];
        return result;
    }

    /*! MKVector fused addition-assignment operator */
    auto operator+= (const MKVector<T>& v) -> MKVector<T>& { /* Fused add-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] += v(i);
        return *this;
    }

    /*! MKVector subtraction operator */
    auto operator- (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(*this);
        for(int i=0; i<size(); i++) result.array[i] -= v.array[i];
        return result;
    }

    /*! MKVector fused subtraction-assignment operator */
    auto operator-= (const MKVector<T>& v) -> MKVector<T>& { /* Fused subtract-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] -= v(i);
        return *this;
    }

    /*! MKVector multiply operator */
    auto operator* (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(*this);
        for(int i=0; i<size(); i++) result.array[i] *= v.array[i];
        return result;
    }

    /*! MKVector fused multiply-assignment operator */
    auto operator*= (const MKVector<T>& v) -> MKVector<T>& { /* Fused multiply-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] *= v(i);
        return *this;
    }

    /*! MKVector division operator */
    auto operator/ (const MKVector<T>& v) const -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(*this);
        for(int i=0; i<size(); i++) result.array[i] /= v.array[i];
        return result;
    }

    /*! MKVector fused divide-assignment operator */
    auto operator/= (const MKVector<T>& v) -> MKVector<T>& { /* Fused divide-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] /= v(i);
        return *this;
    }

protected:
    /*! pointer to elements of MKVector */
    std::vector<T> array;
};

template <class T>
auto fma(const MKVector<T>& x, const MKVector<T>& y, const MKVector<T>& z)
    -> std::shared_ptr< MKVector<T> > {
    // MKVector<T> result(x);
    auto result = std::make_shared< MKVector<T> >(x);
    for(int i=0; i<x.size(); i++) (*result)[i] = fma(x[i], y[i], z[i]);
    return result;
}

#endif /* MK_VECTOR */
