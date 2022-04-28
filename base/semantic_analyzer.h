#pragma once

#include "text_link.h"
#include "token.h"
#include "error_handler.h"

class SemanticAnalyzer
{

private:
    TextLink<Token>* txt_link;
    ErrorHandler* err;


public:
    SemanticAnalyzer
    (
        TextLink<Token>* txt_link_,
        ErrorHandler* err_
    ) : txt_link(txt_link_), err(err_)
    {}

    void Start();
};