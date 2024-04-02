#include "scanner.h"

std::unordered_map<std::string, TokenType> keywords =
    {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}};

bool Scanner::isAtEnd()
{
    return this->current >= this->source.length();
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
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
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
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        this->line++;
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
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
        if (match('/'))
        {
            // A comment goes until the end of the line.
            while (peek() != '\n' && !isAtEnd())
                advance();
        }
        else
        {
            addToken(TokenType::SLASH);
        }
        break;
    default:
        if (isDigit(c))
        {
            number();
        }
        else if (isAlpha(c))
        {
            identifier();
        }
        else
        {
            // TODO: implement proper error handling
            std::cerr << "Line " << line << ": Unexpected character." << std::endl;
            exit(1);
        }
        break;
    }
}

char Scanner::advance()
{
    return this->source.at(this->current++);
}

void Scanner::addToken(TokenType type)
{
    addToken(type, "");
}

void Scanner::addToken(TokenType type, std::string literal)
{
    std::string text = this->source.substr(this->start, this->current);
    tokens.push_back(Token(type, text, literal, this->line));
}

bool Scanner::match(char expected)
{
    if (isAtEnd())
        return false;
    if (this->source.at(this->current) != expected)
        return false;

    this->current++;
    return true;
}

char Scanner::peek()
{
    if (isAtEnd())
        return '\0';
    return this->source.at(this->current);
}

void Scanner::string()
{
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
            this->line++;
        advance();
    }

    if (isAtEnd())
    {
        std::cerr << line << "Unterminated string." << std::endl;
        return;
    }

    advance();

    std::string value = source.substr(start + 1, current - 1);
    addToken(TokenType::STRING, value);
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

void Scanner::number()
{
    while (isDigit(peek()))
        advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext()))
    {
        // Consume the "."
        advance();

        while (isDigit(peek()))
            advance();
    }

    addToken(TokenType::NUMBER, this->source.substr(this->start, this->current));
}

char Scanner::peekNext()
{
    if (current + 1 >= source.length())
        return '\0';
    return source.at(current + 1);
}

void Scanner::identifier()
{
    while (isAlphaNumeric(peek()))
        advance();

    std::string text = this->source.substr(this->start, this->current);
    TokenType type = keywords.at(text);
    if (keywords.find(text) == keywords.end())
    {
        type = TokenType::IDENTIFIER;
    }

    addToken(type);
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

bool Scanner::isAlphaNumeric(char c)
{
    return isAlpha(c) || isDigit(c);
}

Scanner::Scanner(std::string source)
{
    this->source = source;
}

std::vector<Token> Scanner::scanTokens()
{
    while (!isAtEnd())
    {
        this->start = this->current;
        scanToken();
    }

    tokens.push_back(Token(TokenType::EoF, "", "", this->line));

    return tokens;
}