/*! TestKit TKNumberedAttribute Header */

#ifndef TK_NUMBERED_ATTRIBUTE_HPP
#define TK_NUMBERED_ATTRIBUTE_HPP

#include "TKBaseAttribute.hpp"
#include <map>

template <typename T>
class TKNumberedAttribute : public TKBaseAttribute {
public:
    TKNumberedAttribute() {}
    ~TKNumberedAttribute() {}
    auto operator+ (const TKNumberedAttribute& addend) -> TKNumberedAttribute {
        auto sum = TKNumberedAttribute();
        for (auto at : attribute) {
            attribute[at.first] = at.second + (*addend)[at.first];
        }
        return *this;
    }

    auto operator+= (const TKNumberedAttribute& addend) -> TKNumberedAttribute& {
        for (auto at : addend.repr()) {
            attribute[at.first] = at.second + (attribute)[at.first];
        }
        return *this;
    }

    auto operator[] (const std::string key) const -> const T {
        return attribute.at(key);
    }

    auto operator[] (const std::string key) -> T& {
        // std::cout << "ADDED" << key  << std::endl;
        return attribute[key];
    }

    auto repr() const -> const std::map<std::string, T> {
        return attribute;
    }

auto to_string(std::string sep1 = "=", std::string sep2 = "\n") -> std::string {
    auto stream = std::stringstream();

    for (auto iter = attribute.begin(); iter != attribute.end(); ++iter) {
        if (iter != attribute.begin()) {
            stream << sep2;
        }
        stream << iter->first << sep1 << iter->second;
    }
    return stream.str();
}

private:
    std::map<std::string, T> attribute;
};

#endif /* TK_NUMBERED_ATTRIBUTE_HPP */
