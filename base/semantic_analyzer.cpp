#include "semantic_analyzer.h"


// Add error type 
// Separate analyzator errors

void SemanticAnalyzer::set_var_int(Token symbol, int num, bool is_set, bool is_const)
{
    TableBody<SymbolTableRec<int>> tmp(SymbolTableRec<int>(symbol.get_text(), num, is_const));
    tmp.data->is_set = true;
    if (symbol_table_int->insert(symbol.get_text(), tmp) == false) {
        if (symbol_table_int->find(symbol.get_text())->data->is_const != true) {
            symbol_table_int->find(symbol.get_text())->data->num = num;
        }
        else {
            err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
        }
    }
}

void SemanticAnalyzer::set_var_double(Token symbol, double num, bool is_set, bool is_const)
{
    TableBody<SymbolTableRec<double>> tmp(SymbolTableRec<double>(symbol.get_text(), num, is_const));
    tmp.data->is_set = true;
    if (symbol_table_double->insert(symbol.get_text(), tmp) == false) {
        if (symbol_table_double->find(symbol.get_text())->data->is_const != true) {
            symbol_table_double->find(symbol.get_text())->data->num = num;
        }
        else {
            err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
        }
    }
}

SymbolTableRec<int>* SemanticAnalyzer::get_var_int(Token symbol)
{
    if (symbol_table_int->find(symbol.get_text()) != nullptr) {
        return symbol_table_int->find(symbol.get_text())->data;

    }
    else {
        return nullptr;
    }
}


SymbolTableRec<double>* SemanticAnalyzer::get_var_double(Token symbol)
{
    if (symbol_table_double->find(symbol.get_text()) != nullptr) {
        
        return symbol_table_double->find(symbol.get_text())->data;
    }
    else {
        return nullptr;
    }
}


int SemanticAnalyzer::check_var(Token var)
{
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

    err->push(var.get_line_num(), progError::k_VAR_NO_DECLARATED, true);
    return not_found;
}


void SemanticAnalyzer::set_var(Token var, Token value, bool is_set = true, bool is_const = false)
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
            
            var = txt_link->get_node();

            // :
            txt_link->go_next_node();
            // Var type
            txt_link->go_next_node();

            // ; or =
            txt_link->go_next_node();

            if (txt_link->get_node().s_type() == Token::SEMICOLON) {
                //Const  not set
                err->push(var.get_line_num(), progError::k_CONST_NOT_INIT, true);
                continue;
            }

            // Value
            txt_link->go_next_node();
            set_var(var, txt_link->get_node(), true, true);

            // ;
            txt_link->go_next_node();
        
        } while (txt_link->go_next_node());

        while (txt_link->get_node().s_type() != Token::CONST_DEFINITION_KEYWORD) {
            txt_link->go_prev_node();
        }
    }
    
    txt_link->go_next_node();

    // Var block
    if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
        txt_link->go_down_node();
        do {
            // Add variable
            Token var;
            var = txt_link->get_node();

            // :
            txt_link->go_next_node();

            // Var type
            txt_link->go_next_node();

            // ; or =
            txt_link->go_next_node();

            if (txt_link->get_node().s_type() == Token::SEMICOLON) {
                Token default_value;
                set_var(var, default_value, false, false);
                continue;
            }

            // Value
            txt_link->go_next_node();
            set_var(var, txt_link->get_node(), false, false);

            // ;
            txt_link->go_next_node();

        } while (txt_link->go_next_node());

        while (txt_link->get_node().s_type() != Token::VAR_DEFINITION_KEYWORD) {
            txt_link->go_prev_node();
        }
    }

    // Begin
    txt_link->go_next_node();

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
            if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
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
                continue;
            }
            else {
                // begin
                txt_link->go_next_node();

                // begin body
                if (txt_link->go_down_node()) {
                    continue;
                }
            }
        }


        // ELSE
        if (txt_link->get_node().s_type() == Token::ELSE_KEYWORD) {
            // Check else without begin
            if (txt_link->go_down_node() != false) {
                continue;
            }
            else {
                // begin
                txt_link->go_next_node();

                // begin body
                if (txt_link->go_down_node()) {
                    continue;
                }
            }
        }



    } while (txt_link->go_next_node());

    // End of program
    if (txt_link->get_node().s_type() == Token::END_OF_FILE) {
        return;
    }

    // End of level
    int inner_nesting = txt_link->get_node().get_nesting();
    while (txt_link->get_node().get_nesting() != inner_nesting - 1)
    {
        txt_link->go_prev_node();
    }

    // begin || else || next command (if without else)
    txt_link->go_next_node();

    // end
    if (txt_link->get_node().s_type() == Token::END_KEYWORD) {
        // next of end
        txt_link->go_next_node();
    }

    // Main cycle
    goto mc;


}