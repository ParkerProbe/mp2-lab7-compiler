#include <gtest.h>
#include "text_link.h"
#include "token.h"


TEST(Node, can_create_node)
{
    Token tmp;
    ASSERT_NO_THROW(TTextNode <Token> * node = new TTextNode<Token>(tmp, NULL, NULL));
}
TEST(Node, can_get_content)
{
    Token tmp;
    TTextNode <Token>* node = new TTextNode<Token>(tmp, NULL, NULL);
    ASSERT_NO_THROW(node->get_content());
}
TEST(Node, can_set_content)
{
    Token tmp;
    Token tmp2;
    TTextNode <Token>* node = new TTextNode<Token>(tmp, NULL, NULL);
    ASSERT_NO_THROW(node->set_content(tmp2));
}


TEST(TextLink, can_create_link)
{
    ASSERT_NO_THROW(TText <Token> link);
}
TEST(TextLink, can_go_first_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.go_first_node());
}
TEST(TextLink, can_go_down_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.go_down_node());
}
TEST(TextLink, can_go_next_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.go_next_node());
}
TEST(TextLink, can_go_prev_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.go_prev_node());
}
TEST(TextLink, can_get_current_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.get_node());
}
TEST(TextLink, can_set_current_node)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.set_node(tmp));
}
TEST(TextLink, can_ins_down_node)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.ins_down_node(tmp));
}
TEST(TextLink, can_del_down_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.del_down_node());
}
TEST(TextLink, can_ins_next_node)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.ins_next_node(tmp));
}
TEST(TextLink, can_del_next_node)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.del_next_node());
}
TEST(TextLink, can_ins_down_section)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.ins_down_section(tmp));
}
TEST(TextLink, can_del_down_section)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.del_down_section());
}
TEST(TextLink, can_ins_next_section)
{
    Token tmp;
    TText <Token> link;
    ASSERT_NO_THROW(link.ins_next_section(tmp));
}
TEST(TextLink, can_del_next_section)
{
    TText <Token> link;
    ASSERT_NO_THROW(link.del_next_section());
}