#include "error_handler.h"
void ErrorHandler::print_head()
{
    cout << " CODE ";
    cout << " LINE ";
    cout << " ERROR MESSAGE\n";
}
void ErrorHandler::print_cur_error()
{
    cout << errors[cur_pos].error_num;
    int gap_counter;
    int tmp_num = errors[cur_pos].error_num;
    for (int i = 0; i < 6; i++) {

    }
}
void ErrorHandler::push(size_t line_num, progError error_num, bool is_critical)
{
    ErrorParam extra(line_num, error_num, is_critical);
    if (size + 1 > buff) {
        ErrorParam* tmp = new ErrorParam[size];
        for (int i = 0; i < size; i++)
            tmp[i] = errors[i];
        tmp[size] = extra;
        delete[] errors;
        buff = buff << 1;
        errors = new ErrorParam[buff];
        size++;
        for (int i = 0; i < size; i++) {
            errors[i] = tmp[i];
        }
        delete[]tmp;
    }
    else {
        errors[size] = extra;
        size++;
    }
}