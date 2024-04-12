#pragma once

#include <vector>

#include "token.hpp"
#include "ast.hpp"

class Interpreter
{
public:
    Interpreter();
    void interpretFile(const char *fileName);
    void interactivePrompt();

private:
    void interpret(const std::string& source);
    std::vector<Token> scan(const std::string& source);
    std::vector<StmtPtrVariant> parse(const std::vector<Token>& tokenVec);
    bool hasError = false;
};