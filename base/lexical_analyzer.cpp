#include "lexical_analyzer.h"

void LexicalAnalyzer::del_garb()
{
    std::string str;
    std::getline(*source_code, str, '\n');

}