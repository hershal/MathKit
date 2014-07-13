/*! MathKit Vector Class */

#include <iostream>
#include <vector>

template <typename T>
class MKVector {
public:
    MKVector(std::size_t n){ //constructor
        array.resize(n);
    }

    ~MKVector(){ //destructor
        // Don't need to delete anything
    }

    MKVector(const MKVector& v) { //copy constructor
        array = v.to_vector();
    }

    auto to_vector() const -> const std::vector<T> {
        return array;
    }

    auto to_string(std::string sep = ", ") -> const std::string {
        std::string out;
        for (auto i=0; i<size(); ++i) {
            if (i != 0) { out += sep; }
            out += std::to_string(array[i]);
        }
        return out;
    }

    auto size() const -> const std::size_t {
        return array.size();
    }

    auto operator() (std::size_t i) const -> const T { //get-value operator
        if(i<0 || i>=size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        return array[i];
    }

    auto operator() (std::size_t i) -> T& { //set-value operator
        if(i<0 || i>=size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        return array[i];
    }

    auto operator= (const MKVector& v) -> MKVector& { //equate-two-vecs operator
        array = v.to_vector();
        return *this;
    }

    auto operator= (T x) -> MKVector& { //fill-vec-by-scalar operator
        for(int i=0; i<size(); i++) {
            array[i] = x;
        }
        return *this;
    }

    auto operator+ (const MKVector& v) -> MKVector { //add-two-vecs operator
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        MKVector sum(size());
        for(int i=0; i<size(); i++) sum.array[i] = array[i] + v.array[i];
        return sum;
    }

    auto operator- (const MKVector& v) -> MKVector { //subtract-two-vecs operator
        if(size() != v.size)
            throw std::out_of_range("MKVector index is invalid");
        MKVector difference(size());
        for(int i=0; i<size(); i++) difference.array[i] = array[i] - v.array[i];
        return difference;
    }
private:
    std::vector<T> array; //pointer to elements of MKVector
};
