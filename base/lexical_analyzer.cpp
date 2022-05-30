#include "lexical_analyzer.h"

//void LexicalAnalyzer::del_garb()
//{
//    const char big[] = { 'A','B','C','D','E','F','G','H','I','J','K','L',
//        'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
//    const char small[] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
//       'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
//
//
//    //const int n_op = 10;
//    //const string op[n_op] = { "+", "-", "*", "/", "div","mod","fdiv", "while","if","else" };
//    //const int n_keywords = 5;
//    //const string keywords[n_keywords] = { "program","begin","end","var","const" };
//    //const int n_logic_op = 8;
//    //const string logic_op[n_logic_op] = { "and","or", ">","<",">=","<=","<>","=" };
//    //const string symbols[] = { "+","-","*","/",";" };
//
//    //const int n_smalls = 11;
//    ////up to 4-th elem
//    //const char smalls[n_smalls] = { '+','-','*','/',';','{','}',':',' ','_','.' };
//    //const int n_letters = 26;
//    //const char letters[n_letters] = { 'a','b','c','d','e','f','g','h','i','j','k','l',
//    //   'm','n','o','p','q','r','s','t','u','v','w','x','y','z' };
//
//    std::string p = "";
//
//    std::string str;
//    int counter = 1;
//    while (*source_code)
//    {
//        std::getline(*source_code, str, '\n');
//        int gap_counter = 0;
//        std::string::iterator it1 = str.begin();
//        for (; *it1 == ' ' && it1!=str.end(); ++it1) {
//            gap_counter++;
//        }
//        if (it1 == str.end())
//            continue;
//        if (gap_counter % Token::k_MIN_TAB != 0) {
//            ErrorParam ep(counter, progError::k_INCORRECT_TABULATION, true);
//            eh->push(ep);
//        }
//        for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
//            ////begining of strange thing
//
//            //if (*it == ' ')
//            //    it = str.erase(it);
//            //
//            //// end of strange thing
//
//            // Big letters become small letters
//            for (int i = 0; i < 26; i++) {
//                if (*it == big[i]) {
//                    *it = small[i];
//                    goto next_cycle;
//                }
//            }
//            //if this is an expression in WRITELN
//            if (*it == '\'') {
//                do {
//                    it = str.erase(it);
//                    if (it == str.end()) {
//                        ErrorParam ep(counter, progError::k_UNEXPECTED_TERMINATION_OF_STRING, true);
//                        eh->push(ep);
//                        break;
//                    }
//                } while (*it != '\'');
//            }
//            else
//                if (*it == '{') {
//                    while (*it != '}')
//                    {
//                        it = str.erase(it);
//                        if (it == str.end()) {
//                            ErrorParam ep(counter, progError::k_ENDLESS_ONE_LINE_COMMENT, true);
//                            eh->push(ep);
//                            break;
//                        }
//                    }
//                }
//                else
//                    if (*it == '}') {
//                        ErrorParam ep(counter, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true);
//                    }
//            next_cycle:
//        }
//        plain_code.push_back(str);
//        counter++;
//    }
//}

void LexicalAnalyzer::create_tokens()
{
    const int k_num_of_tokens = 32;// name of program can be everything, but...

    //    PROGRAM_KEY_VALUE /* program */, SEMICOLON /* ; */,
    //    BEGIN_KEYWORD /* begin */, END_KEYWORD /* end */,
    //    IF_HEADING /* if */, THEN_KEYWORD /* then */, ELSE_KEYWORD /* else */,
    //    LSBRACE /* ( */, RSBRACE /* ) */, //LBRACE/* { */, RBRACE /* } */,
    //    PLUS_OPERATOR, MINUS_OPERATOR, MULTIPLY_OPERATOR, DIVIDE_OPERATOR,
    //    DIV_OPERATOR, MOD_OPERATOR, COMMA /* , */, ASSIGN_OPERATOR /*:=*/,
    //    AND_OPERATOR, OR_OPERATOR, EQUALS_RELATION_OPERATOR /* = */,
    //    NOT_EQUALS_RELATIONAL_OPERATOR /* <> */, LESS_RELATIONAL_OPERATOR,
    //    LESS_OR_EQUALS_RELATIONAL_OPERATOR, GREATER_RELATIONAL_OPERATOR,
    //    GREATER_OR_EQUALS_RELATIONAL_OPERATOR /* >= */, COLON /* : */,
    //    CONST_DEFINITION_KEYWORD /* const */, VAR_DEFINITION_KEYWORD /* var */,
    //    READ_FUNC /* read */, WRITE_FUNC /* write */, INTEGER_TYPE /*integer*/,
    //    DOUBLE_TYPE /* double */,

    const string values[k_num_of_tokens] = { "program", ";","begin","end","if",
        "then", "else","(",")","+","-","*","/", "div", "mod", ",", ":=",
        /*not necessary*/ "and","or" /*end of not necessary*/,"=","<>", "<",
        "<=", ">",">=",":","const", "var", "read", "write", "integer", "double" };
   // std::map<string, std::pair<Token::LexemeType, Token::LexemeSubType>> ex;
    std::map<string, Token::LexemeSubType> examples; // examples of all lexemes
    for (int i = 0; i < k_num_of_tokens; i++) {
        examples.insert(std::pair<string, Token::LexemeSubType>(values[i], static_cast<Token::LexemeSubType>(i)));
    }
    std::map<string, Token::LexemeSubType>::iterator it;// to create most of tokens

    std::string cur_line; // current line
    int line_counter = 1;
    std::string word; // curent word
    int i = 0;
    int gap_counter = 0;
    Token::LexemeSubType sub; // subtype of token
    //Token::LexemeType type; // type of token
    Token::StringCoord coord; // coords of line
    std::getline(*source_code, cur_line, '\n');
    for (; i < cur_line.size() && cur_line[i] == ' '; i++) {
        ;
    }
    if (i > 0) {
        if (i % Token::k_MIN_TAB)
            eh->push(line_counter, progError::k_INCORRECT_NESTING_LEVEL, true);
        else {
            eh->push(line_counter, progError::k_INCORRECT_TABULATION, true);
        }
    }
    int word_counter = 0;
    // only just to create tokens with program key word and name of program
    // and to create errors then they don't exist
    for (; i < cur_line.size(); i++) {
        if (cur_line[i] >= 'A' && cur_line[i] <= 'z')
            word.push_back(tolower(cur_line[i]));
        if (cur_line[i] == ' ')
        {
            if (!word.empty()) {
                coord.set(line_counter, gap_counter);
                if (word_counter) {
                    sub = Token::LexemeSubType::PROGRAM_NAME;
      //              type = Token::LexemeType::USER_TYPE;
            //        tokens->push_back(Token(coord, type, sub, word));
                    tokens->push_back(Token(coord, sub, word));
                }
                else {
                    if (word == string("program")) {
                        sub = Token::LexemeSubType::PROGRAM_HEADING;
        //                type = Token::LexemeType::DECLARATION_KEYWORD;
          //              tokens->push_back(Token(coord, type, sub, word));
                        tokens->push_back(Token(coord, sub, word));
                    }
                    else {
                        eh->push(line_counter, progError::k_NO_PROGRAM_KEY_WORD, true);
                    }
                }
                word.clear();
            }
        }
        else
            if (cur_line[i] == ';')
                if (!word.empty()) {
                    coord.set(line_counter, gap_counter);
                    if (word_counter) {
                        sub = Token::LexemeSubType::PROGRAM_NAME;
                       /* type = Token::LexemeType::DECLARATION_KEYWORD;
                        tokens->push_back(Token(coord, type, sub, word));*/
                        tokens->push_back(Token(coord, sub, word));
                    }
                    else {
                        if (word == string("program")) {
                            sub = Token::LexemeSubType::PROGRAM_HEADING;
                           /* type = Token::LexemeType::DECLARATION_KEYWORD;
                            tokens->push_back(Token(coord, type, sub, word));*/
                            tokens->push_back(Token(coord, sub, word));
                        }
                        else {
                            eh->push(line_counter, progError::k_NO_PROGRAM_KEY_WORD, true);
                        }
                    }
                    break;
                }
    }
    if (word_counter < 2)
        eh->push(line_counter, progError::k_NO_PROGRAM_NAME, true);
    while (*source_code) {
        std::getline(*source_code, cur_line, '\n');
        word.clear();
        gap_counter = 0;
        for (i = 0; i < cur_line.size() && cur_line[i] == ' '; i++) {
            gap_counter++;
        }
        coord.set(line_counter, gap_counter);
        if (gap_counter % Token::k_MIN_TAB) {
            eh->push(line_counter, progError::k_INCORRECT_TABULATION, true);
        }
        for (; i < cur_line.size(); i++) {
            switch (cur_line[i]) {
            case ';': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(line_counter, sub, word));
                    word.clear();
                }
                sub = Token::LexemeSubType::SEMICOLON;
                tokens->push_back(Token(line_counter, sub, string(";")));
                goto next_line;
            }
            case ' ': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(line_counter, sub, word));
                    word.clear();
                }
                while (cur_line[i] == ' ' && i < cur_line.size()) {
                    i++;
                }
                //it's not lexer's buisness. It is responsibility of syntaxer
                /*if (i == cur_line.size()) {
                    
                }*/
                break;
            }
            case '{': {
                while (cur_line[i] != '}' && i < cur_line.size())
                    i++;
                if (i == cur_line.size()) {
                    eh->push(line_counter, progError::k_ENDLESS_ONE_LINE_COMMENT, true);
                }
                break;
            }
            case '+':case'*':case '/':case'-': case '(': case ')': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                        tokens->push_back(Token(line_counter, sub, word));
                        word.clear();
                    }
                    else {
                        sub = it->second;
                    }
                }
                if (cur_line[i] == '+' || cur_line[i] == '-') {
                    if (cur_line[i] == '+') {
                        sub = Token::LexemeSubType::PLUS_OPERATOR;
                    }
                    else {
                        sub = Token::LexemeSubType::MINUS_OPERATOR;
                    }
                }
                else
                    if (cur_line[i] == '(' || cur_line[i] == ')') {
                        if (cur_line[i] == '(') {
                            sub = Token::LexemeSubType::LSBRACE;
                        }
                        else {
                            sub = Token::LexemeSubType::RSBRACE;
                        }
                    }
                    else {
                        if (cur_line[i] == '*') {
                            sub = Token::LexemeSubType::MULTIPLY_OPERATOR;
                        }
                        else {
                            sub = Token::LexemeSubType::DIVIDE_OPERATOR;
                        }
                    }
                string tmp_str;
                tmp_str.push_back(cur_line[i]);
                tokens->push_back(Token(coord, sub, tmp_str));
                // Чистить слово не нужно, потому что мы в него ничего не клали
                break;
            }
            case '0':case '1':case'2':case'3':case '4':case '5':case'6':case'7':case'8':case '9': {
                bool part_of_lexeme = word.empty();
                while (cur_line[i] <= '9' && cur_line[i] >= '0')
                {
                    word.push_back(cur_line[i]);
                }
                if (cur_line[i] == '.') {
                    if (part_of_lexeme) {
                        sub = Token::USER_KEY_WORD;
                        tokens->push_back(Token(coord, sub, word));
                        word.clear();
                    }
                    sub = Token::LexemeSubType::DOUBLE_LITERAL;
                    word.push_back(cur_line[i]);
                    while (cur_line[i] <= '9' && cur_line[i] >= '0')
                    {
                        word.push_back(cur_line[i]);
                    }
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                ///////////////////////////////////////////////////// can be continue of lexeme
                else {
                    if (!part_of_lexeme) {
                        sub = Token::LexemeSubType::INTEGER_LITERAL;
                        tokens->push_back(Token(coord, sub, word));
                        word.clear();
                    }
                }
                break;
            }
           case ':': {
               char c = word[i + 1];
               if (!word.empty()) {
                   it = examples.find(word);
                   if (it == examples.end()) {
                       sub = Token::LexemeSubType::USER_KEY_WORD;
                   }
                   else {
                       sub = it->second;
                   }
                   tokens->push_back(Token(line_counter, sub, word));
                   word.clear();
               }
               if (c == '=') {
                   i++;
                   sub = Token::LexemeSubType::ASSIGN_OPERATOR;
                   tokens->push_back(Token(coord, sub, string(":=")));
                   word.clear();
               }
               else {
                   sub = Token::LexemeSubType::COLON;
                   tokens->push_back(Token(coord, sub, string(":")));
                   word.clear();
               }
                break;
            }
            case '<':case'>': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(line_counter, sub, word));
                    word.clear();
                }
                char c = word[i];
                if (word[i + 1] == '=')
                {
                    i++;
                    word.push_back(cur_line[i]);
                    if (c == '<') {
                        sub = Token::LexemeSubType::LESS_OR_EQUALS_RELATIONAL_OPERATOR;                   
                    }
                    else {
                        sub = Token::LexemeSubType::GREATER_OR_EQUALS_RELATIONAL_OPERATOR;
                    }
                }
                else {
                    if (word[i + 1] == '>' && c == '<') {
                        i++;
                        word.push_back(cur_line[i]);
                        sub = Token::LexemeSubType::NOT_EQUALS_RELATIONAL_OPERATOR;
                    }
                    else {
                        if (c == '<') {
                            sub = Token::LexemeSubType::LESS_RELATIONAL_OPERATOR;
                        }
                        else {
                            sub = Token::LexemeSubType::GREATER_RELATIONAL_OPERATOR;
                        }
                    }                    
                }
                tokens->push_back(Token(coord, sub, word));
                break;
            }
            case '=': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(line_counter, sub, word));
                    word.clear();
                }
                sub = Token::LexemeSubType::EQUALS_RELATION_OPERATOR;
                tokens->push_back(Token(line_counter, sub, string("=")));
                break;
            }
            case '\'': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(line_counter, sub, word));
                    word.clear();
                }
                word.push_back(cur_line[i]);
                i++;
                while (cur_line[i] != '\'' && i != cur_line.size()) {
                    word.push_back(cur_line[i]);
                    i++;
                }
                if (i == cur_line.size()) {
                    eh->push(line_counter, progError::k_UNEXPECTED_TERMINATION_OF_STRING, true);
                }
                tokens->push_back(Token(coord, sub, word));
                break;
            }
            default: {
                word.push_back(tolower(cur_line[i]));
            }
            }
        }
next_line:        line_counter++;
    }
    sub = Token::LexemeSubType::END_OF_FILE;
    coord.set(line_counter, 0);
    tokens->push_back(Token(coord, sub, string("eof")));
}