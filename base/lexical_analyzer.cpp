#include "lexical_analyzer.h"

void LexicalAnalyzer::create_tokens()
{
    const int k_num_of_tokens = 32;// name of program can be everything, but...

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
                    tokens->push_back(Token(coord, sub, word));
                }
                else {
                    if (word == string("program")) {
                        sub = Token::LexemeSubType::PROGRAM_HEADING;
                        tokens->push_back(Token(coord, sub, word));
                    }
                    else {
                        eh->push(line_counter, progError::k_NO_PROGRAM_KEY_WORD, true);
                    }
                }
                word.clear();
            }
            word_counter++;
        }
        else
            if (cur_line[i] == ';')
            {
                if (!word.empty()) {
                    coord.set(line_counter, gap_counter);
                    if (word_counter) {
                        sub = Token::LexemeSubType::PROGRAM_NAME;
                        tokens->push_back(Token(coord, sub, word));
                    }
                    else {
                        if (word == string("program")) {
                            sub = Token::LexemeSubType::PROGRAM_HEADING;
                            tokens->push_back(Token(coord, sub, word));
                        }
                        else {
                            eh->push(line_counter, progError::k_NO_PROGRAM_KEY_WORD, true);
                        }
                    }
                }
                tokens->push_back(Token(coord, Token::LexemeSubType::SEMICOLON, string(";")));
                break;
            }
    }
    if (word_counter < 1)
        eh->push(line_counter, progError::k_NO_PROGRAM_NAME, true);
    line_counter++;
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
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                sub = Token::LexemeSubType::SEMICOLON;
                tokens->push_back(Token(coord, sub, string(";")));
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
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                while (cur_line[i] == ' ' && i < cur_line.size()) {
                    i++;
                }
                i--;
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
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
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
                bool part_of_lexeme = !word.empty();
                while (cur_line[i] <= '9' && cur_line[i] >= '0')
                {
                    word.push_back(cur_line[i]);
                    i++;
                }
                if (part_of_lexeme) {
                    i--;
                    break;
                }
                else {
                    if (cur_line[i] == '.') {
                        sub = Token::LexemeSubType::DOUBLE_LITERAL;
                        word.push_back(cur_line[i]);
                        i++;
                        while (cur_line[i] <= '9' && cur_line[i] >= '0')
                        {
                            word.push_back(cur_line[i]);
                            i++;
                        }
                        i--;
                        tokens->push_back(Token(coord, sub, word));
                        word.clear();
                    }
                    else {
                        sub = Token::LexemeSubType::INTEGER_LITERAL;
                        tokens->push_back(Token(coord, sub, word));
                        word.clear();
                        i--;
                    }
                }
                break;
            }
            case ':': {
                char c = cur_line[i + 1];
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(coord, sub, word));
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
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                char c = cur_line[i];
                if (cur_line[i + 1] == '=')
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
                    if (cur_line[i + 1] == '>' && c == '<') {
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
                word.clear();
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
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                sub = Token::LexemeSubType::EQUALS_RELATION_OPERATOR;
                tokens->push_back(Token(coord, sub, string("=")));
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
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                word.push_back(cur_line[i]);
                i++;
                while (cur_line[i] != '\'' && i != cur_line.size()) {
                    word.push_back(cur_line[i]);
                    i++;
                }
                if (i < cur_line.size()) {
                    word.push_back(cur_line[i]);
                }
                else {
                    eh->push(line_counter, progError::k_UNEXPECTED_TERMINATION_OF_STRING, true);
                }
                tokens->push_back(Token(coord, sub, word));
                word.clear();
                break;
            }
            case '.': {
                word.push_back(cur_line[i]);
                if (word == "end.") {
                    tokens->push_back(Token(coord, Token::LexemeSubType::END_OF_FILE, word));
                    return;
                }
            }
            case ',': {
                if (!word.empty()) {
                    it = examples.find(word);
                    if (it == examples.end()) {
                        sub = Token::LexemeSubType::USER_KEY_WORD;
                    }
                    else {
                        sub = it->second;
                    }
                    tokens->push_back(Token(coord, sub, word));
                    word.clear();
                }
                tokens->push_back(Token(coord, Token::LexemeSubType::COMMA, string(",")));
            }
            default: {
                word.push_back(tolower(cur_line[i]));
            }
            }
        }
        if (!word.empty()) {
            it = examples.find(word);
            if (it == examples.end()) {
                sub = Token::LexemeSubType::USER_KEY_WORD;
            }
            else {
                sub = it->second;
            }
            tokens->push_back(Token(coord, sub, word));
            word.clear();
        }
    next_line:        line_counter++;
    }
}