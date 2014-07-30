/*! TestKit TKCumulableAttribute Header */

#ifndef TK_CUMULABLE_ATTRIBUTE_HPP
#define TK_CUMULABLE_ATTRIBUTE_HPP

#include "TKBaseAttribute.hpp"
#include <map>

template <typename T>
class TKCumulableAttribute : public TKBaseAttribute {
public:
    TKCumulableAttribute() : TKBaseAttribute() {}
    ~TKCumulableAttribute() {}
    auto operator+ (const TKCumulableAttribute<T>& addend) -> TKCumulableAttribute<T> {
        auto sum = TKCumulableAttribute();
        for (auto at : this->attribute) {
            this->attribute[at.first] = at.second + (*addend)[at.first];
        }
        return *this;
    }

    auto operator+= (const TKCumulableAttribute<T>& addend) -> TKCumulableAttribute<T>& {
        for (auto at : addend.repr()) {
            this->attribute[at.first] = at.second + (this->attribute)[at.first];
        }
        return *this;
    }

    auto operator[] (const std::string key) const -> const T {
        return this->attribute.at(key);
    }

    auto operator[] (const std::string key) -> T& {
        // std::cout << "ADDED" << key  << std::endl;
        return this->attribute[key];
    }

    auto repr() const -> const std::map<std::string, T> {
        return this->attribute;
    }

    auto to_string(const std::string prefix = "", 
                   const std::string infix = "=",
                   const std::string postfix = "\n") const
        -> const std::string {

        auto stream = std::stringstream();

        for (auto iter = this->attribute.begin(); iter != this->attribute.end(); ++iter) {
            if (iter != this->attribute.begin()) {
                stream << postfix;
            }
            stream << prefix << iter->first << infix << iter->second;
        }
        return stream.str();
    }

private:
    std::map<std::string, T> attribute;
};

#endif /* TK_CUMULABLE_ATTRIBUTE_HPP */
