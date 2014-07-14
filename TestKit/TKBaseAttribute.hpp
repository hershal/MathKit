/*! TestKit TKBaseAttribute Header */

#ifndef TK_BASE_ATTRIBUTE_HPP
#define TK_BASE_ATTRIBUTE_HPP

class TKBaseAttribute {
public:
    TKBaseAttribute() {}
    ~TKBaseAttribute() {}
    virtual std::string to_string(std::string sep1, std::string sep2) = 0;
private:
    /* Nothing Here */
};

#endif /* TK_BASE_ATTRIBUTE_HPP */
