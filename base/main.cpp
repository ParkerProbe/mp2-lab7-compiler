#include <iostream>
#include "vector"
#include "string"
#include <fstream>
#include <new>
#include <sys/types.h>
#include "string.h"
#include "compiler_config.h"
#include "interface.h"


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
    compiler_parameters compl_conf; 

    try {
        
        std::ifstream* source_code = nullptr;
        
        Interface interface;
        // ErrorHandler* err = new ErrorHandler;
        
        // TextLinker* txt_link = new TextLinker;

        /* 
        
            Argument Analysis 
        
        */ 

        source_code = new std::ifstream(argv[1]);
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i] , "-l") == 0) {
                compl_conf.lexer_only = true; 
            }
            if (strcmp(argv[i] , "-s") == 0) {
                compl_conf.syntax_only = true; 
            }
            if (strcmp(argv[i] , "-g") == 0) {
                compl_conf.gen_only = true; 
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
        // if(lexer_only) {}

                
        /* 
            
            Start Syntax Analysis 

        */

        // SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
        // (
        //     txt_link,
        //     err,
        //     syntax_only
        // );

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

        source_code->close();
    }
    catch(std::bad_alloc& e) {
        return k_MEMORY_ALLOC_ERROR;
    }


    return 0;
}
