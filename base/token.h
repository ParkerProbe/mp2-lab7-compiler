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
        DELIMETER /* '_' */, RANGE, PROGRAM_HEADING, SEMICOLON, ENDOFFILE,
        BEGIN_KEYWORD, END_KEYWORD, ASSIGNMENT_OPERATOR, DOT,
        IF_HEADING, THEN_KEYWORD, ELSE_KEYWORD, ADDITION_OPERATOR,
        MULTIPLICATION_OPERATOR, NIL, LSBRACE, RSBRACE, COMMA /* ',' */,
        LBRACE, RBRACE, PLUS_OPERATOR, MINUS_OPERATOR, OR_OPERATOR,
        FDIV_OPERATOR, IDIV_OPERATOR, MOD_OPERATOR,
        AND_OPERATOR, EQUALS_RELATION_OPERATOR, NOT_EQUALS_RELATIONAL_OPERATOR,
        LESS_RELATIONAL_OPERATOR, LESS_OR_EQUALS_RELATIONAL_OPERATOR,
        GREATER_RELATIONAL_OPERATOR, GREATER_OR_EQUALS_RELATIONAL_OPERATOR,
        PROGRAM_BLOCK, CONST_DEFINITION_KEYWORD, 
        DECLARATION_TYPE, VAR_DEFINITION_KEYWORD, COLON /* ':' */,
        READ_FUNC, WRITE_FUNC
        /* ' ' - ?*/
    };

private:
        struct StringCoord
        {
            int col;
            // int row;
            StringCoord(int col_ = -1) : col(col_)
                {}
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
        inline void* get_value();

        bool operator==(const std::string);
        bool operator!=(const std::string);
};
