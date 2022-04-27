#pragma once
#include <vector>
#include "token.h"
#include "error_handler.h"
//May be LexicalAnalyzer
class Lexer
{
    std::vector<Token> tokens;
    ErrorHandler* eh;
    //deletes all garbage from program
    //garbage is comments and gaps
    void del_garb();

public:
    //runs del_garb then creates tokens;
    //can find errors in program;
    Lexer(std::vector<std::string> prog, ErrorHandler* _eh);
    //returns vector of tokens
    std::vector<Token> get_tokens();

};