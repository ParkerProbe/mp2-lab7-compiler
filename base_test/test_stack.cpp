//#include "stack.h"

#include <gtest.h>
#include "stack.h"

TEST(Stack, can_create_stack)
{
    ASSERT_NO_THROW(Stack<int> st);
}
TEST(Stack, can_add_elem_in_stack)
{
    Stack<int> st;
    ASSERT_NO_THROW(st.add(5));
}
TEST(Stack, can_true_empty)
{
    Stack<int> st;
    EXPECT_EQ(true, st.is_empty());
}
TEST(Stack, cant_get_elem_from_empty_stack)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.get_top());
}
TEST(Stack, cant_get_info_elem_from_empty_stack)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.info_top());
}
TEST(Stack, can_get_info_elem_from_stack)
{
    Stack<int> st;
    st.add(2);
    EXPECT_EQ(2, st.info_top());
}
TEST(Stack, can_get_elem_from_stack)
{
    Stack<int> st;
    st.add(2);
    st.get_top();
    EXPECT_EQ(true, st.is_empty());
}
TEST(Stack, can_get_size_stack)
{
    Stack<int> st;
    EXPECT_EQ(2000, st.get_size());
}
TEST(Stack, can_set_size_stack)
{
    Stack<int> st;
    st.set_size(3);
    EXPECT_EQ(3, st.get_size());
}


