#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "error_param.h"

class ErrorHandler
{
private:
    //static const int k_ERROR_HANDLER_MAX = 16;
    std::vector<ErrorParam> errors;
    const std::string comment[16] = {
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


    void print_head() 
    {
        std::cout << " CODE ";
        std::cout << " LINE ";
        std::cout << " ERROR MESSAGE\n";
    }
    void print_cur_error(int cur_pos)
    {
        std::cout << ' ';
        std::cout << errors[cur_pos].error_num;
        int gap_counter = 6;// string "CODE "
        gap_counter -= get_symbol_quan(errors[cur_pos].error_num);
        for (; gap_counter > 0; gap_counter--) {
            std::cout << ' ';
        }
        std::cout << errors[cur_pos].line_num;
        gap_counter = 6;// string "LINE "
        gap_counter -= get_symbol_quan(errors[cur_pos].line_num);
        for (; gap_counter > 0; gap_counter--) {
            std::cout << ' ';
        }
        if (errors[cur_pos].is_critical) {
            std::cout << "ERROR: ";
        }
        else {
            std::cout << "WARNING: ";
        }
        std::cout << comment[errors[cur_pos].error_num] << '\n';
    }
    int get_symbol_quan(int cur_pos) 
    {
        int quan = 0;
        while (cur_pos > 0) {
            cur_pos /= 10;
            quan++;
        }
        return quan;
    }

public:
    //prints every cur error + head
    void print_errors()
    {
        print_head();
        std::sort(errors.begin(), errors.end());
        /// <summary>
        /// /////////////////////////////////////////////////
        /// </summary>
        for (int i = 0; i < errors.size(); i++) {
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
    
    bool comp(ErrorParam a, ErrorParam b)
    {
        return a.line_num > b.line_num;
    }
};