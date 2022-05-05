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


void StartCompiler(std::string path)
{
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

	SyntaxAnalyzer* syn_analyzer = new SyntaxAnalyzer
	(
		&txt_link,
		&lexems,
		&err
	);
	SemanticAnalyzer* sym_analyzer = new SemanticAnalyzer
	(
		&txt_link,
		&symbol_table_int,
		&symbol_table_double,
		&err
	);
	source_code->close();
}


TEST(Compiler, test_file_1)
{
	ASSERT_NO_THROW(StartCompiler("test_files/test1.pas"));
}