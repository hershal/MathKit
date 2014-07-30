/*! TestKit TKBaseAttribute Header */

#ifndef TK_BASE_ATTRIBUTE_HPP
#define TK_BASE_ATTRIBUTE_HPP

template <typename T>
class TKBaseAttribute {
public:
    TKBaseAttribute() {}
    ~TKBaseAttribute() {}
    virtual auto to_string(const std::string prefix = "",
                           const std::string infix = "=",
                           const std::string postfix = "\n") const
        -> const std::string = 0;
    virtual auto repr() const -> const std::map<std::string, T> = 0;
    virtual auto operator+= (const TKBaseAttribute<T>& addend) -> TKBaseAttribute<T>& = 0;
protected:
    std::map<std::string, T> attribute;
};

#endif /* TK_BASE_ATTRIBUTE_HPP */
