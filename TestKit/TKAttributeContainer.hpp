/* TestKit Attribute Container Header */

#ifndef TK_ATTRIBUTE_CONTAINTER_HPP
#define TK_ATTRIBUTE_CONTAINTER_HPP

#include "TKBaseAttribute.hpp"
#include <vector>

class TKAttributeContainer {
public:
    TKAttributeContainer();
    ~TKAttributeContainer();
    auto add(const std::shared_ptr<TKBaseAttribute> a) -> void;
    auto to_string() -> const std::string;

private:
    std::vector<std::shared_ptr<TKBaseAttribute> > m_attributes;
};

#endif  /* TK_ATTRIBUTE_CONTAINTER_HPP */
