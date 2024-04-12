#pragma once

#include <string>
#include <variant>

class Literal {
    public:
        std::variant<std::string, int> get();
        void assign(const int& num);
        void assign(const std::string& str);
    private:
        std::variant<std::string, int> literal;
};