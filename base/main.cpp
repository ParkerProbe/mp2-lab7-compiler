#include <iostream>
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
#include "hash_table_list.h"
#include "symbol_table_rec.h"
#include "semantic_analyzer.h"
#include "lexical_analyzer.h"
#include "code_runner.h"
#include "syntax_analyzer.h"



#define COMPILER_VERSION 0.1

namespace Compiler_codes {
    
    enum return_codes
    {
        k_NO_ERROR,
        k_SOURCE_FILE_ERROR,
        k_MEMORY_ALLOC_ERROR,
        k_LEXICAL_ANALYSIS_ERROR,
        k_SYNTAX_ANALYSIS_ERROR,
        k_SYMANTIC_ANALYSIS_ERROR,
        k_CODE_RUN_ERROR,
        k_INTERNAL_ERROR
    };
}

void PrintOut(ErrorHandler* err)
{
    // Critical


}



int main(int argc, char* argv[])
{
    compiler_parameters compl_conf; 

    try {
        std::string path = ".\\.\\test_files\\test.pas";
        std::ifstream* source_code = nullptr;

        ErrorHandler* err = new ErrorHandler;
        Interface interface(err, &compl_conf, COMPILER_VERSION);

        TText<Token>* txt_link = new TText<Token>;
        vector<Token>* lexems = new vector<Token>;

        HashTableList<SymbolTableRec<int>>* symbol_table_int = nullptr;
        HashTableList<SymbolTableRec<double>>* symbol_table_double = nullptr;

        /*

            Argument Analysis

        */

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-p") == 0) {
                if (i + 1 < argc) {
                    source_code = new std::ifstream(argv[i + 1]);
                    interface.set_path(argv[i + 1]);
                }
                else {
                    interface.no_file_dialog();
                    return Compiler_codes::k_SOURCE_FILE_ERROR;
                }
            }
            if (strcmp(argv[i], "-l") == 0) {
                compl_conf.lexer_only = true;
            }
            if (strcmp(argv[i], "-s") == 0) {
                compl_conf.syntax_only = true;
            }
            if (strcmp(argv[i], "-v") == 0) {
                compl_conf.pr_version = true;
            }
            if (strcmp(argv[i], "--help") == 0) {
                compl_conf.pr_help = true;
            }
        }
        source_code = new std::ifstream(path);
        interface.set_path(path);
        if (source_code == nullptr) {
            compl_conf.pr_path_dlg = true;
            interface.print_file_dialog(source_code);
        }
        if (source_code->fail()) {
            interface.error_file_dialog();
            return Compiler_codes::k_SOURCE_FILE_ERROR;
        }

        LexicalAnalyzer* lex_analyzer = new LexicalAnalyzer
        (
            source_code,
            lexems,
            err
        );
        lex_analyzer->create_tokens();

        // Critical error in analyze
        if (err->condition() == 2) {
            interface.printer();
            source_code->close();
            return Compiler_codes::k_LEXICAL_ANALYSIS_ERROR;
        }
        // if (compl_conf.lexer_only) {}
        

         SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
         {
             txt_link,
             lexems,
             err
         };
         syn_analyzer->Start();

         // Critical error in analyze
         if (err->condition() == 2) {
             interface.printer();
             source_code->close();
             return Compiler_codes::k_SYNTAX_ANALYSIS_ERROR;
         }
        // if (compl_conf.syntax_only) {}


        SemanticAnalyzer* sym_analyzer = new SemanticAnalyzer
        (
            txt_link,
            symbol_table_int,
            symbol_table_double,
            err
        );
        sym_analyzer->Start();

        // Critical error in analyze
        if (err->condition() == 2) {
            interface.printer();
            source_code->close();
            return Compiler_codes::k_SYMANTIC_ANALYSIS_ERROR;
        }

         CodeRunner* runner = new CodeRunner
         (
             txt_link,
             symbol_table_int,
             symbol_table_double,
             err
         );
         runner->Start();

        source_code->close();

        if (err->condition() == 2) {
            return Compiler_codes::k_CODE_RUN_ERROR;
        }
        else {
            return 0;
        }

    }
    catch(std::bad_alloc& e) {
        return Compiler_codes::k_MEMORY_ALLOC_ERROR;
    }
    catch(EqException& internal_error) {
        return Compiler_codes::k_INTERNAL_ERROR;
    }


    return 0;
}
