#pragma once

#include "token.hpp"
#include "interpreter.hpp"

class Scanner
{
public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    void scanToken();
    char advance();
    bool match(char expected);
    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);
    void addToken(TokenType type, int literal);
    char peek();
    char peekNext();
    void number();
    void string();
    void identifier();
};