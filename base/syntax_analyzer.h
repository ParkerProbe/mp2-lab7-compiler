#pragma once
#include <vector>

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
//#include "symbol_table_rec.h"
//#include "hash_table_list.h"

class SyntaxAnalyzer
{

private:
    TText<Token>* txt_link;
    ErrorHandler* err;
    std::vector<Token>* tokens;
public:
    SyntaxAnalyzer
    (
        TText<Token>* txt_link_,
        std::vector<Token>* tokens_,
        ErrorHandler* err_
    )
        : txt_link(txt_link_), tokens(tokens_), err(err_)
    {}

    void Start()
    {
        int num1, num2, num3;
        int countbrake1 = 0;
        int countbrake2 = 0;
        int countbrace1 = 0;
        int countbrace2 = 0;
        int countif = 0;
        int countthen = 0;
        std::vector<Token>::iterator iter = (*tokens).begin();
        while (iter != (*tokens).end())
        {
            int space, spacecurr;
            if (txt_link->is_empty() == true)
            {
                txt_link->set_first_node(*iter);
                ++iter;
                continue;
            }

            switch ((*iter).s_type())
            {
            case Token::LexemeSubType::BEGIN_KEYWORD:
                countbrake1++;
                if (countbrake1 == 1)
                    num1 = (*iter).get_line_num();
                break;
            case Token::LexemeSubType::END_KEYWORD: case Token::LexemeSubType::END_OF_FILE:
                countbrake2++;
                break;
            case Token::LexemeSubType::LSBRACE:
                countbrace1++;
                if (countbrace1 == 1)
                    num2 = (*iter).get_line_num();
                break;
            case Token::LexemeSubType::RSBRACE:
                countbrace2++;
                break;
            case Token::LexemeSubType::IF_HEADING:
                countif++;
                if (countif == 1)
                    num3 = (*iter).get_line_num();
                break;
            case Token::LexemeSubType::THEN_KEYWORD:
                countthen++;
                break;
            }
            spacecurr = txt_link->get_node().get_nesting();
            space = (*iter).get_nesting();

            if (space == spacecurr)
            {
                txt_link->ins_next_node(*iter);
                txt_link->go_next_node();
            }
            if (space < spacecurr)
            {
                while (space < txt_link->get_node().get_nesting())
                    txt_link->go_prev_node();
                txt_link->ins_next_node(*iter);
                txt_link->go_next_node();
            }
            if (space > spacecurr)
            {
                txt_link->ins_down_node(*iter);
                txt_link->go_down_node();
            }
            ++iter;
        }
        if (countbrake1 != countbrake2)
            err->push(num1, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true); 
        if (countbrace1 != countbrace2)
            err->push(num2, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true);
        if (countif != countthen)
            err->push(num3, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true);

    }
};