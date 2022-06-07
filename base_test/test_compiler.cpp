#include <gtest.h>

#include "compiler_config.h"
#include "stack.h"
#include "interface.h"
#include "text_link.h"
#include "eq_exception.h"
#include "token.h"
#include "hash_table_list.h"
#include "symbol_table_rec.h"
#include "semantic_analyzer.h"
#include "lexical_analyzer.h"
#include "syntax_analyzer.h"
#include "code_runner.h"
#include "symbol_table_rec.h"



int StartCompiler(std::string path)
{
    std::ifstream* source_code = new std::ifstream(path);

    ErrorHandler* err = new ErrorHandler();
    TText<Token>* txt_link = new TText<Token>;
    vector<Token>* lexems = new vector<Token>;

    UnsortListTable<std::string, SymbolTableRec<int>>* symbol_table_int = new UnsortListTable<std::string, SymbolTableRec<int>>;
    UnsortListTable<std::string, SymbolTableRec<double>>* symbol_table_double = new UnsortListTable<std::string, SymbolTableRec<double>>;



    LexicalAnalyzer* lex_analyzer = new LexicalAnalyzer
    (
        source_code,
        lexems,
        err
    );
    lex_analyzer->create_tokens();

    if (err->condition() == 1) {
        source_code->close();
        return 1;
    }
    if (err->condition() == 2) {
        source_code->close();
        return 2;
    }

    SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
    {
        txt_link,
        lexems,
        err
    };
    syn_analyzer->Start();

    if (err->condition() == 1) {
        source_code->close();
        return 3;
    }
    if (err->condition() == 2) {
        source_code->close();
        return 4;
    }

    SemanticAnalyzer* sym_analyzer = new SemanticAnalyzer
    (
        txt_link,
        symbol_table_int,
        symbol_table_double,
        err
    );
    sym_analyzer->Start();

    if (err->condition() == 1) {
        source_code->close();
        return 5;
    }
    if (err->condition() == 2) {
        source_code->close();
        return 6;
    }
    
    source_code->close();
    return 0;
}



TEST(Compiler, var_no_defined)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_1.pas"), 4);
}

TEST(Compiler, no_semicolon_1)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_1.pas"), 4);
}

TEST(Compiler, no_semicolon_2)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_3.pas"), 4);
}

TEST(Compiler, conv_real_to_int)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_4.pas"), 6);
}

TEST(Compiler, no_type_dicl)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_5.pas"), 6);
}

TEST(Compiler, writeln_no_apostrophe)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_6.pas"), 6);
}

TEST(Compiler, writeln_wrong_use)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_7.pas"), 6);
}

TEST(Compiler, var_no_type)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_8.pas"), 6);
}

TEST(Compiler, var_no_init)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_9.pas"), 6);
}


TEST(Compiler, sqrt_from_negative)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_11.pas"), 6);
}

TEST(Compiler, if_begin_end_1)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_12.pas"), 4);
}

TEST(Compiler, if_begin_end_2)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_13.pas"), 4);
}


TEST(Compiler, real_comparison)
{
	EXPECT_EQ(StartCompiler("test_files\\test_file_1_15.pas"), 4);
}
