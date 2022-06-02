#pragma once

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"

class SemanticAnalyzer
{

private:
    TText<Token>* txt_link;
    ErrorHandler* err;

    HashTableList<SymbolTableRec<int>>* symbol_table_int;
    HashTableList<SymbolTableRec<double>>* symbol_table_double;



    void set_var_int(Token symbol, int num, bool is_set, bool is_const);
    void set_var_double(Token symbol, double num, bool is_set,  bool is_const);
    SymbolTableRec<int>* get_var_int(Token symbol);
    SymbolTableRec<double>* get_var_double(Token symbol);
    void set_var(Token var, Token value, bool is_set = true, bool is_const = false);
    int check_var(Token var);

public:
    SemanticAnalyzer
    (
        TText<Token>* txt_link_,
        HashTableList<SymbolTableRec<int>>* sti,
        HashTableList<SymbolTableRec<double>>* std,
        ErrorHandler* err_
    )
    : txt_link(txt_link_), symbol_table_int(sti),
    symbol_table_double(std), err(err_)
    {}

    void Start();
};
