#pragma once

#include <fstream>
#include <string>
#include <system_error>

#include "compiler_config.h"
#include "error_handler.h"

class Interface {

private:

    ErrorHandler *err;
    compiler_parameters* prs;
    double compl_version;
    std::string path;

    void help()
    {
        cout << "Team ADA Pascal compiler" << std::endl;
        cout << "Usage: pascal [-l] [-s] [--help] [-v] file_name" << std::endl;
        cout << "  -l - lexical analysis only" << std::endl;
        cout << "  -s - syntax analysis only" << std::endl;
        cout << "  -v - print program version" << std::endl;
        cout << "  --help - print help page" << std::endl;
    }

public:

    Interface
    (
        ErrorHandler* _err,
        compiler_parameters* _prs,
        double compl_version_
    ) : err(_err), prs(_prs), compl_version(compl_version_)
    {}

    void printer()
    {
        if(prs->pr_version) {
            cout << "Compiler version: " << compl_version << std::endl;
        }
        
        // if (err.error_cnt()) {
        //     cout << path <<  std::endl;
        //     err.print_errors();
        // }

        if(prs->pr_help) {
            help();
        }


    }


    inline void set_path(std::string _path)
    {
        path = _path;
    }

    void no_file_dialog()
    {
        cout << "fatal error: no input file" << std::endl;  
        cout << "commpilation terminated" << std::endl;  
    }

    void error_file_dialog()
    {
        cout << "fatal error: error open file " << path << std::endl;
        cout << "commpilation terminated" << std::endl;  
  
    }

    void print_file_dialog(std::ifstream* src_code)
    {
        std::cout << "Enter path to source code file" << std::endl;
        std::getline(std::cin, path);
        src_code = new std::ifstream (path);
        system("cls");
    }

};