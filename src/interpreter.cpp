#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "interpreter.hpp"
#include "scanner.hpp"
#include "parser.hpp"
#include "prettyprinter.hpp"

Interpreter::Interpreter()
{
    this->hasError = false;
}

void Interpreter::interpretFile(const char *fileName)
{
    try
    {
        std::ifstream input(fileName, std::ios::in);
        std::stringstream source;
        source << input.rdbuf();
        interpret(source.str());
    }
    catch(const std::exception& e)
    {
        std::cerr << "Couldn't read input file: " << e.what() << '\n';
    }
}

void Interpreter::interactivePrompt()
{
    std::string str;

    while(std::cout << "> " && std::getline(std::cin, str))
    {
        if (str.empty())
            break;
        interpret(str);
    }
}

std::vector<Token> Interpreter::scan(const std::string& source)
{
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.scanTokens();
    return tokens;
}

std::vector<StmtPtrVariant> parse(const std::vector<Token>& tokens)
{
    Parser parser(tokens);
    std::vector<StmtPtrVariant> statements = parser.parse();

    PrettyPrinter::toString(statements);

    return statements;
}


void Interpreter::interpret(const std::string& source)
{
    std::vector<Token> tokens = scan(source);
}