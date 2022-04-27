#pragma once
#include <string>

#define k_EXCEPTION_COUNT 2

enum error_codes
{
    k_NO_ERROR,
    k_UNDEFINED_EXCEPTION,
};
class EqException
{
private:
    void operator=(const EqException& other) = delete;
    EqException(EqException& eq) = delete;
    EqException() = delete;

    // code of error
    error_codes error;
    const std::string comment[k_EXCEPTION_COUNT] = { "NO ERROR", "UNDEFINED EXCEPTION" };


public:
    // create exception using error_codes::<something>
    EqException(error_codes error_)
        : error(error_)
    {}
    ~EqException() = default;

    inline const std::string& get_comment() const
    {
        return comment[error];
    }

    inline int get_error() const
    {
        return error;
    }

};