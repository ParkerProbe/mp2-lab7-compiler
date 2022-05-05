#pragma once
#include <vector>

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"

class SyntaxAnalyzer
{

private:
    TText<Token>* txt_link;
    ErrorHandler* err;
    std::vector<Token>* tokens;
public:
    SyntaxAnalyzer
    (
        TText<Token>* txt_link_,
        std::vector<Token>* tokens_,
        ErrorHandler* err_
    )
        : txt_link(txt_link_), tokens(tokens_), err(err_)
    {}

    void Start() {};
};