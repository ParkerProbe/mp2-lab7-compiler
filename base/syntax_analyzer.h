#pragma once

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"

class SyntaxAnalyzer
{

private:
    TextLink<Token>* txt_link;
    ErrorHandler* err;
    HashTableList<SymbolTableRecInt>* symbol_table_int;
    HashTableList<SymbolTableRecDouble>* symbol_table_double;


public:
    SyntaxAnalyzer
    (
        TextLink<Token>* txt_link_,
        ErrorHandler* err_,
        HashTableList<SymbolTableRecInt>* sti,
        HashTableList<SymbolTableRecDouble>* std
    )
        : txt_link(txt_link_), err(err_),
        symbol_table_int(sti), symbol_table_double(std)
    {}

    void Start() {};
};