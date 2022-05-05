#pragma once

#include "text_link.h"
#include "token.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"
#include "postfix.h"
#include "stack.h"
#include <string>

class CodeRunner
{

private:
    TText<Token>* txt_link;
    HashTableList<SymbolTableRecInt>* symbol_table_int;
    HashTableList<SymbolTableRecDouble>* symbol_table_double;
    TPostfix op();
    Stack <string> tp;
    ErrorHandler* err;

public:
    CodeRunner
    (
        TText<Token>* txt_link_,
        HashTableList<SymbolTableRecInt>* sti,
        HashTableList<SymbolTableRecDouble>* std,
        ErrorHandler* err_
    )
        : txt_link(txt_link_),
        symbol_table_int(sti), symbol_table_double(std), err(err_)
    {}

    void Start();
};
