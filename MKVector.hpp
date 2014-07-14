/*! MathKit Vector Class */

#include <iostream>
#include <vector>

template <typename T>
class MKVector {
public:
    /*! MKVector constructor with size */
    MKVector(std::size_t n){
        array.resize(n);
    }

    /*! MKVector destructor */
    ~MKVector() {
        /* Don't need to delete, everything is local */
    }

    /*! MKVector copy constructor */
    MKVector(const MKVector& v) {
        array = v.to_vector();
    }

    /*! MKVector get-pure-std::vector method */
    auto to_vector() const -> const std::vector<T> {
        return array;
    }

    /*! MKVector string printer */
    auto to_string(std::string sep = ", ") -> const std::string {
        std::string out;
        for (auto i=0; i<size(); ++i) {
            if (i != 0) { out += sep; }
            out += std::to_string(array[i]);
        }
        return out;
    }

    /*! MKVector get size */
    auto size() const -> const std::size_t {
        return array.size();
    }

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
    auto operator= (const MKVector& v) -> MKVector& {
        array = v.to_vector();
        return *this;
    }

    /*! MKVector fill-vector-with-scalar operator */
    auto operator= (T x) -> MKVector& {
        for(int i=0; i<size(); i++) {
            array[i] = x;
        }
        return *this;
    }

    /*! MKVector addition operator */
    auto operator+ (const MKVector& v) -> MKVector {
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        MKVector sum(size());
        for(int i=0; i<size(); i++) sum.array[i] = array[i] + v.array[i];
        return sum;
    }

    /*! MKVector fused addition-assignment operator */
    auto operator+= (const MKVector& v) -> MKVector& {
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] + v(i);
        return *this;
    }

    /*! MKVector subtraction operator */
    auto operator- (const MKVector& v) -> MKVector {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector difference(size());
        for(int i=0; i<size(); i++) difference.array[i] = array[i] - v.array[i];
        return difference;
    }

    /*! MKVector fused subtraction-assignment operator */
    auto operator-= (const MKVector& v) -> MKVector& { /* Fused subtract-equality */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] - v(i);
        return *this;
    }

    /*! MKVector multiply operator */
    auto operator* (const MKVector& v) -> MKVector {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector difference(size());
        for(int i=0; i<size(); i++) difference.array[i] = array[i] * v.array[i];
        return difference;
    }

    /*! MKVector fused multiply-assignment operator */
    auto operator*= (const MKVector& v) -> MKVector& { /* Fused subtract-equality */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] * v(i);
        return *this;
    }

    /*! MKVector division operator */
    auto operator/ (const MKVector& v) -> MKVector {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector difference(size());
        for(int i=0; i<size(); i++) difference.array[i] = array[i] / v.array[i];
        return difference;
    }

    /*! MKVector fused divide-assignment operator */
    auto operator/= (const MKVector& v) -> MKVector& { /* Fused subtract-equality */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] / v(i);
        return *this;
    }

private:
    /*! pointer to elements of MKVector */
    std::vector<T> array;
};
