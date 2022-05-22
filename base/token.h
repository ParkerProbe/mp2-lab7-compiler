#pragma once

#include "string"
#include <fstream>
#include <string>

using std::string;



/// May be too much functions to be realized
/// Methods and constructors in Token

class Token
{
public:
    /// Min number of spaces which makes tab
    static const int k_MIN_TAB = 2;

    enum LexemeType 
    {
        //!!! AT FIRST USE THESE TYPES IN SYNTAX ANALYZER:
        ADDITION_OPERATOR /* +, -, OR */,
        MULTYPLICATION_OPERATOR, /* *, /, AND, MOD, DIV */
        RELATIONAL_OPERATOR /* >, <, >=, <=, =, <>, IN*/,
        IO_OPERATOR /*WRITE, READ*/,
        DECLARATION_KEYWORD /* INTEGER, REAL, VAR, CONST, PROGRAM*/,
        SERVICE_KEYWORDS /*BEGIN, END, IF, ELSE, THEN*/,
        LITERAL /*INT, DOUBLE, STRING*/,
        ASSIGNMENT_OPERATOR /* := */, // ALSO SMALL TYPE
        ENDOFFILE /* IT MUST BE AT THE END OF PROGRAM */, // ALSO SMALL TYPE 

        //!!! AFTER CHOOSING ONE BIG TYPE FIND SMALL TYPE FROM:
        //DOT /* '.' */,
        INTEGER_LITERAL /* int value*/, REAL_LITERAL /* double value*/, 
        STRING_LITERAL /* string value*/,  DELIMETER /* '_' */, 
        PROGRAM_HEADING /* program + name */, SEMICOLON /* ; */, 
        BEGIN_KEYWORD /* begin */, END_KEYWORD /* end */,
        IF_HEADING /* if */, THEN_KEYWORD /* then */, ELSE_KEYWORD /* else */, 
        LSBRACE /* ( */, RSBRACE /* ) */, LBRACE/* { */, RBRACE /* } */, 
        PLUS_OPERATOR, MINUS_OPERATOR, MULTIPLY_OPERATOR, DIVIDE_OPERATOR,
        FDIV_OPERATOR, IDIV_OPERATOR, MOD_OPERATOR, COMMA /* , */,
        AND_OPERATOR, OR_OPERATOR, EQUALS_RELATION_OPERATOR /* = */, 
        NOT_EQUALS_RELATIONAL_OPERATOR /* <> */, LESS_RELATIONAL_OPERATOR, 
        LESS_OR_EQUALS_RELATIONAL_OPERATOR, GREATER_RELATIONAL_OPERATOR, 
        GREATER_OR_EQUALS_RELATIONAL_OPERATOR /* >= */, COLON /* : */,
        CONST_DEFINITION_KEYWORD /* const */, VAR_DEFINITION_KEYWORD /* var */, 
        READ_FUNC /* read */, WRITE_FUNC /* write */, INTEGER_TYPE /*integer*/,
    };

private:
        struct StringCoord 
        {
            int col; // number of line where token is in
            int space; // number of spaces before the line 
            StringCoord(int col_ = -1, int _sp=0) : col(col_), space(_sp)
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
        inline std::string get_text() const;
        inline void* get_value();
        inline int get_nesting() const;

        bool operator==(const std::string);
        bool operator!=(const std::string);
};
