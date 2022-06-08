#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <new>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include<fstream>


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
    void print_cur_error(int cur_pos, std::string cur_line)
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
        std::cout << "LINE: \"" << cur_line << "\"" << '\n';
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
    ErrorHandler() :errors(0)
    {}


    //prints every cur error + head
    void print_errors(std::ifstream* source_code)
    {
        std::string cur_line;
        print_head();
        std::sort(errors.begin(), errors.end());
        source_code->clear();
        source_code->seekg(0);
        int j = 0;
        for (int i = 0; i < errors.size(); i++) {
            for (; j < errors[i].line_num; j++)
                std::getline(*source_code, cur_line, '\n');
            for (; i < errors.size()&&errors[i].line_num == j; i++) {
                print_cur_error(i, cur_line);
            }
        }
    }


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