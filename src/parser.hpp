#pragma once

#include <initializer_list>

#include "token.hpp"
#include "ast.hpp"

class Parser
{
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<StmtPtrVariant> parse();
private:
    std::vector<Token> tokens;
    std::vector<StmtPtrVariant> statements;
    int current = 0;

    // 'rules' for parsing expressions
    void start();
    

    // helper functions
    bool isAtEnd();
    bool check(TokenType type);
    bool match(std::initializer_list<TokenType>& types);
    Token advance();
    Token peek();
    Token previous();
    void consume(TokenType type);
};