#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using std::cout;

/// TO DO:

#define k_ERROR_HANDLER_MAX 15
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
    k_UNDEFINED_LEXEME, // MOST ERRORS IN LEXICAL ANALYZER
    k_ID_NO_DECLARATED,
    k_CONST_NOT_INIT,
    k_CHANGED_CONST_VALUE,
    k_INCORRECT_OPERATION,
    k_INCORRECT_WRITE_CALL,


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
    //ErrorParam* errors;
    std::vector<ErrorParam> errors;
   // size_t cur_pos;
    const std::string comment[k_ERROR_HANDLER_MAX] = {
        "Unexpected termination of string", 
        "Unexpected termination of operator", "Endless one-line comment", 
        "Incorrect tabulation", "Incorrect level of nesting", 
        "Too many arguments", "No program key word","No program name", 
        "First part of pair is missed", "Identifier is not declared", 
        "Const did not initialized", "Const value was changed",
        "Incorrect operation", "Incorrect write call",
        "Undefined error" };


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
    void push(ErrorParam err);

    //only for tests
    ErrorParam operator[](size_t ind) const
    {
        return errors[ind];
    }


    //void print_error(size_t ind, std::ostream& os)
    //{
    //    std::ostringstream ot;
    //    const char vert = 179, horiz = 196;
    //    const char left_up = 192, up = 193, rigth_up = 217;
    //    const char left_down = 218, down = 194, rigth_down = 191;
    //    //console length = 120
    //    os << left_down;
    //    for (int i = 1; i < 17; i++)
    //        os << horiz;
    //    os << down;
    //    for (int i = 18; i < 119; i++)
    //        os << horiz;
    //    os << rigth_down;
    //    os << '\n';
    //    os << vert;
    //    os << errors[ind].error_num;
    //    ot << errors[ind].error_num;
    //    for (int i = ot.str().size(); i < 16; i++)
    //        os << ot.str();
    //    os << vert;
    //    for
    //}
    //void print_errors()
    //{
    //    std::ostringstream os;
    //    for (int i = 0; i < size; i++) {
    //        os << errors[i].error_num;
    //        for(int i=0;i<)
    //    }
    //}
    //void print()
    //{
    //    print_head();
    //    print_error();
    //}
    //friend std::ostream& operator<<(std::ostream& os, const ErrorHandler& eh);
};

//std::ostream& operator<<(std::ostream& os, const ErrorHandler& eh)
//{
//    const char vert = 179, horiz = 196;
//    const char left_up = 192, up = 193, rigth_up = 217;
//    const char left_down = 218, down = 194, rigth_down = 191;
//    //console length = 120
//    os << left_down;
//    for (int i = 1; i < 17; i++)
//        os << horiz;
//    os << down;
//    for (int i = 18; i < 119; i++)
//        os << horiz;
//    os << rigth_down;
//    os << '\n';
//    os << vert;
//    os << ts->key;
//    for (int i = ts->key.size(); i < 16; i++)
//        os << ' ';
//    os << vert;
//    for (int i = 0; i < ts->body.poly_string.size() && i < 101; i++)
//        os << ts->body.poly_string[i];
//    for (int i = 0; i < 101 - ts->body.poly_string.size(); i++)
//        os << ' ';
//    os << vert;
//    os << '\n';
//    os << left_up;
//    for (int i = 1; i < 17; i++)
//        os << horiz;
//    os << up;
//    for (int i = 18; i < 119; i++)
//        os << horiz;
//    os << rigth_up;
//    os << '\n';
//    return os;
//}