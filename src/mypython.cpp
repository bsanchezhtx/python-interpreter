/*
    Team 27
    Code adapted from https://craftinginterpreters.com/contents.html
*/

#include <iostream>

#include "interpreter.hpp"

int main(int argc, char *argv[])
{
    Interpreter interpreter;

    if (argc > 2)
    {
        std::cout << "Usage: ./mypython {file_name}.py" << std::endl;
        exit(1);
    }
    else if (argc == 2)
    {
        interpreter.interpretFile(argv[1]);
    }
    else
    {
        interpreter.interactivePrompt();
    }

    return 0;
}