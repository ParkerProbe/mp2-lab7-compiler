#pragma once

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"

class SemanticAnalyzer
{

private:
    TextLink<Token>* txt_link;
    ErrorHandler* err;
    HashTableList<SymbolTableRecInt>* symbol_table_int;
    HashTableList<SymbolTableRecDouble>* symbol_table_double;


public:
    SemanticAnalyzer
    (
        TextLink<Token>* txt_link_,
        HashTableList<SymbolTableRecInt>* sti,
        HashTableList<SymbolTableRecDouble>* std,
        ErrorHandler* err_
    )
    : txt_link(txt_link_), symbol_table_int(sti),
    symbol_table_double(std), err(err_)
    {}

    void Start();
};
