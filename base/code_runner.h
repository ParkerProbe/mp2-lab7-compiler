#pragma once


#include <string>


#include "text_link.h"
#include "token.h"
#include "symbol_table_rec.h"
#include "postfix.h"
#include "stack.h"
#include "error_handler.h"
#include "unsort_list_table.h"

class CodeRunner
{

private:
    TText<Token>* txt_link;
    UnsortListTable<std::string, SymbolTableRec<int>>* symbol_table_int;
    UnsortListTable<std::string, SymbolTableRec<double>>* symbol_table_double;
    TPostfix op;
    ErrorHandler* err;

    SymbolTableRec<int>* get_var_int(Token symbol);
    SymbolTableRec<double>* get_var_double(Token symbol);
    void set_var_int(Token symbol, int num, bool is_set, bool is_const);
    void set_var_double(Token symbol, double num, bool is_set, bool is_const);
    void set_var(Token var, double value, bool is_set = true, bool is_const = false);
    void get_var(Token var, SymbolTableRec<int>* var_int, SymbolTableRec<double>* var_double);

    bool is_operation(Token symbol);

    // For finded var
    SymbolTableRec<int>* var_int;
    SymbolTableRec<double>* var_double;


public:
    CodeRunner
    (
        TText<Token>* txt_link_,
        UnsortListTable<std::string, SymbolTableRec<int>>* sti,
        UnsortListTable<std::string, SymbolTableRec<double>>* std,
        ErrorHandler* err_
    )
        : txt_link(txt_link_), symbol_table_int(sti), symbol_table_double(std), op(), err(err_), var_int(), var_double()
    {}

    void Start();
};
