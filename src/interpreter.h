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
};