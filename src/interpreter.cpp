#include "enum.h"
#include "interpreter.h"
#include "token.h"

void Interpreter::interpret(std::string source)
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    for (auto& token : tokens)
    {
        std::cout << tokenToString(token) << std::endl;
    }
}

Interpreter::Interpreter()
{
    this->hasError = false;
}

void Interpreter::interpretFile(char *fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    std::stringstream buffer;
    buffer << input.rdbuf();
    interpret(buffer.str());

    if (this->hasError)
    {
        exit(1);
    }
}

void Interpreter::interactivePrompt()
{
    std::string str;

    for (;;)
    {
        std::cout << "> ";
        std::getline(std::cin, str);
        if (str.empty())
            break;
        interpret(str);
    }
}