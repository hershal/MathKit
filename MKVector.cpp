/*! MathKit Vector Implemenation Class */

#include "MKVector.hpp"

template <typename T>
class MKVector {
public:
    MKVector::MKVector(size_t n){ //constructor 
        array.resize(n);
    }

    MKVector::~MKVector(){ //destructor 
        // Don't need to delete anything
    }

    MKVector::MKVector(const MKVector& v) { //copy constructor
        array = v.to_vector();
    }

    auto MKVector::to_vector() const -> const std::vector {
        return array;
    }

    auto MKVector::to_string(std::string sep) -> const std::string {
        std::string out;
        for (auto i=0; i<size(); ++i) {
            if (i != 0) { out += sep; }
            out += std::to_string(array[i]);
        }
        return out;
    }

    auto MKVector::size() -> const std::size_t {
        return array.size();
    }

    auto MKVector::operator() (std::size_t i) const -> const double { //get-value operator
        if(i<0 || i>=size())
            std::cerr << "MKVector index is invalid\n";
        return array[i]; 
    }

    auto MKVector::operator() (int i) -> double& { //set-value operator
        if(i<0 || i>=size())
            cerr << "MKVector index is invalid\n";
        return array[i]; 
    }

    auto MKVector::operator= (const MKVector& v) -> MKVector& { //equate-two-vecs operator
        array = v.to_vector();
        return *this;
    }

    auto MKVector::operator= (double x) -> MKVector& { //fill-vec-by-scalar operator
        for(int i=0; i<size(); i++) {
            array[i] = x;
        }
        return *this;
    }

    auto MKVector::operator+ (const MKVector& v) -> MKVector { //add-two-vecs operator
        if(size() != v.size())
            cerr << "MKVector addition undefined -- sizes differ\n";
        MKVector sum(size);
        for(int i=0; i<size; i++) sum.array[i] = array[i] + v.array[i];
        return sum;
    }

    auto MKVector::operator- (const MKVector& v) -> MKVector { //subtract-two-vecs operator
        if(size != v.size)
            cerr << "MKVector subtraction undefined -- sizes differ\n";
        MKVector difference(size);
        for(int i=0; i<size; i++) difference.array[i] = array[i] - v.array[i];
        return difference;
    }
};
