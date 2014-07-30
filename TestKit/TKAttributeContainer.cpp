/* TestKit Attribute Container Implementation */

#include <string>
#include <sstream>
#include "TKAttributeContainer.hpp"

TKAttributeContainer::TKAttributeContainer() {
    m_attributes.clear();
}

TKAttributeContainer::~TKAttributeContainer() {}

auto TKAttributeContainer::add(const std::shared_ptr<TKBaseAttribute> a) -> void {
    m_attributes.push_back(a);
}

auto TKAttributeContainer::to_string(std::string tab)
    -> const std::string {

    std::stringstream stream;
    for (auto iter = m_attributes.begin(); iter != m_attributes.end(); ++iter) {
        if (iter != m_attributes.begin()) {
            stream << "\n\n";
        }
        stream << (*iter)->get_name() << ":\n";
        stream << (*iter)->to_string(tab);
    }
    return stream.str();
}
