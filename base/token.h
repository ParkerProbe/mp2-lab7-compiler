#pragma once

#include "string"
#include <fstream>
#include <string>

using std::string;



/// May be too much functions to be realized
/// Methods and constructors in Token

/// !!! Sintaxer MUST realize:
/// + - * / div mod :=
/// if then else
/// begin end end; end.
/// > < >= <= = <>
/// keywords, double and integer types

/// OTHER THINGS SUCH AS
/// in or and etc
/// Are NOT necessary

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
        BRACKET /*(, )*/,
        IO_OPERATOR /*WRITE, READ*/,
        DECLARATION_KEYWORD /* INTEGER, DOUBLE, VAR, CONST, PROGRAM, 
        program name */,
        SERVICE_KEYWORDS /*BEGIN, END, IF, ELSE, THEN*/,
        LITERAL /*INT, DOUBLE, STRING*/,
        ASSIGNMENT_OPERATOR /* := : */, 
        ENDOFFILE /* IT MUST BE AT THE END OF PROGRAM */, // SMALL TYPE 
                 
    };
    //!!! AFTER CHOOSING ONE BIG TYPE FIND SMALL TYPE FROM:
    enum LexemeSubType
    {
        PROGRAM_HEADING /* program */, SEMICOLON /* ; */,
        BEGIN_KEYWORD /* begin */, END_KEYWORD /* end */,
        IF_HEADING /* if */, THEN_KEYWORD /* then */, ELSE_KEYWORD /* else */,
        LSBRACE /* ( */, RSBRACE /* ) */, //LBRACE/* { */, RBRACE /* } */,
        PLUS_OPERATOR, MINUS_OPERATOR, MULTIPLY_OPERATOR, DIVIDE_OPERATOR,
        DIV_OPERATOR, MOD_OPERATOR, COMMA /* , */, ASSIGN_OPERATOR /*:=*/,
        AND_OPERATOR, OR_OPERATOR, EQUALS_RELATION_OPERATOR /* = */,
        NOT_EQUALS_RELATIONAL_OPERATOR /* <> */, LESS_RELATIONAL_OPERATOR,
        LESS_OR_EQUALS_RELATIONAL_OPERATOR, GREATER_RELATIONAL_OPERATOR,
        GREATER_OR_EQUALS_RELATIONAL_OPERATOR /* >= */, COLON /* : */,
        CONST_DEFINITION_KEYWORD /* const */, VAR_DEFINITION_KEYWORD /* var */,
        READ_FUNC /* read */, WRITE_FUNC /* write */, INTEGER_TYPE /*integer*/,
        DOUBLE_TYPE /* double */, USER_KEY_WORD /* everything else */,
        INTEGER_LITERAL /* int value */, DOUBLE_LITERAL /* double value*/,
        STRING_LITERAL /* string value*/, PROGRAM_NAME /* program's name */,
        END_OF_FILE
    };

    struct StringCoord
    {
        int col; // number of line where token is in
        int space; // number of spaces before the line 
        StringCoord(int col_ = 0, int _sp = -1) : col(col_), space(_sp)
        {}
        void set(int col_, int _sp)
        {
            col = col_;
            space = _sp;
        }
    };
private:
    std::string text;
    LexemeType type;
    LexemeSubType subtype;
    StringCoord position_in_string;

    // Prohibition
    Token(StringCoord);
    Token() {}
public:
        //Token(StringCoord coord, LexemeType lex_type, LexemeSubType lex_sub_type, std::string _text, void*);
    Token(StringCoord coord, LexemeType lex_type, LexemeSubType lex_sub_type,
        std::string _text) :
        position_in_string(coord), type(lex_type), subtype(lex_sub_type), 
        text(text)
    {}
    ~Token() = default;

    inline LexemeType g_type() const;
    inline LexemeSubType s_type() const;
    inline std::string get_text() const;
    //inline void* get_value(); // May be will help anyone
    inline int get_nesting() const;

    bool operator==(const std::string lex_text);//text from other lexeme
    bool operator!=(const std::string lex_text);//text from other lexeme
};
