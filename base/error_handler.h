#pragma once
#include <iostream>
#include <vector>

/// TO DO:


enum progError
{
    k_UNEXPECTED_TERMINATION_OF_STRING, // A NEW LINE BEFORE SECOND '
    k_UNEXPECTED_TERMINATION_OF_OPERATOR, // ABSENCE OF ; OR UNEXPECTED TRANSITION TO A NEW LINE
    k_ENDLESS_ONE_LINE_COMMENT, // ABSENCE OF } IN COMMENT OR A NEW LINE. COMMENTS ARE ONLY SINGLE-LINE
    k_INCORRECT_TABULATION, // NOT A MULTIPLE OF THE SPECIFIED NUMBER OF SPACES
    k_INCORRECT_NESTING_LEVEL,// TOO MANY OR TOO FEW TABS
    k_TOO_MANY_ARGUMENTS, // IT CAN BE IN WRITE, READ OPERATORS. MAY BE MORE
    k_FIRST_PART_OF_PAIR_IS_MISSED, // ] OR ) OR } BEFORE [ OR ) OR }
    k_NO_PROGRAM_KEY_WORD, //THERE IS NO WORD PROGRAM AT THE BEGINNING
    k_NO_PROGRAM_NAME, // THERE IS NO NAME OF PROGRAM IN FIRST LINE
    k_CUT_DOUBLE_VALUE, // BEGINS FROM POINT. MUST BEGIN FROM DIGIT
    k_ID_NO_DECLARATED,
    k_CONST_NOT_INIT,
    k_CHANGED_CONST_VALUE,
    k_INCORRECT_OPERATION,
    k_INCORRECT_WRITE_CALL,
    k_ID_DOUBLE_DECLARATION,

    k_UNDEFINED_ERROR // DO NOT USE IT! 

};
struct ErrorParam
{
    // line number
    size_t line_num;
    // error number
    progError error_num;
    // flag. if critical - is error, not - warning
    bool is_critical;
    ErrorParam(size_t _line_num = 0, progError _error_num = 
        progError::k_UNDEFINED_ERROR, bool _is_critical = false): line_num(_line_num),
        error_num(_error_num),is_critical(_is_critical)
    {}
};

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
    void print_errors();
    ErrorHandler()
    {
        errors.reserve(4);
    }


    int condition();
    void push(size_t line_num, progError error_num, bool is_critical);

    //only for tests
    ErrorParam operator[](size_t ind) const
    {
        return errors[ind];
    }
};