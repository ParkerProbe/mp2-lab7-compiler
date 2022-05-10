#pragma once

#include "string"
#include <fstream>
#include <string>

using std::string;

/// NIL - constant of null pointer. We have no pointers. Why we need nil?
/// PROGRAM_BLOCK ?
/// RANGE ?
/// ADDITION_OPERATOR and PLUS_OPERATOR ?
/// May be too much functions to be realized
/// Explain StringCoord
/// DECLARATION_TYPE. It is 'integer', 'real' ?
/// LSBRACE and RSBRACE ?
/// INVALID, KEYWORD, RESERVED_IDENTIFIER, UNRESERVED_IDENTIFIER ? ALL OF THIS

class Token
{

    enum LexemeType 
    {
        INVALID, KEYWORD, RESERVED_IDENTIFIER, UNRESERVED_IDENTIFIER,
        INTEGER_LITERAL /* int value*/, FLOAT_LITERAL /* float value*/, STRING_LITERAL /* string value*/, OPERATOR,
        DELIMETER /* '_' */, RANGE, PROGRAM_HEADING, SEMICOLON /* ; */, ENDOFFILE,
        BEGIN_KEYWORD, END_KEYWORD, ASSIGNMENT_OPERATOR /* ':=' */, DOT /* '.' */,
        IF_HEADING, THEN_KEYWORD, ELSE_KEYWORD, ADDITION_OPERATOR,
        MULTIPLICATION_OPERATOR, NIL, LSBRACE, RSBRACE, COMMA /* ',' */,
        LBRACE/* { */, RBRACE /* } */, PLUS_OPERATOR, MINUS_OPERATOR, OR_OPERATOR,
        FDIV_OPERATOR, IDIV_OPERATOR, MOD_OPERATOR,
        AND_OPERATOR, EQUALS_RELATION_OPERATOR, NOT_EQUALS_RELATIONAL_OPERATOR /* <> */,
        LESS_RELATIONAL_OPERATOR, LESS_OR_EQUALS_RELATIONAL_OPERATOR,
        GREATER_RELATIONAL_OPERATOR, GREATER_OR_EQUALS_RELATIONAL_OPERATOR,
        PROGRAM_BLOCK /* 'program' */, CONST_DEFINITION_KEYWORD /* 'const'*/, 
        DECLARATION_TYPE, VAR_DEFINITION_KEYWORD /* 'var' */, COLON /* ':' */,
        READ_FUNC /* 'read' */, WRITE_FUNC /* 'write' */
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
