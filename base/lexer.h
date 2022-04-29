#pragma once

#include <vector>
#include "token.h"
#include "error_handler.h"

class LexicalAnalyzer
{
    std::vector*<Token> tokens;
    ErrorHandler* eh;
    std::ifstream* source_code = nullptr;
    //deletes all garbage from program
    //garbage is comments and gaps
    void del_garb();

public:
    //runs del_garb then creates tokens;
    //can find errors in program;
    LexicalAnalyzer
    (
      std::vector*<Token> tokens,
      std::ifstream* source_code_,
      ErrorHandler* eh_
    ) : tokens(tokens_), eh(eh_), source_code(source_code_)
    {}

    //returns vector of tokens
    // std::vector<Token> get_tokens();

};
