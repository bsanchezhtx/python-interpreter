#include <unordered_map>
#include <iostream>

#include "scanner.hpp"

std::unordered_map<std::string, TokenType> keywords =
    {
        {"and", TokenType::AND},
        {"or", TokenType::OR},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"while", TokenType::WHILE},
        {"None", TokenType::NONE},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}};

Scanner::Scanner(std::string source)
{
    this->source = source;
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::EoF, "", "", line));

    return tokens;
}


bool Scanner::isAtEnd()
{
    return current >= source.length();
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (source.at(current) != expected)
        return false;

    current++;
    return true;
}

char Scanner::advance()
{
    return source.at(current++);
}

char Scanner::peek()
{
    if (isAtEnd())
        return '\0';
    return source.at(current);
}

char Scanner::peekNext()
{
    if (current + 1 >= source.length())
        return '\0';
    return source.at(current + 1);
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (isAtEnd())
    {
        std::cerr << "Line " << line << ": Unterminated string!" << std::endl;
        exit(1);
    }

    advance();

    std::string value = source.substr(start + 1, current - start - 1);
    addToken(TokenType::STRING, value);
}

void Scanner::number()
{
    while (isdigit(peek()))
        advance();

    // currently, only working with integers, so just add the integer token
    addToken(TokenType::INTEGER, source.substr(start, current - start));
}

void Scanner::identifier()
{
    while (isalnum(peek()))
        advance();

    std::string text = source.substr(start, current - start);

    // by default, assume it is a user defined intentifier
    TokenType type = TokenType::IDENTIFIER;

    // if the text is matched to a keyword in the hash map, change token type
    if (keywords.count(text) > 0)
    {
        type = keywords[text];
    }

    addToken(type);
}

void Scanner::addToken(TokenType type)
{
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c)
    {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case ':':
        addToken(TokenType::COLON);
        break;

    // comments
    case '#':
        // A comment goes until the end of the line.
        while (peek() != '\n' && !isAtEnd())
            advance();
        break;

    // whitespace and carriage returns
    // TODO: Handle Indentation for nested statements
    case ' ':
    case '\r':
    case '\t':
        break;

    // newlines
    case '\n':
        line++;
        break;

    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        addToken(TokenType::SLASH);
        break;
    case '"':
        string();
        break;

    default:
        if (isdigit(c))
        {
            number();
        }
        else if (isalpha(c))
        {
            identifier();
        }
        else
        {
            // TODO: implement proper error handling
            std::cerr << "Line " << line << ": Unexpected character!" << std::endl;
            exit(1);
        }
        break;
    }
}

