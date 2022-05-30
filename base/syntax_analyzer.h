#pragma once
#include <vector>

#include "text_link.h"
#include "token.h"
#include "error_handler.h"
#include "symbol_table_rec.h"
#include "hash_table_list.h"

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
        int countbrake1 = 0;
        int countbrake2 = 0;
        int countbrace1 = 0;
        int countbrace2 = 0;
        int countif = 0;
        int countthen = 0;
        std::vector<Token>::iterator iter = (*tokens).begin();
        while ((iter != (*tokens).end()) && ((*iter).g_type()!= Token::LexemeType::ENDOFFILE))
        {
            int space, spacecurr;
            if (txt_link->get_node() == NULL)
            {
                txt_link->set_first_node(*iter);
                ++iter;
                continue;
            }

            switch ((*iter).g_type())
            {
            case Token::LexemeSubType::BEGIN_KEYWORD:
                countbrake1++;
                break;
            case Token::LexemeSubType::END_KEYWORD:
                countbrake2++;
                break;
            case Token::LexemeSubType::LSBRACE:
                countbrace1++;
                break;
            case Token::LexemeSubType::RSBRACE:
                countbrace2++;
                break;
            case Token::LexemeSubType::IF_HEADING:
                countif++;
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
        if (countbrace1!=countbrace2||countbrake1!=countbrake2||countif!=countthen)
            err->push(0, progError::k_FIRST_PART_OF_PAIR_IS_MISSED, true);
    }
};