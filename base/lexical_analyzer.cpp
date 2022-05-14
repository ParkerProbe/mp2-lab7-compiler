#include "lexical_analyzer.h"

void LexicalAnalyzer::del_garb()
{
    const char big[] = { 'A','B','C','D','E','F','G','H','I','J','K','L',
        'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
    const char small[] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
       'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    std::string str;
    int counter = 1;
    while (*source_code)
    {
        std::getline(*source_code, str, '\n');
        int gap_counter = 0;
        std::string::iterator it1 = str.begin();
        for (; *it1 == ' ' && it1!=str.end(); ++it1) {
            gap_counter++;
        }
        if (it1 == str.end())
            continue;
        if (gap_counter % Token::k_MIN_TAB != 0) {
            ErrorParam ep(counter, progError::k_INCORRECT_TABULATION, true);
            eh->push(ep);
        }
        for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
            ////begining of strange thing

            //if (*it == ' ')
            //    it = str.erase(it);
            //
            //// end of strange thing

            //if this is an expression in WRITELN
            for (int i = 0; i < 26; i++) {
                if (*it == big[i]) {
                    *it = small[i];
                    goto next_cycle;
                }
            }
            if (*it == '\'') {
                do {                  
                    ++it;
                    if (it == str.end()) {
                        ErrorParam ep(counter, progError::k_UNEXPECTED_TERMINATION_OF_STRING, true);
                        eh->push(ep);
                        break;
                    }
                } while (*it != '\'');
            }
            else
                if (*it == '{') {
                    while (*it != '}')
                    {                      
                        it = str.erase(it);
                        if (it == str.end()) {
                            ErrorParam ep(counter, progError::k_ENDLESS_COMMENT, true);
                            eh->push(ep);
                            break;
                        }
                    }
                }
            next_cycle:
        }
        plain_code.push_back(str);
        counter++;
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