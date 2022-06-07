#pragma once
#include "prog_error.h"
struct ErrorParam
{
    // line number
    int line_num;
    // error number
    progError error_num;
    // flag. if critical - is error, not - warning
    bool is_critical;
    ErrorParam(int _line_num = 0, progError _error_num =
        progError::k_UNDEFINED_ERROR, bool _is_critical = false) : line_num(_line_num),
        error_num(_error_num), is_critical(_is_critical)
    {}
    bool operator<(const ErrorParam& ep)
    {
        return line_num < ep.line_num;
    }
    bool operator==(const ErrorParam& ep)
    {
        return (line_num == ep.line_num && error_num == ep.error_num && is_critical == ep.is_critical);
    }
};