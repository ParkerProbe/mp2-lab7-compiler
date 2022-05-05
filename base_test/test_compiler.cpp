#include "stack.h"

#include <gtest.h>

#include "compiler_config.h"
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


int StartCompiler(std::string path)
{
	// 1 - Warning
	// 2 - Critical

	std::ifstream* source_code = nullptr;
	ErrorHandler err;
	TText<Token> txt_link;
	vector<Token> lexems;
	HashTableList<SymbolTableRecInt> symbol_table_int;
	HashTableList<SymbolTableRecDouble> symbol_table_double;

	source_code = new std::ifstream(path);

	LexicalAnalyzer* lex_analyzer = new LexicalAnalyzer
	(
		source_code,
		&lexems,
		&err
	);
	if (err.condition() == 1) {
		source_code->close();
		return 1;
	}
	if (err.condition() == 2) {
		source_code->close();
		return 2;
	}

	SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
	(
		&txt_link,
		&lexems,
		&err
	);
	if (err.condition() == 1) {
		source_code->close();
		return 3;
	}
	if (err.condition() == 2) {
		source_code->close();
		return 4;
	}

	SemanticAnalyzer* sym_analyzer = new SemanticAnalyzer
	(
		&txt_link,
		&symbol_table_int,
		&symbol_table_double,
		&err
	);
	if (err.condition() == 1) {
		source_code->close();
		return 5;
	}
	if (err.condition() == 2) {
		source_code->close();
		return 6;
	}

	source_code->close();
	return 0;
}


TEST(Compiler, test_file_1)
{
	EXPECT_EQ(StartCompiler("test_files/test1.pas"), 0);
}