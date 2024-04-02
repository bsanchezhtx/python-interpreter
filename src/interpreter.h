#pragma once
#include "enum.h"
#include "token.h"
#include "scanner.h"

class Interpreter
{
private:
    bool hasError;
    void interpret(std::string source);

public:
    Interpreter();
    void interpretFile(char *fileName);
    void interactivePrompt();
    // void error(int line, std::string message);
    // void report(int line, std::string where, std::string message);
};