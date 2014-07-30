/*! TestKit TKBaseAttribute Header */

#ifndef TK_BASE_ATTRIBUTE_HPP
#define TK_BASE_ATTRIBUTE_HPP

enum TKAttrType {base=0, cumulable=1};

class TKBaseAttribute {
public:
    TKBaseAttribute(const std::string name, const std::string prefix,
                    const std::string infix, const std::string postfix) :
        m_name(name), m_prefix(prefix), m_infix(infix), m_postfix(postfix) {}
    ~TKBaseAttribute() {}
    virtual auto to_string(const std::string pre_prefix = "",
                           const std::string post_postfix = "")
        const -> const std::string = 0;
    auto get_name() -> std::string {return m_name;}
    virtual auto get_type() -> TKAttrType { return base; }
    virtual auto get_type_string() -> std::string { return "base"; }
protected:
    std::string m_name;
    std::string m_prefix;
    std::string m_infix;
    std::string m_postfix;
private:
    /* Nothing here */
};

#endif /* TK_BASE_ATTRIBUTE_HPP */
