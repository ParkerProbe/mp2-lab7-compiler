#include <gtest.h>
#include "error_handler.h"
TEST(ErrorHandler, can_create_error_handler)
{
    ASSERT_NO_THROW(ErrorHandler eh);
}
TEST(ErrorHandler, can_push_errors)
{
    ErrorHandler eh;
    ErrorParam ep;
    ASSERT_NO_THROW(eh.push(ep));
    ASSERT_NO_THROW(eh.push(12, progError::k_UNDEFINED_ERROR, true));
}
TEST(ErrorHandler, can_return_errors)
{
    ErrorHandler eh;
    ErrorParam ep(12, progError::k_UNDEFINED_ERROR, true);
    EXPECT_EQ(ep, eh[0]);
}

TEST(ErrorHandler, can_create_exception_by_error_codes)
{
    ASSERT_NO_THROW(ErrorHandler eh(progError::k_SUCCESS));
}
TEST(ErrorHandler, can_get_error_codes)
{
    ErrorHandler eh(progError::k_SUCCESS);
    EXPECT_EQ(progError::k_SUCCESS, eh.get_error());
}
TEST(ErrorHandler, can_error_comment)
{
    ErrorHandler eh(progError::k_UNDEFINED_ERROR);
    EXPECT_EQ("UNDEFINED ERROR", eh.get_comment());
}