#pragma once
#include "enum.h"
#include "token.h"
#include "interpreter.h"

class Scanner
{
private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::string literal);
    bool match(char expected);
    char peek();
    void string();
    bool isDigit(char c);
    void number();
    char peekNext();
    void identifier();
    bool isAlpha(char c);
    bool isAlphaNumeric(char c);
public:
    Scanner(std::string source);
    std::vector<Token> scanTokens();
};