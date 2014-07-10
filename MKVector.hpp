/*! MathKit Vector Header Class */

#ifndef MK_VECTOR_H
#define MK_VECTOR_H

#include <iostream>
#include <vector>

template <typename T>
class MKVector {
public:
    MKVector(std::size_t = 0);
    MKVector(const MKVector&);
    ~MKVector();

    auto operator() (size_t) const -> const T; //! get-value index operator
    auto operator() (size_t) -> T&; //! set-value index operator

    auto operator=(const MKVector&) -> MKVector&; //! equate-two-vecs operator
    auto operator=(T) -> MKVector&;        //! fill-vec-by-scalar operator
    auto operator+(const MKVector&) -> MKVector;  //! add-two-vecs operator
    auto operator-(const MKVector&) -> MKVector;  //! subtract-two-vecs operator

    auto to_vector() const -> const std::vector<T>;
    auto to_string(std::string sep = ", ") -> const std::string;
    auto size() -> const std::size_t;

private:
    std::vector<T> array; //pointer to elements of MKVector
};

#endif // MK_VECTOR_H

