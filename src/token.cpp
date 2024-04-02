#include "token.h"
#include "enum.h"

Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
{
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

std::string tokenToString(Token token)
{
    return tokenTypeToString(token.type) + " " + token.lexeme + " " + token.literal;
}