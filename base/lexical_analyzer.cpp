#include "lexical_analyzer.h"

void LexicalAnalyzer::del_garb()
{
    const char big[] = { 'A','B','C','D','E','F','G','H','I','J','K','L',
        'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
    const char small[] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
       'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };


    //const int n_op = 10;
    //const string op[n_op] = { "+", "-", "*", "/", "div","mod","fdiv", "while","if","else" };
    //const int n_keywords = 5;
    //const string keywords[n_keywords] = { "program","begin","end","var","const" };
    //const int n_logic_op = 8;
    //const string logic_op[n_logic_op] = { "and","or", ">","<",">=","<=","<>","=" };
    //const string symbols[] = { "+","-","*","/",";" };

    //const int n_smalls = 11;
    ////up to 4-th elem
    //const char smalls[n_smalls] = { '+','-','*','/',';','{','}',':',' ','_','.' };
    //const int n_letters = 26;
    //const char letters[n_letters] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
    //   'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };

    std::string p = "";

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

            // Big letters become small letters
            for (int i = 0; i < 26; i++) {
                if (*it == big[i]) {
                    *it = small[i];
                    goto next_cycle;
                }
            }
            //if this is an expression in WRITELN
            if (*it == '\'') {
                do {
                    it = str.erase(it);
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
                            ErrorParam ep(counter, progError::k_ENDLESS_ONE_LINE_COMMENT, true);
                            eh->push(ep);
                            break;
                        }
                    }
                }
                else
                    if (*it == '}') {
                        ErrorParam ep(counter, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true);
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
    const int n_keywords = 6;
    const string keywords[n_keywords] = { "program","begin","end","var","const", "end" };
    const int n_logic_op = 8;
    const string logic_op[n_logic_op] = { "and","or", ">","<",">=","<=","<>","=" };
    const string symbols[] = { "+","-","*","/",";" };

    const int n_smalls = 11;
    //up to 4-th elem
    const char smalls[n_smalls] = { '+','-','*','/',';',' ',':','_','.' };
    const int n_letters = 26;
    const char letters[n_letters] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
       'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
    /// <summary>
    /// Стратегия - каждую строку накопление до пробела слова. 
    /// Это слово анализируется на предмет совпадения с доступными
    /// Если анализ не дал результатов, посылаем ошибку непонятное ключевое слово
    /// </summary>
    string tmp = "";
    for (string str : plain_code) {
        for (char c : str) {
           for(int i=0;i<n_smalls;i++)
               if (smalls[i] == c) {
                   switch (c) {
                   case ' ': {
                       if (!tmp.empty()) {
                           //add token;
                       }
                   }
                   case ';': {

                       // create token of ;
                       // do not add it;
                   }
                   case '+':case '*':case '/': case '-': {
                       //create new token and add it;
                   }
                   }
//                   if (c == ' ') {
//                       break;
//                   }
//                   else
//                       if (i < 4) {
////                           creating token
//                       }
//                       e

               }
        }
    }
}

void LexicalAnalyzer::to_tokens()
{
    const int k_num_of_tokens = 37;
    //const string[k_num_of_tokens]={""}
    std::map<Token::LexemeSubType, string> examples; // examples of all lexemes
    std::string cur_line; // current line
    int line_counter = 1;
    while (*source_code) {
        std::getline(*source_code, cur_line, '\n');
        std::string word; // cuurent word
        char c = '\0';
        int i = 0;
        int gap_counter = 0;
        for (; i < cur_line.size() && cur_line[i] == ' '; i++) {
            gap_counter++;
        }
        if (gap_counter % Token::k_MIN_TAB) {
            ErrorParam ep(line_counter, progError::k_INCORRECT_TABULATION, true);
            eh->push(ep);
        }
        for (; i < cur_line.size(); i++) {
            switch (cur_line[i]) {
            case '{': {
                while (cur_line[i] != '}' && i < cur_line.size())
                    i++;
                if (i == cur_line.size()) {
                    ErrorParam ep(line_counter, progError::k_ENDLESS_ONE_LINE_COMMENT, true);
                    eh->push(ep);
                    break;
                }

            }
            case ' ': {
                while (cur_line[i] == ' ' && i < cur_line.size()) {
                    i++;
                }
            }
            case '+':case'*':case '/':case'-': case '(': case ')': {
                Token::LexemeType type;
                Token::LexemeSubType sub;
                if (cur_line[i] == '+' || cur_line[i] == '-') {
                    type = Token::LexemeType::ADDITION_OPERATOR;
                    if (cur_line[i] == '+') {
                        sub = Token::LexemeSubType::PLUS_OPERATOR;
                    }
                    else {
                        sub = Token::LexemeSubType::MINUS_OPERATOR;
                    }
                }
                else
                    if (cur_line[i] == '(' || cur_line[i] == ')') {
                        type = Token::LexemeType::BRACKET;
                        if (cur_line[i] == '(') {
                            sub = Token::LexemeSubType::LSBRACE;
                        }
                        else {
                            sub = Token::LexemeSubType::RSBRACE;
                        }
                    }
                    else {
                        type = Token::LexemeType::MULTYPLICATION_OPERATOR;
                        if (cur_line[i] == '*') {
                            sub = Token::LexemeSubType::MULTIPLY_OPERATOR;
                        }
                        else {
                            sub = Token::LexemeSubType::DIVIDE_OPERATOR;
                        }
                    }
                Token::StringCoord coord(line_counter, gap_counter);
                string tmp_str;
                tmp_str.push_back(cur_line[i]);
                tokens->push_back(Token(coord, type, sub, tmp_str));
            }
            default: {
                ////////////////////////////////////////////////////////////////////
            }
            }
        }
    }
    line_counter++;
}