#pragma once

#include <string>
#include "stack.h"
#include "table.h"
#include "token.h"
#include "list.h"
#include "symbol_table_rec.h"
#include "unsort_list_table.h"
using namespace std;

class TPostfix
{
	std::vector<Token> infix;
	std::vector<Token> postfix;
	//operation stack
	Stack <Token> sc;
	//operand stack
	Stack <double> sd;
	//to store the values of variables
	double* p;
public:
	TPostfix()
	{
		p = new double[10];
	}
	~TPostfix()
	{
		delete[] p;
	}

	// Changed in accordance with the coding rules

	int prior(Token::LexemeSubType a);
	void set_infix(std::vector<Token> t) { infix = t; }
	std::vector<Token> get_infix() { return infix; }
	std::vector<Token> get_postfix() { return postfix; }
	std::vector<Token> to_postfix();
	double calculate(UnsortListTable<std::string, SymbolTableRec<int>>* symbol_table_int, UnsortListTable<std::string, SymbolTableRec<double>>* symbol_table_double);
};