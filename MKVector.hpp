/*! MathKit Vector Class */

#include <vector>

template <class T>
class MKVector {
public:
    /*! MKVector constructor with size */
    MKVector(std::size_t n) {
        array.resize(n);
        ar_size = n;
    }

    /*! MKVector constructor with size and inner argument constructor */
    MKVector(std::size_t n, const T& t) {
        array.resize(n, t);
        ar_size = n;
    }

    /*! MKVector destructor */
    ~MKVector() {
        /* Don't need to delete, everything is local */
    }

    /*! MKVector copy constructor */
    MKVector(const MKVector<T>& v) {
        array = v.to_vector();
        ar_size = v.size();
    }

    /*! MKVector get-pure-std::vector method */
    auto to_vector() const -> const std::vector<T> {
        return array;
    }

    friend auto operator<< (std::ostream& os, MKVector<T>& v) -> std::ostream& {
        os << v.to_string();
        return os;
    }

    /*! MKVector string printer */
    auto to_string(std::string sep = ", ") -> const std::string {
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
    auto inline dim() const -> const std::size_t { return ar_size; }

    /*! MKVector get size (alias to dim()) */
    auto inline size() const -> const std::size_t { return ar_size; }

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
        array = v.to_vector();
        return *this;
    }

    /*! MKVector fill-vector-with-scalar operator */
    auto operator= (T x) -> MKVector<T>& {
        for(int i=0; i<size(); i++) {
            array[i] = x;
        }
        return *this;
    }

    /*! MKVector addition operator */
    auto operator+ (const MKVector<T>& v) -> MKVector<T> {
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        MKVector<T> result(v);
        for(int i=0; i<size(); i++) result.array[i] = array[i] + result.array[i];
        return result;
    }

    /*! MKVector fused addition-assignment operator */
    auto operator+= (const MKVector<T>& v) -> MKVector<T>& { /* Fused add-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] + v(i);
        return *this;
    }

    /*! MKVector subtraction operator */
    auto operator- (const MKVector<T>& v) -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(v);
        for(int i=0; i<size(); i++) result.array[i] = array[i] - result.array[i];
        return result;
    }

    /*! MKVector fused subtraction-assignment operator */
    auto operator-= (const MKVector<T>& v) -> MKVector<T>& { /* Fused subtract-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] - v(i);
        return *this;
    }

    /*! MKVector multiply operator */
    auto operator* (const MKVector<T>& v) -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(v);
        for(int i=0; i<size(); i++) result.array[i] = array[i] * result.array[i];
        return result;
    }

    /*! MKVector fused multiply-assignment operator */
    auto operator*= (const MKVector<T>& v) -> MKVector<T>& { /* Fused multiply-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] * v(i);
        return *this;
    }

    /*! MKVector division operator */
    auto operator/ (const MKVector<T>& v) -> MKVector<T> {
        if(size() != v.size())
            throw std::out_of_range("MKVector index is invalid");
        MKVector<T> result(v);
        for(int i=0; i<size(); i++) result.array[i] = array[i] / result.array[i];
        return result;
    }

    /*! MKVector fused divide-assignment operator */
    auto operator/= (const MKVector<T>& v) -> MKVector<T>& { /* Fused divide-assign */
        if(size() != v.size()) {
            throw std::out_of_range("MKVector index is invalid");
        }
        for(int i=0; i<size(); i++) array[i] = array[i] / v(i);
        return *this;
    }

private:
    /*! pointer to elements of MKVector */
    std::vector<T> array;
    std::size_t ar_size;
};

template <class T>
auto fma(const MKVector<T>& x, const MKVector<T>& y, const MKVector<T>& z)
    -> std::shared_ptr< MKVector<T> > {
    // MKVector<T> result(x);
    auto result = std::make_shared< MKVector<T> >(x);
    for(int i=0; i<x.size(); i++) (*result)[i] = fma(x[i], y[i], z[i]);
    return result;
}
