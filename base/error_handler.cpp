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
    std::cout << " CODE ";
    std::cout << " LINE ";
    std::cout << " ERROR MESSAGE\n";
}
void ErrorHandler::print_cur_error(size_t cur_pos)
{
    std::cout << ' ';
    std::cout << errors[cur_pos].error_num;
    int gap_counter = 6;// string "CODE "
    gap_counter -= get_symbol_quan(errors[cur_pos].error_num);
    for (; gap_counter > 0; gap_counter--) {
        std::cout << ' ';
    }
    std::cout << errors[cur_pos].line_num;
    gap_counter = 5;// string "LINE "
    gap_counter -= get_symbol_quan(errors[cur_pos].line_num);
    for (; gap_counter > 0; gap_counter--) {
        std::cout << ' ';
    }
    if (errors[cur_pos].is_critical) {
        std::cout << "ERROR: ";
    }
    else {
        std::cout << "WARNING: ";
    }
    std::cout << comment[errors[cur_pos].error_num] << '\n';
}
//void ErrorHandler::print_errors()
//{
//    print_head();
//    for (size_t i = 0; i < errors.size(); i++) {
//        print_cur_error(i);
//    }
//}
//void ErrorHandler::push(int line_num, progError error_num, bool is_critical)
//{
//    errors.push_back(ErrorParam(line_num, error_num, is_critical));
//}

//int ErrorHandler::condition()
//{
//    if (errors.size() == 0)
//        return 0;
//    for (int i = 0; i < errors.size(); i++)
//        if (errors[i].is_critical)
//            return 2;
//    return 1;
//}