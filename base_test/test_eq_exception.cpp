#include <gtest.h>
#include "eq_exception.h"
TEST(EqException, can_create_exception_by_error_codes)
{
    ASSERT_NO_THROW(EqException eq(error_codes::k_NO_ERROR_CODE));
}
TEST(EqException, can_get_error_codes)
{
    EqException eq(error_codes::k_UNDEFINED_EXCEPTION);
    EXPECT_EQ(error_codes::k_UNDEFINED_EXCEPTION, eq.get_error());
}
TEST(EqException, can_error_comment)
{
    EqException eq(error_codes::k_UNDEFINED_EXCEPTION);
    EXPECT_EQ("UNDEFINED EXCEPTION", eq.get_comment());
}