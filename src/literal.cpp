#include <string>

#include "literal.hpp"

std::variant<std::string, int> Literal::get()
{
    return literal;
}

void Literal::assign(const int& num) 
{
    literal = num;
}

void Literal::assign(const std::string& str) 
{
    literal = str;
}