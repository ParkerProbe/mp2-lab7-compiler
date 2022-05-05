

#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_get_infix)
{
  TPostfix p;
  std::string form = "m div (60+a)";
  p.set_infix(form);
  std::string in = "m div (60+a)";
  EXPECT_EQ(in, p.get_infix());
}
TEST(TPostfix, can_get_postfix)
{
  TPostfix p;
  std::string form = "m div (60+a)";
  p.set_infix(form);
  p.to_postfix();
  std::string post = "60|a|+_|m|dv|";
  EXPECT_EQ(post, p.get_postfix());
}
TEST(TPostfix, can_calculate)
{
    TPostfix p;
    std::string form = "20 mod (60+1)";
    p.set_infix(form);
    p.to_postfix();
    EXPECT_EQ(20, p.calculate());
}
