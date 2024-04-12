#include <optional>

#include "parser.hpp"
#include "ast.hpp"

Parser::Parser(const std::vector<Token> &tokens)
{
    this->tokens = tokens;
}

std::vector<StmtPtrVariant> Parser::parse()
{
    start();
    return std::move(this->statements);
}

void start()
{
    
}

bool Parser::isAtEnd()
{
    return peek().getType() == TokenType::EoF;
}

bool Parser::check(TokenType type)
{
    if (isAtEnd())
    {
        return false;
    }

    return type == peek().getType();
}

bool Parser::match(std::initializer_list<TokenType> &types)
{
    bool result = false;
    for (auto &type : types)
    {
        result = (result || check(type));
    }

    return result;
}

Token Parser::advance()
{
    if (!isAtEnd())
    {
        current++;
    }
    return previous();
}

Token Parser::peek()
{
    return tokens.at(current);
}

Token Parser::previous()
{
    return tokens.at(current - 1);
}

void Parser::consume(TokenType type)
{
    if (peek().getType() == type)
        advance();
}
