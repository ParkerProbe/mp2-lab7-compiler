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
        END_OF_FILE /*this lexeme is only at the end of program*/,
        DEFAULT_TYPE /*this sh*t shows that token is empty*/
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
    StringCoord position_in_string;
    LexemeSubType subtype;
    std::string text;   
    // Prohibition
    Token(StringCoord);
public:
        //Token(StringCoord coord, LexemeType lex_type, LexemeSubType lex_sub_type, std::string _text, void*);
    Token(StringCoord coord, /*LexemeType lex_type,*/ LexemeSubType lex_sub_type,
        std::string _text) :
        position_in_string(coord), /*type(lex_type),*/ subtype(lex_sub_type), 
        text(text)
    {}
    Token():position_in_string(0,-1),subtype(Token::LexemeSubType::DEFAULT_TYPE),text("")
    {}
    ~Token() = default;

    Token::LexemeSubType s_type() const;
    std::string get_text() const;
    //inline void* get_value(); // May be will help anyone
    int get_nesting() const;
    int get_line_num() const;

    bool operator==(const std::string lex_text);//text from other lexeme
    bool operator!=(const std::string lex_text);//text from other lexeme
};
