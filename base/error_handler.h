#pragma once
#include <iostream>
#include <vector>
#include "error_param.h"

class ErrorHandler
{
private:
    static const int k_ERROR_HANDLER_MAX = 16;
    //ErrorParam
    std::vector<ErrorParam> errors;
   // size_t cur_pos;
    const std::string comment[k_ERROR_HANDLER_MAX] = {
        "Unexpected termination of string", 
        "Unexpected termination of operator", "Endless one-line comment", 
        "Incorrect tabulation", "Incorrect level of nesting", 
        "Too many arguments","First part of pair is missed", 
        "No program key word", "No program name", "Double value is cut",
        "Identifier is not declared", "Const did not initialized", 
        "Const value was changed", "Incorrect operation", 
        "Incorrect write call", "Double declaration of identifier"
        "Undefined error" 
    };


    void print_head();
    void print_cur_error(size_t cur_pos);
    int get_symbol_quan(size_t num);

public:
    //prints every cur error + head
    void print_errors()
    {
        print_head();
        for (size_t i = 0; i < errors.size(); i++) {
            print_cur_error(i);
        }
    }
    ErrorHandler():errors(0)
    {}


    int condition() 
    {
        if (errors.size() == 0)
            return 0;
        for (int i = 0; i < errors.size(); i++)
            if (errors[i].is_critical)
                return 2;
        return 1;
    }
    void push(int line_num, progError error_num, bool is_critical) 
    {
        errors.push_back(ErrorParam(line_num, error_num, is_critical));
    }

    //only for tests
    ErrorParam operator[](size_t ind) const
    {
        return errors[ind];
    }
};