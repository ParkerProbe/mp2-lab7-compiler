////
//
//#include "postfix.h"
//#include <gtest.h>
//
//TEST(TPostfix, can_create_postfix)
//{
//    ASSERT_NO_THROW(TPostfix p);
//}
//
//TEST(TPostfix, can_get_infix)
//{
//    std::vector<Token>* tokens;
//    Token::LexemeSubType sub;
//    sub = Token::LexemeSubType::INTEGER_LITERAL;
//    tokens->push_back(Token(1, sub, string("2")));
//    tokens->push_back(Token(1, Token::LexemeSubType::PLUS_OPERATOR, string("+")));
//    tokens->push_back(Token(1, sub, string("5")));
//    TPostfix p;
//    p.set_infix(*tokens);
//    bool flag;
//    if (p.get_infix() == *tokens)
//        flag = true;
//    EXPECT_EQ(true, flag);
//}
//
//TEST(TPostfix, can_get_postfix)
//{
//    std::vector<Token>* tokens;
//    Token::LexemeSubType sub;
//    sub = Token::LexemeSubType::INTEGER_LITERAL;
//    tokens->push_back(Token(1, sub, string("2")));
//    tokens->push_back(Token(1, Token::LexemeSubType::PLUS_OPERATOR, string("+")));
//    tokens->push_back(Token(1, sub, string("5")));
//    std::vector<Token>* post;
//    post->push_back(Token(1, sub, string("2")));
//    post->push_back(Token(1, sub, string("5")));
//    post->push_back(Token(1, Token::LexemeSubType::PLUS_OPERATOR, string("+")));
//    TPostfix p;
//    p.set_infix(*tokens);
//    p.to_postfix();
//    EXPECT_EQ(*post, p.get_postfix());
//}
//TEST(TPostfix, can_calculate)
//{
//    UnsortListTable < std::string, SymbolTableRec < int>>* symbol_table_int; UnsortListTable < std::string, SymbolTableRec < double>>* symbol_table_double;
//    std::vector<Token>* tokens = new vector<Token>;;
//    Token::LexemeSubType sub;
//    sub = Token::LexemeSubType::INTEGER_LITERAL;
//    tokens->push_back(Token(1, sub, string("2")));
//    tokens->push_back(Token(1, Token::LexemeSubType::PLUS_OPERATOR, string("+")));
//    tokens->push_back(Token(1, sub, string("5")));
//    TPostfix p;
//    p.set_infix(*tokens);
//    p.to_postfix();
//    EXPECT_EQ((double)5, p.calculate(symbol_table_int, symbol_table_double));
//}
