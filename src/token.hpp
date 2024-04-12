#pragma once

#include <string>

#include "literal.hpp"

enum class TokenType
{
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SLASH,
    STAR,
    COLON,
    HASH,
    NEWLINE,
    INDENT,
    DEDENT,

    NOT,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    IDENTIFIER,
    STRING,
    INTEGER,

    AND,
    OR,
    IF,
    ELSE,
    TRUE,
    FALSE,
    FOR,
    WHILE,
    NONE,
    PRINT,
    RETURN,

    EoF
};

class Token
{
public:
    Token(TokenType type, std::string lexeme, std::string literal, int line);
    Token(TokenType type, std::string lexeme, int literal, int line);
    Token(TokenType type, std::string lexeme, int line);
    std::string toString();
    std::string getLexeme();
    TokenType getType();

private:
    TokenType type;
    std::string lexeme;
    Literal literal;
    int line;
};