#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// error handling
void report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error " << where << ": " << message << std::endl;
}

void error(int line, std::string message)
{
    report(line, "", message);
}

// TODO: make this actually interpret the python code
void interpret(std::string source)
{
    std::cout << source << std::endl;
}

// reads a file and interprets the code
void interpretFile(char *fileName)
{
    std::ifstream input(fileName, std::ios::binary);
    std::stringstream buffer;
    buffer << input.rdbuf();
    interpret(buffer.str());
}

// runs the interpreter in 'interactive mode'
void interactivePrompt()
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

int main(int argc, char *argv[])
{
    // checks arguments
    if (argc > 2)
    {
        std::cout << "Usage: ./mypython {script}" << std::endl;
        exit(0);
    }
    else if (argc == 2)
    {
        interpretFile(argv[1]);
    }
    else
    {
        interactivePrompt();
    }

    return 0;
}