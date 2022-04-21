#include <iostream>
#include "vector"
#include "string"
#include <fstream>
#include <sys/types.h>
#include "string.h"
#include "compiler_data.h"
#define COMPILER_VERSION 0.1





enum  return_codes
{
    k_NO_ERROR,
    k_SOURCE_FILE_ERROR,
    k_MEMORY_ALLOC_ERROR,
    k_LEXICAL_ANALYSIS_ERROR,
    k_SYNTAX_ANALYSIS_ERROR,
    k_INTERPRETATION_ERROR,
};





int main(int argc, char* argv[])
{
    /*        
    
        Compiler parameters
    
    */
    compiler_parameters conf; 

    std::ifstream* source_code = nullptr;
    if (!source_code) {
        return k_MEMORY_ALLOC_ERROR;
    }

    // ErrorHandler* err = new ErrorHandler;
    // if (!err) {
    //     return k_MEMORY_ALLOC_ERROR;
    // }
    
    // TextLinker* txt_link = new TextLinker;

    // Argument analysis

    source_code = new std::ifstream(argv[1]);
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i] , "-l") == 0) {
           conf.lexer_only = true; 
        }
        if (strcmp(argv[i] , "-s") == 0) {
           conf.syntax_only = true; 
        }
        if (strcmp(argv[i] , "-g") == 0) {
           conf.gen_only = true; 
        }
        if (strcmp(argv[i] , "-v") == 0) {
            conf.pr_version = true;
        }
        if (strcmp(argv[i] , "--help") == 0) {
            conf.pr_help = true;
        }
        
    }
    if (source_code == nullptr) {
        return k_NO_ERROR;
    }
    else if(source_code->fail()) {
        // PRINT FATAL ERROR
        return k_SOURCE_FILE_ERROR;
    }

    /* 
        Start Lexical Analysis 

    */
    // LexicalAnalyzer* lex_analyzer = new LexicalAnalyzer
    // (
    //     source_code,
    //     err,
    //     lexer_only
    // );
    // Token* token = nullptr;
    // Error Work
    // if (!lex_analyzer) {
    //     return k_MEMORY_ALLOC_ERROR;
    // }

    // if(lexer_only) {}

    // 
             
    /* 
        Start Syntax Analysis 

    */
    // SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
    // (
    //     lex_analyzer,
    //     txt_link,
    //     err,
    //     syntax_only
    // );
    // // Error Work
    // if (!syn_analyzer) {
    //     return k_MEMORY_ALLOC_ERROR;
    // }
    //

    // if(syntax_only) {}



    /* 
        Start Interpretation

    */
    // Interpretator* intpr = new Interpretator
    // (
    //     txt_link,
    //     err,
    //     gen_only
    // );
    // // Error Work
    // if (!intpr) {
    //     return k_MEMORY_ALLOC_ERROR;
    // }
    //

    source_code->close();


    return 0;
}