#pragma once

#include <string>


struct SymbolTableRecInt
{

   std::string symbol;
   int  num;
   bool is_const;

    SymbolTableRecInt(std::string symbol_, int num_, bool is_const_ = false)
        :   symbol(symbol_), num(num_), is_const(is_const_)
    {}  
};

struct SymbolTableRecDouble
{
   std::string symbol;
   double  num;
   bool is_const;

    SymbolTableRecDouble(std::string symbol_, double num_, bool is_const_ = false)
        :   symbol(symbol_), num(num_), is_const(is_const_)
    {}  
};


