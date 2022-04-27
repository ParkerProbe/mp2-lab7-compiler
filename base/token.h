#pragma once
#include "string"
#include <fstream>
#include <string>

using std::string;

class Token
{

    enum LexemeType 
    {
        INVALID, KEYWORD, RESERVED_IDENTIFIER, UNRESERVED_IDENTIFIER,
        INTEGER_LITERAL, FLOAT_LITERAL, STRING_LITERAL, OPERATOR, 
        DELIMETER, RANGE, PROGRAM_HEADING, SEMICOLON,ENDOFFILE,
        BEGIN_KEYWORD, END_KEYWORD, ASSIGNMENT_OPERATOR, DOT, WHILE_HEADING,
        RELATIONAL_OPERATOR, DO_KEYWORD, REPEAT_HEADING, UNTIL_KEYWORD, FOR_HEADING,
		FOR_UP_KEYWORD, FOR_DOWN_KEYWORD, IF_HEADING, THEN_KEYWORD, ELSE_KEYWORD,
        ADDITION_OPERATOR, MULTIPLICATION_OPERATOR, NIL, LSBRACE, RSBRACE, COMMA, LBRACE, RBRACE, PLUS_OPERATOR,
		MINUS_OPERATOR, OR_OPERATOR, MUL_OPERATOR, FDIV_OPERATOR, IDIV_OPERATOR, MOD_OPERATOR,
        AND_OPERATOR, EQUALS_RELATION_OPERATOR, NOT_EQUALS_RELATIONAL_OPERATOR, LESS_RELATIONAL_OPERATOR,
		LESS_OR_EQUALS_RELATIONAL_OPERATOR, GREATER_RELATIONAL_OPERATOR,
        GREATER_OR_EQUALS_RELATIONAL_OPERATOR, IN_RELATIONAL_OPERATOR, PROGRAM_BLOCK, CONST_DEFINITION_KEYWORD, 
		DECLARATION_TYPE, VAR_DEFINITION_KEYWORD, COLON, ARRAY_HEADING, OF_KEYWORD
    };

    std::string keywords[34] = 
    {
        "and", "array", "begin", "break", "const", "continue",
        "div", "do", "else", "end", "file", 
        "if", "in", "mod", "nil", "not", "of",
        "or","program", "record", "repeat",
        "set", "then", "to", "var", "while",
        "with", "xor",
    };

private:
        struct StringCoord
        {
			int col, row;
		};

		std::string text;
		LexemeType type;

		StringCoord position_in_string;



public:
		

        Token() {}
		Token(StringCoord, LexemeType, std::string, void*);
		Token(StringCoord);
		~Token();

		inline void set_text(std::string);
		inline void set_type(LexemeType);

		void print(std::ofstream& output);

		inline int get_line() const;
		inline LexemeType get_type() const;
		inline LexemeType get_sub_type();
		inline std::string get_text();

		inline void* getValue();

		bool operator==(const char*);
		bool operator!=(const char*);



};