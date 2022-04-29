#pragma once

#include "text_link.h"
#include "token.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"
#include "postfix.h"
#include "stack.h"
#include <string>

class SemanticAnalyzer
{

private:
    TextLink<Token>* txt_link;
    HashTableList<SymbolTableRecInt>* symbol_table_int;
    HashTableList<SymbolTableRecDouble>* symbol_table_double;
    TPostfix op();
    TStack <string> tp;

public:
    SemanticAnalyzer
    (
        TextLink<Token>* txt_link_,
        HashTableList<SymbolTableRecInt>* sti,
        HashTableList<SymbolTableRecDouble>* std
    )
        : txt_link(txt_link_),
        symbol_table_int(sti), symbol_table_double(std)
    {}

    void Start();
};
