#pragma once

#include <vector>
#include "token.h"
#include "error_handler.h"
#include <string>
#include <iostream>
#include "token.h"

//TO DO: FILL IN CASES OF DEL_GARB AND FILL CREATE_TOKENS

class LexicalAnalyzer
{
    std::vector<Token>* tokens;
    ErrorHandler* eh;
    std::ifstream* source_code = nullptr;
    std::vector<string> plain_code;//code for making tokens
    //deletes all garbage from program
    //garbage is comments and gaps, changes all letters to the same register
    void del_garb();
    void create_tokens();

public:
    //runs del_garb then creates tokens;
    //can find errors in program;
    LexicalAnalyzer
    (
      std::ifstream* source_code_,
      std::vector<Token>* tokens_,
      ErrorHandler* eh_
    ) : tokens(tokens_), source_code(source_code_), eh(eh_)
    {}
    //returns vector of tokens
    // std::vector<Token> get_tokens();

};
