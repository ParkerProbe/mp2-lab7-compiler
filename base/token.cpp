#include "token.h"
int Token::get_nesting() const
{
    return position_in_string.space / k_MIN_TAB;
}
std::string Token::get_text() const
{
    return text;
}
//Token::LexemeType Token::g_type() const
//{
//    return type;
//}
Token::LexemeSubType Token::s_type() const
{
    return subtype;
}
bool Token::operator==(const std::string lex_text)
{
    return text == lex_text;
}
bool Token::operator!=(const std::string lex_text)
{
    return text != lex_text;
}
