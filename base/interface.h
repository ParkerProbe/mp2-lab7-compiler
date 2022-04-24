#pragma once

#include <fstream>
#include <system_error>
#include "compiler_config.h"

class Interface {

private:

    ErrorHandler *err;
    compiler_parameters* prs;

public:

    Interface
    (
        ErrorHandler* _err,
        compiler_parameters* _prs
    ) : err(_err), prs(_prs)
    {}

    void printer() {}

    void print_file_dialog(std::ifstream* src_code);

}