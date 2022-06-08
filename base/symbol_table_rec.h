#pragma once

#include <string>


template <class T>
struct SymbolTableRec
{

   std::string symbol;
   T  num;
   bool is_const;
   bool is_set;

    SymbolTableRec(std::string symbol_, T num_, bool is_const_, bool is_set_)
        :   symbol(symbol_), num(num_), is_const(is_const_), is_set(is_set_)
    {}  

    SymbolTableRec& operator=(SymbolTableRec& other) = default;
};