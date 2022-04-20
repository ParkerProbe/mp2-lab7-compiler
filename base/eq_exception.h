#ifndef EQ_EXCEPTION_H_
#define EQ_EXCEPTION_H_

#include <string>

#define MAX_COMMENT_LEN 256

enum error_codes
{
    k_NO_ERROR,
    k_UNDEFINED_EXCEPTION,
};
class EqException
{
private:
    void operator=(const EqException& other) = delete;

    // code of error
    error_codes error;
    const std::string k_set_comment[2] = { "NO ERROR", "UNDEFINED EXCEPTION"};

public:
    // create exception using error_codes::<something>
    EqException(error_codes error_)
        : error(error_)
    {}
    EqException(EqException& eq) :error(eq.error)
    {}
    ~EqException() = default;

    inline const std::string& get_comment() const
    {
        return k_set_comment[error];
    }

    inline int get_error() const
    {
        return error;
    }

};


#endif // EQ_EXCEPTION_H
