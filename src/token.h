#pragma once
#include "enum.h"

class Token
{
    private:
    public:
        TokenType type;
        std::string lexeme;
        std::string literal;
        int line;
        Token(TokenType type, std::string lexeme, std::string literal, int line);
};

std::string tokenToString(Token token);