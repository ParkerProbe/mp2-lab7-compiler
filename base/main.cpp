#include <iostream>
#include "semantic_analyzer.h"
#include "vector"
#include "string"
#include <fstream>
#include <new>
#include <sys/types.h>
#include "string.h"



#include "compiler_config.h"
#include "interface.h"
#include "text_link.h"
#include "eq_exception.h"
#include "token.h"
#include "lexer.h"
#include "hash_table_list.h"
#include "symbol_table_rec.h"



#define COMPILER_VERSION 0.1

namespace Compiler_codes {
    
    enum return_codes
    {
        k_NO_ERROR,
        k_SOURCE_FILE_ERROR,
        k_MEMORY_ALLOC_ERROR,
        k_LEXICAL_ANALYSIS_ERROR,
        k_SYNTAX_ANALYSIS_ERROR,
        k_INTERPRETATION_ERROR,
        k_INTERNAL_ERROR
    };
}

int main(int argc, char* argv[])
{
    compiler_parameters compl_conf; 

    try {
        
        std::ifstream* source_code = nullptr;
        
        ErrorHandler* err = new ErrorHandler;
        Interface interface(err, &compl_conf, COMPILER_VERSION);

        TextLink<Token>* txt_link = new TextLink<Token>;
        
        HashTableList<SymbolTableRecInt>* symbol_table_int;
        HashTableList<SymbolTableRecDouble>* symbol_table_double;
        



        /* 
        
            Argument Analysis 
        
        */ 

        source_code = new std::ifstream(argv[1]);
        interface.set_path(argv[1]);

        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i] , "-l") == 0) {
                compl_conf.lexer_only = true; 
            }
            if (strcmp(argv[i] , "-s") == 0) {
                compl_conf.syntax_only = true; 
            }
            if (strcmp(argv[i] , "-v") == 0) {
                compl_conf.pr_version = true;
            }
            if (strcmp(argv[i] , "--help") == 0) {
                compl_conf.pr_help = true;
            }
            
        }

        if (source_code == nullptr) {
            compl_conf.pr_path_dlg = true;
            interface.print_file_dialog(source_code);
        }
        
        if (source_code->fail()) {
            interface.error_file_dialog();
            return Compiler_codes::k_SOURCE_FILE_ERROR;
        }


        // LexicalAnalyzer* lex_analyzer = new LexicalAnalyzer
        // (
        //     source_code,
        //     err,
        // );
        // if(lexer_only) {}

        // SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
        // (
        //     txt_link,
        //     err,
        // );

        // if(syntax_only) {}

        SemanticAnalyzer* sym_analyzer = new SemanticAnalyzer
        (
            txt_link,
            symbol_table_int,
            symbol_table_double,
            err
        );

        // Interpretator* intpr = new Interpretator
        // (
        //     txt_link,
        //     err,
        // );

        source_code->close();
    }
    catch(std::bad_alloc& e) {
        return Compiler_codes::k_MEMORY_ALLOC_ERROR;
    }
    catch(EqException& internal_error) {
        return Compiler_codes::k_INTERNAL_ERROR;
    }


    return 0;
}