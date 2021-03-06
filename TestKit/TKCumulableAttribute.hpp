/*! TestKit TKCumulableAttribute Header */

#ifndef TK_CUMULABLE_ATTRIBUTE_HPP
#define TK_CUMULABLE_ATTRIBUTE_HPP

#include "TKBaseAttribute.hpp"
#include <map>

template <typename T>
class TKCumulableAttribute : public TKBaseAttribute {
public:
    TKCumulableAttribute(const std::string name = "NO_NAME",
                         const std::string prefix = "",
                         const std::string infix = "=",
                         const std::string postfix = "\n")
        : TKBaseAttribute(name, prefix, infix, postfix) {}
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

    auto to_string(const std::string pre_prefix = "",
                   const std::string post_postfix = "")
        const -> const std::string {

        auto stream = std::stringstream();

        for (auto iter = this->attribute.begin(); iter != this->attribute.end(); ++iter) {
            if (iter != this->attribute.begin()) {
                stream << this->m_postfix << post_postfix;
            }
            stream << pre_prefix << this->m_prefix
                   << iter->first << this->m_infix
                   << iter->second;
        }
        return stream.str();
    }
    auto get_type() -> TKAttrType { return cumulable; }
    auto get_type_string() -> std::string { return "cumulable"; }

private:
    std::map<std::string, T> attribute;
};

#endif /* TK_CUMULABLE_ATTRIBUTE_HPP */
