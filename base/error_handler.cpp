#include "error_handler.h"

int ErrorHandler::get_symbol_quan(size_t num)
{
    int quan = 0;
    while (num > 0) {
        num /= 10;
        quan++;
    }
    return quan;
}
void ErrorHandler::print_head()
{
    cout << " CODE ";
    cout << " LINE ";
    cout << " ERROR MESSAGE\n";
}
void ErrorHandler::print_cur_error(size_t cur_pos)
{
    cout << ' ';
    cout << errors[cur_pos].error_num;
    int gap_counter = 6;// string "CODE "
    gap_counter -= get_symbol_quan(errors[cur_pos].error_num);
    for (; gap_counter > 0; gap_counter--) {
        cout << ' ';
    }
    cout << errors[cur_pos].line_num;
    gap_counter = 6;// string "LINE "
    gap_counter -= get_symbol_quan(errors[cur_pos].line_num);
    for (; gap_counter > 0; gap_counter--) {
        cout << ' ';
    }
    if (errors[cur_pos].is_critical) {
        cout << "ERROR: ";
    }
    else {
        cout << "WARNING: ";
    }
    cout << comment[errors[cur_pos].error_num] << '\n';
}
void ErrorHandler::print_errors()
{
    print_head();
    for (size_t i = 0; i < errors.size(); i++) {
        print_cur_error(i);
    }
}
void ErrorHandler::push(size_t line_num, progError error_num, bool is_critical)
{
    ErrorParam extra(line_num, error_num, is_critical);
    push(extra);
}
void ErrorHandler::push(ErrorParam err)
{
    errors.push_back(err);
    //if (size + 1 > buff) {
    //    ErrorParam* tmp = new ErrorParam[size];
    //    for (int i = 0; i < size; i++)
    //        tmp[i] = errors[i];
    //    tmp[size] = err;
    //    delete[] errors;
    //    buff = buff << 1;//multyplying buffer by two
    //    errors = new ErrorParam[buff];
    //    size++;
    //    for (int i = 0; i < size; i++) {
    //        errors[i] = tmp[i];
    //    }
    //    delete[]tmp;
    //}
    //else {
    //    errors[size] = err;
    //    size++;
    //}
}

int ErrorHandler::condition()
{
    if (errors.size() == 0)
        return 0;
    for (int i = 0; i < errors.size(); i++)
        if (errors[i].is_critical)
            return 2;
    return 1;
}