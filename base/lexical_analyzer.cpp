#include "lexical_analyzer.h"

void LexicalAnalyzer::del_garb()
{
    const char big[] = { 'A','B','C','D','E','F','G','H','I','J','K','L',
        'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
    std::string str;
    while (*source_code)
    {
        std::getline(*source_code, str, '\n');
        for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
            if (*it == ' ')
                it = str.erase(it);
            else
                if (*it == '\'') {
                    //if this is an expression in WRITELN
                }
                else
                    if (*it == '{' || *it == '}') {
                        //delete commets
                    }
        }
    }
}
void LexicalAnalyzer::create_tokens()
{
    //std::vector<string> plain_code;
  //  const char ch_op[] = { '+','-','*','/' };
    const int n_op = 10;
    const string op[n_op] = { "+", "-", "*", "/", "div","mod","fdiv", "while","if","else" };
    const int n_keywords = 5;
    const string keywords[n_keywords] = { "program","begin","end","var","const" };
    const int n_logic_op = 8;
    const string logic_op[n_logic_op] = { "and","or", ">","<",">=","<=","<>","=" };
    const string symbols[] = { "+","-","*","/",";" };

    const int n_smalls = 11;
    //up to 4-th elem
    const char smalls[n_smalls] = { '+','-','*','/',';','{','}',':',' ','_','.' };
    const int n_letters = 26;
    const char letters[n_letters] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
       'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    for (string str : plain_code) {
        for (char c : str) {
           for(int i=0;i<n_smalls;i++)
               if (smalls[i] == c) {
                   if (c == ' ') {
                       break;
                   }
                   else
                       if (i < 4) {
//                           tokens->push_back(symbols[i]);
                       }

               }
        }
    }
}