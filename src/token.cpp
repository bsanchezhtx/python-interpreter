#include "token.hpp"

std::string tokenTypeToString(const TokenType &token)
{
    switch (token)
    {
    case TokenType::LEFT_PAREN:
        return "LEFT_PAREN";
    case TokenType::RIGHT_PAREN:
        return "RIGHT_PAREN";
    case TokenType::COMMA:
        return "COMMA";
    case TokenType::DOT:
        return "DOT";
    case TokenType::MINUS:
        return "MINUS";
    case TokenType::PLUS:
        return "PLUS";
    case TokenType::SLASH:
        return "SLASH";
    case TokenType::STAR:
        return "STAR";
    case TokenType::COLON:
        return "COLON";
    case TokenType::HASH:
        return "COMMENT";
    case TokenType::INDENT:
        return "INDENT";
    case TokenType::DEDENT:
        return "DEDENT";
        

    case TokenType::NOT:
        return "NOT";
    case TokenType::EQUAL:
        return "EQUAL";
    case TokenType::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case TokenType::GREATER:
        return "GREATER";
    case TokenType::GREATER_EQUAL:
        return "GREATER_EQUAL";
    case TokenType::LESS:
        return "LESS";
    case TokenType::LESS_EQUAL:
        return "LESS_EQUAL";

    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::STRING:
        return "STRING";
    case TokenType::INTEGER:
        return "INTEGER";

    case TokenType::AND:
        return "AND";
    case TokenType::OR:
        return "OR";
    case TokenType::IF:
        return "IF";
    case TokenType::ELSE:
        return "ELSE";
    case TokenType::TRUE:
        return "TRUE";
    case TokenType::FALSE:
        return "FALSE";
    case TokenType::FOR:
        return "FOR";
    case TokenType::WHILE:
        return "WHILE";
    case TokenType::NONE:
        return "NONE";
    case TokenType::PRINT:
        return "PRINT";
    case TokenType::RETURN:
        return "RETURN";

    case TokenType::EoF:
        return "EOF";

    default:
        return "Unrecognized Token Type";
        break;
    }
};

Token::Token(TokenType type, std::string lexeme, std::string literal, int line)
{
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

Token::Token(TokenType type, std::string lexeme, int literal, int line)
{
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

Token::Token(TokenType type, std::string lexeme, int line)
{
    this->type = type;
    this-> lexeme = lexeme;
    this->line = line;
}

std::string Token::toString()
{
    return tokenTypeToString(type) + " " + lexeme;
}