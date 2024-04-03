#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

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

std::string tokenTypeToString(TokenType token);