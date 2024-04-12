#pragma once

#include <string>
#include <vector>

#include "ast.hpp"

class PrettyPrinter
{
public:
    static std::vector<std::string> toString (const std::vector<StmtPtrVariant>& statements);
    static std::vector<std::string> toString (const StmtPtrVariant& statement);
    static std::string toString (const ExprPtrVariant& expr);
};