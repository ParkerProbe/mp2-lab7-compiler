#include "postfix.h"
#include "stack.h"
#include <iostream>
#include "token.h"

int TPostfix::prior(Token::LexemeSubType a)
{
	if (a == Token::LexemeSubType::MULTIPLY_OPERATOR || a == Token::LexemeSubType::DIVIDE_OPERATOR || a == Token::LexemeSubType::DIV_OPERATOR || a == Token::LexemeSubType::MOD_OPERATOR )
		return 3;
	if (a == Token::LexemeSubType::PLUS_OPERATOR || a == Token::LexemeSubType::MINUS_OPERATOR)
		return 2;
	if (a == Token::LexemeSubType::LSBRACE || a == Token::LexemeSubType::RSBRACE)
		return 1;
	if (a == Token::LexemeSubType::EQUALS_RELATION_OPERATOR || a == Token::LexemeSubType::NOT_EQUALS_RELATIONAL_OPERATOR || a == Token::LexemeSubType::LESS_RELATIONAL_OPERATOR || a == Token::LexemeSubType::LESS_OR_EQUALS_RELATIONAL_OPERATOR || a == Token::LexemeSubType::GREATER_RELATIONAL_OPERATOR || a == Token::LexemeSubType::GREATER_OR_EQUALS_RELATIONAL_OPERATOR)
		return -1;
	return 0;
}

std::vector<Token>  TPostfix::to_postfix()
{
	Token::LexemeSubType tmp;
	sc.set_size(infix.size());
	sd.set_size(infix.size());
	std::vector<Token>::iterator iter = (infix).begin();
	while (iter != (infix).end())
	{
		tmp = (*iter).s_type();
		if (prior(tmp) == 0)
		{
			postfix.push_back((*iter));
				continue;
		}
		if ((prior(tmp) == 2) || (prior(tmp) == 3) || (prior(tmp) == -1))
		{
			if (sc.is_empty() == true)
				sc.add(*iter);
			else
			{
				if (prior(tmp) > prior(sc.info_top().s_type()))
				{
					sc.add(*iter);
				}
				else
				{
					while (prior(tmp) <= prior(sc.info_top().s_type()))
					{
						postfix.push_back(sc.get_top());
						if (sc.is_empty() == true)
							break;
					}
					sc.add(*iter);
				}
			}
		}
		if (prior(tmp) == 1)
		{
			if (tmp == Token::LexemeSubType::LSBRACE)
				sc.add(*iter);
			else
				if (tmp == Token::LexemeSubType::RSBRACE)
				{
					while (sc.info_top().s_type() != Token::LexemeSubType::LSBRACE)
					{
						postfix.push_back(sc.get_top());
					}
					sc.get_top();
				}
		}
		iter++;
	}
	while (sc.is_empty() != true)
		postfix.push_back(sc.get_top());
	return postfix;
}

double TPostfix::calculate(HashTableList<SymbolTableRecInt>* table_int, HashTableList<SymbolTableRecDouble>* table_double)
{
	double a, b;
	int whole1, whole2;
	int fractional1, fractional2;
	int precision = 4;
	double k;
	std::vector<Token>::iterator iter = (postfix).begin();
	while (iter != (postfix).end())
	{
		if ((*iter).s_type() == Token::LexemeSubType::PLUS_OPERATOR)
		{
			a = sd.get_top(); b = sd.get_top();
			sd.add(a + b);
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::MINUS_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() == true)
					sd.add(a *= -1);
			else
			{
				b = sd.get_top();
				sd.add(b - a);
			}
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::MULTIPLY_OPERATOR)
		{
			a = sd.get_top(); b = sd.get_top();
			sd.add(a * b);
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::DIV_OPERATOR)
		{
			a = sd.get_top(); b = sd.get_top();
			whole1 = (int)a;
			whole2 = (int)b;
			fractional1 = (int)((a - (double)whole1) * pow(10, precision));
			fractional2 = (int)((b - (double)whole2) * pow(10, precision));
			if (fractional1 == 0 && fractional2 == 0 && (whole2%whole1==0))
			sd.add(double(whole2 / whole1));
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::MOD_OPERATOR)
		{
			a = sd.get_top(); b = sd.get_top();
			whole1 = (int)a;
			whole2 = (int)b;
			fractional1 = (int)((a - (double)whole1) * pow(10, precision));
			fractional2 = (int)((b - (double)whole2) * pow(10, precision));
			if (fractional1==0 && fractional2 == 0)
			sd.add(double((int)b % (int)a));
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::DIVIDE_OPERATOR)
		{
			a = sd.get_top(); b = sd.get_top();
			sd.add(b / a);
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::EQUALS_RELATION_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && a == b)
				return 1;
			return 0;
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::NOT_EQUALS_RELATIONAL_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && a != b)
				return 1;
			return 0;
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::LESS_RELATIONAL_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && b < a)
				return 1;
			return 0;
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::LESS_OR_EQUALS_RELATIONAL_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && b <= a)
				return 1;
			return 0;
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::GREATER_RELATIONAL_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && b > a)
				return 1;
			return 0;
			continue;
		}
		if ((*iter).s_type() == Token::LexemeSubType::GREATER_OR_EQUALS_RELATIONAL_OPERATOR)
		{
			a = sd.get_top();
			if (sd.is_empty() != true)
				b = sd.get_top();
			if (sd.is_empty() == true && b >= a)
				return 1;
			return 0;
			continue;
		}
		else
		{
			if ((*table_int).find((*iter).get_text()) != nullptr)
			{
				a = (*table_int).find((*iter).get_text())->data->num;
				sd.add((double)a);
				continue;
			}
			if ((*table_double).find((*iter).get_text()) != nullptr)
			{
				a = (*table_double).find((*iter).get_text())->data->num;
				sd.add((double)a);
				continue;
			}
			if ((*iter).s_type() == Token::LexemeSubType::INTEGER_LITERAL || (*iter).s_type() == Token::LexemeSubType::DOUBLE_LITERAL)
			{
				a = atof((*iter).get_text().c_str());
				sd.add((double)a);
			}
		}
	}
	a = sd.get_top();
	if (sd.is_empty() != true)
	{
		throw 0;
	}
	return a;
}







