// MathKit Argument

#ifndef MK_ARGUMENT_HPP
#define MK_ARGUMENT_HPP

#include <string>
#include <memory>

template <typename T>
class MKArgument {
public:
    MKArgument(T *value, std::string description) { MKArgument(value, description, ""); }
    MKArgument(T *value, std::string description, std::string long_description) {
        m_value = value;
        m_description = description;
        m_long_description = long_description;
    }
    auto get_value() const -> const T { return *m_value; }
    auto get_description() const -> const std::string { return m_description; }
    auto get_long_description() const -> const std::string { return m_long_description; }
    auto to_string() const -> const std::string {
        if (m_description.empty()) {
            return std::to_string(*m_value);
        }
        return m_description + ": " + std::to_string(*m_value);
    }
    auto to_long_string() const -> const std::string {
        if (m_long_description.empty()) {
            return to_string();
        }
        return to_string() + " -- " + m_long_description;
    }
private:
    T *m_value;
    std::string m_description;
    std::string m_long_description;
};

#endif // MK_ARGUMENT_HPP
