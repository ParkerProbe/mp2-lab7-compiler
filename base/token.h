#pragma once

#include "string"
#include <fstream>
#include <string>

using std::string;



/// May be too much functions to be realized

class Token
{
public:
    /// Min number of spaces which makes tab
    static const int k_MIN_TAB = 2;

    enum LexemeType 
    {
        //DOT /* '.' */,
        INTEGER_LITERAL /* int value*/, REAL_LITERAL /* double value*/, 
        STRING_LITERAL /* string value*/,  DELIMETER /* '_' */, 
        PROGRAM_HEADING /* program + name */, SEMICOLON /* ; */, 
        ENDOFFILE /*end in code*/, BEGIN_KEYWORD /* begin */, END_KEYWORD /* end */, 
        ASSIGNMENT_OPERATOR /* ':=' */, WR_STR /*string from write operator*/,
        IF_HEADING /* if */, THEN_KEYWORD /* then */, ELSE_KEYWORD /* else */, 
        LSBRACE /* ( */, RSBRACE /* ) */, LBRACE/* { */, RBRACE /* } */, 
        PLUS_OPERATOR, MINUS_OPERATOR, MULTIPLICATION_OPERATOR, DIVISION_OPERATOR,
        FDIV_OPERATOR, IDIV_OPERATOR, MOD_OPERATOR, COMMA /* , */,
        AND_OPERATOR, OR_OPERATOR, EQUALS_RELATION_OPERATOR /* = */, 
        NOT_EQUALS_RELATIONAL_OPERATOR /* <> */, LESS_RELATIONAL_OPERATOR, 
        LESS_OR_EQUALS_RELATIONAL_OPERATOR, GREATER_RELATIONAL_OPERATOR, 
        GREATER_OR_EQUALS_RELATIONAL_OPERATOR, 
        CONST_DEFINITION_KEYWORD /* const */, VAR_DEFINITION_KEYWORD /* var */,
        DECLARATION_TYPE /* integer or real */, COLON /* : */,
        READ_FUNC /* read */, WRITE_FUNC /* write */
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
