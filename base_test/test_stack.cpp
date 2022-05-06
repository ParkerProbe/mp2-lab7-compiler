#include "stack.h"

#include <gtest.h>


TEST(Stack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(Stack<int> st(5));
}
TEST(Stack, cant_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(Stack<int>  st1(-1));
}
TEST(Stack, cant_create_stack_with_biggest_length)
{
  ASSERT_ANY_THROW(Stack<int> st(MaxStackSize + 1));
}
TEST(Stack, cant_create_stack_with_zero_length)
{
  ASSERT_ANY_THROW(Stack<int>  st1(0));
}
TEST(Stack, can_add_elem_in_stack)
{
  Stack<int> st(5);
  ASSERT_NO_THROW(st.add(5));
}
TEST(Stack, can_true_empty)
{
  Stack<int> st(5);
  EXPECT_EQ(true, st.is_empty());
}
TEST(Stack, can_true_full)
{
  Stack<int> st(1);
  st.add(2);
  EXPECT_EQ(true, st.is_full());
}
TEST(Stack, cant_add_excess_elem)
{
  Stack<int> st(10);
  for (int i = 0; i < 10; i++)
    st.add(i);
  ASSERT_ANY_THROW(st.add(1));
}
TEST(Stack, cant_get_elem_from_empty_stack)
{
  Stack<int> st(2);
  ASSERT_ANY_THROW(st.get_top());
}
TEST(Stack, cant_get_info_elem_from_empty_stack)
{
  Stack<int> st(2);
  ASSERT_ANY_THROW(st.info_top());
}
TEST(Stack, can_get_info_elem_from_stack)
{
  Stack<int> st(2);
  st.add(2);
  EXPECT_EQ(2, st.info_top());
}
TEST(Stack, can_get_elem_from_stack)
{
  Stack<int> st(1);
  st.add(2);
  st.get_top();
  EXPECT_EQ(true, st.is_empty());
}
TEST(Stack, can_get_size_stack)
{
  Stack<int> st(2);
  EXPECT_EQ(2, st.get_size());
}
TEST(Stack, can_set_size_stack)
{
  Stack<int> st(2);
  st.set_size(3);
  EXPECT_EQ(3, st.get_size());
}



