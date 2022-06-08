#include "semantic_analyzer.h"

// Add error type 
// Separate analyzator errors

void SemanticAnalyzer::set_var_int(Token symbol, int num, bool is_set, bool is_const)
{
    SymbolTableRec<int> tmp(SymbolTableRec<int>(symbol.get_text(), num, is_const, is_set));
    SymbolTableRec<int>* tmp_var = symbol_table_int->Find(symbol.get_text());

    if (tmp_var != nullptr) {
        if (tmp_var->is_const == true) {
            err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
        }
        else {
            tmp_var->num = num;
        }
    }
    else {
        symbol_table_int->Insert(symbol.get_text(), tmp);
    }
}

void SemanticAnalyzer::set_var_double(Token symbol, double num, bool is_set, bool is_const)
{
    SymbolTableRec<double> tmp(SymbolTableRec<double>(symbol.get_text(), num, is_const, is_set));
    SymbolTableRec<double>* tmp_var = symbol_table_double->Find(symbol.get_text());

    if (tmp_var != nullptr) {
        if (tmp_var->is_const == true) {
            err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
        }
        else {
            tmp_var->num = num;
        }
    }
    else {

        symbol_table_double->Insert(symbol.get_text(), tmp);

    }
}

SymbolTableRec<int>* SemanticAnalyzer::get_var_int(Token symbol)
{
    if (symbol_table_int->Find(symbol.get_text()) != nullptr) {
        return symbol_table_int->Find(symbol.get_text());

    }
    else {
        return nullptr;
    }
}


SymbolTableRec<double>* SemanticAnalyzer::get_var_double(Token symbol)
{
    if (symbol_table_double->Find(symbol.get_text()) != nullptr) {
        
        return symbol_table_double->Find(symbol.get_text());
    }
    else {
        return nullptr;
    }
}


int SemanticAnalyzer::check_var(Token var, bool is_define = false)
{
    // is_define - true = it in const, var block
    // Return
    enum Var_Type
    {
        not_found = -1,
        val_not_set = 0,
        int_val = 1,
        k_int_val = 2,
        double_val = 3,
        k_double_val = 4
    };
    
    SymbolTableRec<int>* find_int;
    SymbolTableRec<double>* find_double;

    find_int = get_var_int(var);
    if (find_int != nullptr) {
        if (!find_int->is_set) {
            return val_not_set;
        }

        if (find_int->is_const) {
            return k_int_val;
        }
        else {
            return int_val;
        }
    }
    
    find_double = get_var_double(var);
    if (find_double != nullptr) {
        if (!find_double->is_set) {
            return val_not_set;
        }

        if (find_double->is_const) {
            return k_double_val;
        }
        else {
            return double_val;
        }
    }
    if (!is_define) {
        err->push(var.get_line_num(), progError::k_ID_NO_DECLARATED, true);
    }
    return not_found;
}


void SemanticAnalyzer::set_var(Token var, Token value, bool is_set, bool is_const)
{


        if (value.s_type() == Token::DOUBLE_LITERAL) {


            try {
                double num = stod(value.get_text());
                set_var_double(var, num, is_set, is_const);

            }
            catch (...) {
                set_var_double(var, 0, is_set, is_const);
            }
        }

        if (value.s_type() == Token::INTEGER_LITERAL) {


            try {
                int num = stoi(value.get_text());
                set_var_int(var, num, is_set, is_const);

            }
            catch (...) {
                set_var_int(var, 0 , is_set, is_const);
            }
        }
}


void SemanticAnalyzer::Start()
{

    txt_link->go_first_node();

    // program
    txt_link->go_next_node();
    // program name
    txt_link->go_next_node();
    // var || const || begin
    txt_link->go_next_node();


    // Const block
    if (txt_link->get_node().s_type() == Token::CONST_DEFINITION_KEYWORD) {
        txt_link->go_down_node();
        do {
            // Add variable
            Token var;
            bool is_minus = false;
            
            var = txt_link->get_node();

            // :
            txt_link->go_next_node();
            // Var type
            txt_link->go_next_node();
            if ((txt_link->get_node().s_type() == Token::DOUBLE_TYPE) || (txt_link->get_node().s_type() == Token::INTEGER_TYPE)) { ; }
            else {
                err->push(var.get_line_num(), progError::k_TYPE_NO_DECLARATED, true);
            }

            // ; or =
            txt_link->go_next_node();

            if (txt_link->get_node().s_type() == Token::SEMICOLON) {
                if (check_var(var, true) != -1) {
                    err->push(var.get_line_num(), progError::k_ID_DOUBLE_DECLARATION, true);
                }
                //Const  not set
                err->push(var.get_line_num(), progError::k_CONST_NOT_INIT, true);
                continue;
            }

            // Value
            if (check_var(var, true) != -1) {
                err->push(var.get_line_num(), progError::k_ID_DOUBLE_DECLARATION, true);
            }
            txt_link->go_next_node();

            // DELETE
            if (txt_link->get_node().s_type() == Token::MINUS_OPERATOR) {
                is_minus = true;
                txt_link->go_next_node();
            }

            if (is_minus) {
                Token tmp = txt_link->get_node();
                tmp.text.insert(tmp.text.begin(), '-');
                set_var(var, tmp, true, true);
            }
            else {
                set_var(var, txt_link->get_node(), true, true);
            }

            // ;
            txt_link->go_next_node();
        
        } while (txt_link->go_next_node());

        while (txt_link->get_node().s_type() != Token::CONST_DEFINITION_KEYWORD) {
            txt_link->go_prev_node();
        }
    }

    if (txt_link->get_node().s_type() == Token::CONST_DEFINITION_KEYWORD) {
        txt_link->go_next_node();
    }

    // Var block
    if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
        txt_link->go_down_node();
        do {
            // Add variable
            Token var;
            Token var_type;
            bool is_minus = false;

            var = txt_link->get_node();

            // :
            txt_link->go_next_node();

            // Var type
            txt_link->go_next_node();
            var_type = txt_link->get_node();
            if ((txt_link->get_node().s_type() == Token::DOUBLE_TYPE) || (txt_link->get_node().s_type() == Token::INTEGER_TYPE)) { ; }
            else {
                err->push(var.get_line_num(), progError::k_TYPE_NO_DECLARATED, true);
            }

            // ; or =
            txt_link->go_next_node();

            if (txt_link->get_node().s_type() == Token::SEMICOLON) {
                if (check_var(var, true) != -1) {
                    err->push(var.get_line_num(), progError::k_ID_DOUBLE_DECLARATION, true);
                }

                if (var_type.s_type() == Token::DOUBLE_TYPE) {
                    Token tmp = Token();
                    tmp.subtype = Token::DOUBLE_LITERAL;
                    tmp.text = "0.0";
                    set_var(var, tmp, false, false);

                }
                else {
                    Token tmp = Token();
                    tmp.subtype = Token::INTEGER_LITERAL;
                    tmp.text = "0";
                    set_var(var, tmp, false, false);
                }
                continue;
            }

            // Value
            if (check_var(var, true) != -1) {
                err->push(var.get_line_num(), progError::k_ID_DOUBLE_DECLARATION, true);
            }
            txt_link->go_next_node();

            // DELETE
            if (txt_link->get_node().s_type() == Token::MINUS_OPERATOR) {
                is_minus = true;
                txt_link->go_next_node();
            }

            if (is_minus) {
                Token tmp = txt_link->get_node();
                tmp.text.insert(tmp.text.begin(), '-');
                set_var(var, tmp, true, false);
            }
            else {
                set_var(var, txt_link->get_node(), true, false);
            }



            // ;
            txt_link->go_next_node();

        } while (txt_link->go_next_node());

        while (txt_link->get_node().s_type() != Token::VAR_DEFINITION_KEYWORD) {
            txt_link->go_prev_node();
        }
    }


    if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
        txt_link->go_next_node();
    }

    // Main program
    txt_link->go_down_node();

mc:
    do {

        // Begin
        if (txt_link->get_node().s_type() == Token::BEGIN_KEYWORD) {
            txt_link->go_next_node();
        }



        // ASSIGN
        if (txt_link->get_node().s_type() == Token::USER_KEY_WORD) {
            Token var = txt_link->get_node();

            // := or =
            bool is_assign = false;
            txt_link->go_next_node();
            if (txt_link->get_node().s_type() == Token::ASSIGN_OPERATOR) {
                // Check not const
                int var_type = check_var(var);
                if ((var_type == 2) || (var_type == 4)) {
                    err->push(var.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
                }
                is_assign = true;
            }

            if (is_assign) {
                do {
                    txt_link->go_next_node();
                    if (txt_link->get_node().s_type() == Token::USER_KEY_WORD) {
                        Token var = txt_link->get_node();
                        check_var(var);
                    }
                } while (txt_link->get_node().s_type() != Token::SEMICOLON);
            }
            else {
                while (txt_link->get_node().s_type() != Token::SEMICOLON);
            }

            continue;
        }

        /// WRITE
        /// 
        /// Not support alg operations
        if (txt_link->get_node().s_type() == Token::WRITE_FUNC) {
            // (
            txt_link->go_next_node();

            while (txt_link->get_node().s_type() != Token::RSBRACE) {
                txt_link->go_next_node();
                if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
                    check_var(txt_link->get_node());
                }
            }
            // ;
            txt_link->go_next_node();
            continue;
        }


        /// READ
        /// 
        if (txt_link->get_node().s_type() == Token::READ_FUNC) {
            // (
            txt_link->go_next_node();

            txt_link->go_next_node();
            if (txt_link->get_node().s_type() == Token::USER_KEY_WORD) {
                check_var(txt_link->get_node());
            }
            
            // )
            txt_link->go_next_node();

            // ;
            txt_link->go_next_node();
            continue;
        }


        // IF 
        if (txt_link->get_node().s_type() == Token::IF_HEADING) {
            do {
                txt_link->go_next_node();
                if (txt_link->get_node().s_type() == Token::USER_KEY_WORD) {
                    Token var = txt_link->get_node();
                    check_var(var);
                }
            }   while (txt_link->get_node().s_type() != Token::THEN_KEYWORD);

            // Check if without begin
            if (txt_link-> go_down_node() != false) {
                goto mc;
            }
            else {
                // begin
                txt_link->go_next_node();

                // begin body
                if (txt_link->go_down_node()) {
                    goto mc;
                }
            }
        }


        // ELSE
        if (txt_link->get_node().s_type() == Token::ELSE_KEYWORD) {
            // Check else without begin
            if (txt_link->go_down_node() != false) {
                goto mc;
            }
            else {
                // begin
                txt_link->go_next_node();

                // begin body
                if (txt_link->go_down_node()) {
                    goto mc;
                }
            }
        }



    } while (txt_link->go_next_node());

    // End of program
    if (txt_link->get_node().s_type() == Token::END_OF_FILE) {
        return;
    }
    int inner_nesting;
    // End of level
eol:
    inner_nesting = txt_link->get_node().get_nesting();
    while (txt_link->get_node().get_nesting() != inner_nesting - 1)
    {
        txt_link->go_prev_node();
    }

    if (txt_link->get_node().s_type() == Token::THEN_KEYWORD) {
        if (txt_link->go_next_node()) {}
        else {
            goto eol;
        }
    }
    // begin || else || next command (if without else)
    if (!txt_link->go_next_node()) {
        goto eol;
    }

    // end
    if (txt_link->get_node().s_type() == Token::END_KEYWORD) {
        // next of end
        txt_link->go_next_node();
    }

    // Main cycle
    goto mc;


}