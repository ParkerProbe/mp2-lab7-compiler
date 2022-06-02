#pragma once

#include <string>


template <class T>
struct SymbolTableRec
{

   std::string symbol;
   T  num;
   bool is_const;
   bool is_set;

    SymbolTableRec(std::string symbol_, int num_, bool is_const_ = false, bool is_set = true)
        :   symbol(symbol_), num(num_), is_const(is_const_)
    {}  

    SymbolTableRec& operator=(SymbolTableRec& other) = default;
};