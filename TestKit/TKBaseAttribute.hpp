/*! TestKit TKBaseAttribute Header */

#ifndef TK_BASE_ATTRIBUTE_HPP
#define TK_BASE_ATTRIBUTE_HPP

class TKBaseAttribute {
public:
    TKBaseAttribute() {}
    ~TKBaseAttribute() {}
    virtual auto to_string(const std::string prefix = "",
                           const std::string infix = "=",
                           const std::string postfix = "\n")
        const -> const std::string = 0;
private:
    /* Nothing here */
};

#endif /* TK_BASE_ATTRIBUTE_HPP */
