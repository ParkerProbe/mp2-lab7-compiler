#include <gtest.h>
#include "text_link.h"


TEST(Node, can_create_node)
{
    ASSERT_NO_THROW(TTextNode <int> node);
}
TEST(Node, can_get_next)
{
    TTextNode <int> node;
    ASSERT_NO_THROW(node.get_next());
}
TEST(Node, can_get_down)
{
    TTextNode <int> node;
    ASSERT_NO_THROW(node.get_down());
}


TEST(TextLink, can_create_link)
{
    ASSERT_NO_THROW(TText <int> link);
}
TEST(TextLink, can_go_first_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.go_first_node());
}
TEST(TextLink, can_go_down_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.go_down_node());
}
TEST(TextLink, can_go_next_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.go_next_node());
}
TEST(TextLink, can_go_prev_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.go_prev_node());
}
TEST(TextLink, can_get_current_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.get_node());
}
TEST(TextLink, can_set_current_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.set_node(10));
}
TEST(TextLink, can_ins_down_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.ins_down_node(10));
}
TEST(TextLink, can_del_down_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.del_down_node());
}
TEST(TextLink, can_ins_next_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.ins_next_node(10));
}
TEST(TextLink, can_del_next_node)
{
    TText <int> link;
    ASSERT_NO_THROW(link.del_next_node());
}
TEST(TextLink, can_ins_down_section)
{
    TText <int> link;
    ASSERT_NO_THROW(link.ins_down_section(10));
}
TEST(TextLink, can_del_down_section)
{
    TText <int> link;
    ASSERT_NO_THROW(link.del_down_section());
}
TEST(TextLink, can_ins_next_section)
{
    TText <int> link;
    ASSERT_NO_THROW(link.ins_next_section(10));
}
TEST(TextLink, can_del_next_section)
{
    TText <int> link;
    ASSERT_NO_THROW(link.del_next_section());
}