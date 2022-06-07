#include "code_runner.h"



SymbolTableRec<int>* CodeRunner::get_var_int(Token symbol)
{
    if (symbol_table_int->Find(symbol.get_text()) != nullptr) {
        return symbol_table_int->Find(symbol.get_text());

    }
    else {
        return nullptr;
    }
}


SymbolTableRec<double>* CodeRunner::get_var_double(Token symbol)
{
    if (symbol_table_double->Find(symbol.get_text()) != nullptr) {

        return symbol_table_double->Find(symbol.get_text());
    }
    else {
        return nullptr;
    }
}


void CodeRunner::get_var(Token var, SymbolTableRec<int>** var_int, SymbolTableRec<double>** var_double)
{
    *var_int = get_var_int(var);
    *var_double = get_var_double(var);
    return;
}

void CodeRunner::set_var_int(Token symbol, int num, bool is_set, bool is_const)
{
SymbolTableRec<int> tmp(SymbolTableRec<int>(symbol.get_text(), num, is_const));
tmp.is_set = true;
symbol_table_int->Insert(symbol.get_text(), tmp);
if (symbol_table_int->Find(symbol.get_text())->is_const != true) {
    symbol_table_int->Find(symbol.get_text())->num = num;
}
else {
    err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
}
}

void CodeRunner::set_var_double(Token symbol, double num, bool is_set, bool is_const)
{
    SymbolTableRec<double> tmp(SymbolTableRec<double>(symbol.get_text(), num, is_const));
    tmp.is_set = true;
    symbol_table_double->Insert(symbol.get_text(), tmp);
    if (symbol_table_double->Find(symbol.get_text())->is_const != true) {
        symbol_table_double->Find(symbol.get_text())->num = num;
    }
    else {
        err->push(symbol.get_line_num(), progError::k_CHANGED_CONST_VALUE, true);
    }
}

void CodeRunner::set_var(Token var, double value, bool is_set, bool is_const)
{
    get_var(var, &var_int, &var_double);
    if (var_int != nullptr) {
        set_var_int(var, (int)value, is_set, is_const);
    }
    else {
        set_var_double(var, value, is_set, is_const);
    }
}

bool CodeRunner::is_operation(Token symbol)
{
    switch (symbol.s_type()) {
    case Token::AND_OPERATOR: case Token::ASSIGN_OPERATOR: case Token::DIVIDE_OPERATOR:
    case Token::DIV_OPERATOR: case Token::EQUALS_RELATION_OPERATOR:
    case Token::GREATER_OR_EQUALS_RELATIONAL_OPERATOR: case Token::GREATER_RELATIONAL_OPERATOR:
    case Token::LESS_OR_EQUALS_RELATIONAL_OPERATOR: case Token::LESS_RELATIONAL_OPERATOR:
    case Token::MINUS_OPERATOR: case Token::PLUS_OPERATOR: case Token::OR_OPERATOR:
    case Token::NOT_EQUALS_RELATIONAL_OPERATOR: case Token::MULTIPLY_OPERATOR: case Token::MOD_OPERATOR:
        return true;
    }
    return false;

}


void CodeRunner::Start()
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
        txt_link->go_next_node();
    }

    // Var block
    if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
        txt_link->go_next_node();
    }

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
                is_assign = true;
            }

            // Value
            if (is_assign) {
                std::vector<Token> to_postfix;
                do {
                    txt_link->go_next_node();
                    if (txt_link->get_node().s_type() == Token::SEMICOLON) {
                        break;
                    }
                    if
                    (
                        (txt_link->get_node().s_type() == Token::ASSIGN_OPERATOR) ||
                        (txt_link->get_node().s_type() == Token::EQUALS_RELATION_OPERATOR)
                    )
                    {
                        err->push(txt_link->get_node().get_line_num(), progError::k_INCORRECT_OPERATION, true);
                        return;
                    }
                    to_postfix.push_back(txt_link->get_node());
                } while (txt_link->get_node().s_type() != Token::SEMICOLON);
                op.set_infix(to_postfix);
                op.to_postfix();
                set_var(var, op.calculate(symbol_table_int, symbol_table_double));
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

            // Out parameters
            std::string text;

            int order_to_out = 0;
            var_int = nullptr;
            var_double = nullptr;

            while (txt_link->get_node().s_type() != Token::RSBRACE) {
                txt_link->go_next_node();
                if (txt_link->get_node().s_type() == Token::STRING_LITERAL) {
                    if (!order_to_out) {
                        order_to_out = 1;
                    }
                    text = txt_link->get_node().get_text();
                }
                if (txt_link->get_node().s_type() == Token::VAR_DEFINITION_KEYWORD) {
                    if (!order_to_out) {
                        order_to_out = 2;
                    }
                    get_var(txt_link->get_node(), &var_int, &var_double);
                }
                // Operation in write
                if (is_operation(txt_link->get_node())) {
                    err->push(txt_link->get_node().get_line_num(), progError::k_INCORRECT_WRITE_CALL, true);
                    return;
                }
            }

            // Write Realization
            if (order_to_out == 1) {
                if (var_int != nullptr) {
                    std::cout << text << var_int->num << std::endl;
                }
                else if (var_double != nullptr) {
                    std::cout << text << var_double->num << std::endl;
                }
                else {
                    std::cout << text << std::endl;
                }
            }
            if (order_to_out == 2) {
                if (var_int != nullptr) {
                    std::cout <<  var_int->num << text << std::endl;
                }
                else {
                    std::cout << var_double->num <<  text << std::endl;
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
// Argument count
            txt_link->go_next_node();

            if (txt_link->get_node().s_type() == Token::USER_KEY_WORD) {
                // Read realization
                get_var(txt_link->get_node(), &var_int, &var_double);
                if (var_int != nullptr) {
                    int num;
                    std::cin >> num;
                    set_var_int(txt_link->get_node(), num, true, false);
                }
                if (var_double != nullptr) {
                    double num;
                    std::cin >> num;
                    set_var_double(txt_link->get_node(), num, true, false);
                }
            }

            // )
            txt_link->go_next_node();

            // ;
            txt_link->go_next_node();
            continue;
        }


        // IF 
        if (txt_link->get_node().s_type() == Token::IF_HEADING) {


            int equal_type = 0;
            const int equal = 1;
            const int not_equal = 2;
            vector <Token> left_equal;
            vector <Token> right_equal;
            txt_link->go_next_node();

            while(txt_link->get_node().s_type() != Token::THEN_KEYWORD)
            {
                if (txt_link->get_node().s_type() == Token::EQUALS_RELATION_OPERATOR)
                    break;
                if (txt_link->get_node().s_type() == Token::NOT_EQUALS_RELATIONAL_OPERATOR)
                    break;

                left_equal.push_back(txt_link->get_node());
                txt_link->go_next_node();
            }
                

            if (txt_link->get_node().s_type() == Token::EQUALS_RELATION_OPERATOR)
            {
                equal_type = equal;
                txt_link->go_next_node();
            }
            if (txt_link->get_node().s_type() == Token::NOT_EQUALS_RELATIONAL_OPERATOR)
            {
                equal_type = not_equal;
                txt_link->go_next_node();
            }

            if (equal_type) {
                do {
                    right_equal.push_back(txt_link->get_node());
                    txt_link->go_next_node();
                } while (txt_link->get_node().s_type() != Token::THEN_KEYWORD);
            }

            // Calculate if condition
            bool if_condition;
            double left_value;
            op.set_infix(left_equal);
            op.to_postfix();
            left_value = op.calculate(symbol_table_int, symbol_table_double);
            if (equal_type) {
                double right_value;
                op.set_infix(right_equal);
                op.to_postfix();
                right_value = op.calculate(symbol_table_int, symbol_table_double);

                // =
                if (equal_type == equal) {
                    if (right_value == left_value) {
                        if_condition = true;
                    }
                    else {
                        if_condition = false;
                    }
                }

                if (equal_type == not_equal) {
                    if (right_value != left_value) {
                        if_condition = true;
                    }
                    else {
                        if_condition = false;
                    }
                }
            }
            else {
                if (left_value <= 0) {
                    if_condition = false;
                }
                else {
                    if_condition = true;
                }
            }

            // Check if without begin
            if (if_condition) {
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
            else {
                // begin || next command
                txt_link->go_next_node();
                if (txt_link->get_node().s_type() == Token::BEGIN_KEYWORD) {
                    // END
                    txt_link->go_next_node();
                    txt_link->go_next_node();


                }
                if (txt_link->get_node().s_type() == Token::ELSE_KEYWORD) {
                    // begin || next command
                    txt_link->go_next_node();
                    if (txt_link->get_node().s_type() == Token::BEGIN_KEYWORD) {
                        // END
                        txt_link->go_next_node();
                        txt_link->go_next_node();
                    }
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