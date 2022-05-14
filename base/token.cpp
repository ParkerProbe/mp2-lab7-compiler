#include "token.h"
int Token::get_nesting() const
{
    return position_in_string.space % k_MIN_TAB;
}
std::string Token::get_text() const
{
    return text;
}
