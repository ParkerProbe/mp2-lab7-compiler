#pragma once

#include <string>
#include "stack.h"
#include "table.h"
#include "polynom.h"


using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	//operation stack
	Stack <string> sc;
	//operand stack
	Stack <Polynom> sd;
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

	int prior(string a);
	void set_infix(string t) { infix = t; }
	string get_infix() { return infix; }
	string get_postfix() { return postfix; }
	string to_postfix();
	// gets variables and calculates following postfix form
	Polynom calculate(Table** t);
};