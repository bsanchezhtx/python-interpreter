#pragma once

#include "token.hpp"
#include "ast.hpp"

class Parser
{
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<StmtPtrVariant> parse();
};