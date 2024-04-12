/*
    code and solution to use unique_ptr adapted from https://github.com/aakshintala/cpplox/blob/master/cpplox/AST/NodeTypes.h
*/

#pragma once

#include <memory>
#include <variant>
#include <vector>
#include <optional>

#include "token.hpp"

// parent class that all other expression will be derived from
class Expr
{
public:
    explicit Expr() = default;
    virtual ~Expr() = default;
    Expr(const Expr &) = delete;
    auto operator=(const Expr &) -> Expr & = delete;
    Expr(Expr &&) = delete;
    auto operator=(Expr &&) -> Expr & = delete;
};

// class prototypes for each expression type
class LiteralExpr;
class BinaryExpr;
class UnaryExpr;
class GroupingExpr;
class AssignmentExpr;
class FunctionExpr;
class CallExpr;
class ConditionalExpr;
class LogicalExpr;

using LiteralExprPtr = std::unique_ptr<LiteralExpr>;
using BinaryExprPtr = std::unique_ptr<BinaryExpr>;
using UnaryExprPtr = std::unique_ptr<UnaryExpr>;
using GroupingExprPtr = std::unique_ptr<GroupingExpr>;
using AssignmentExprPtr = std::unique_ptr<AssignmentExpr>;
using FuncExprPtr = std::unique_ptr<FunctionExpr>;
using CallExprPtr = std::unique_ptr<CallExpr>;
using ConditionalExprPtr = std::unique_ptr<ConditionalExpr>;
using LogicalExprPtr = std::unique_ptr<LogicalExpr>;

// variant to pass pointers to different expression types
using ExprPtrVariant = std::variant<LiteralExprPtr, BinaryExprPtr, UnaryExprPtr, GroupingExprPtr,
                                    AssignmentExprPtr, FuncExprPtr, CallExprPtr, ConditionalExprPtr,
                                    LogicalExprPtr>;

// class prototypes for statement types, will be used in functions
class ExprStmt;
class PrintStmt;
class BlockStmt;
class VarStmt;
class IfStmt;
class WhileStmt;
class ForStmt;
class FuncStmt;
class RetStmt;
class ClassStmt;

using ExprStmtPtr = std::unique_ptr<ExprStmt>;
using PrintStmtPtr = std::unique_ptr<PrintStmt>;
using BlockStmtPtr = std::unique_ptr<BlockStmt>;
using VarStmtPtr = std::unique_ptr<VarStmt>;
using IfStmtPtr = std::unique_ptr<IfStmt>;
using WhileStmtPtr = std::unique_ptr<WhileStmt>;
using ForStmtPtr = std::unique_ptr<ForStmt>;
using FuncStmtPtr = std::unique_ptr<FuncStmt>;
using RetStmtPtr = std::unique_ptr<RetStmt>;
using ClassStmtPtr = std::unique_ptr<ClassStmt>;

// variant to pass around pointers to different statement types
using StmtPtrVariant = std::variant<ExprStmtPtr, PrintStmtPtr, BlockStmtPtr, VarStmtPtr,
                                    IfStmtPtr, WhileStmtPtr, ForStmtPtr, FuncStmtPtr, RetStmtPtr,
                                    ClassStmtPtr>;

/*

    Helper functions to create PtrVariants

*/

// ExprPtrVariants for each statement
ExprPtrVariant createLiteralEPV(Literal literal);
ExprPtrVariant createBinaryEPV(ExprPtrVariant left, Token op, ExprPtrVariant right);
ExprPtrVariant createUnaryEPV(Token op, ExprPtrVariant right);
ExprPtrVariant createGroupingEPV(ExprPtrVariant right);
ExprPtrVariant createAssignmentEPV(Token varName, ExprPtrVariant expr);
ExprPtrVariant createFunctionEPV(std::vector<Token> params, std::vector<StmtPtrVariant> fnBody);
ExprPtrVariant createCallEPV(ExprPtrVariant callee, Token paren, std::vector<ExprPtrVariant> arguments);
ExprPtrVariant createConditionalEPV(ExprPtrVariant condition, ExprPtrVariant then, ExprPtrVariant elseBranch);

// StmtPtrVariants for each statement type
StmtPtrVariant createExprSPV(ExprPtrVariant expr);
StmtPtrVariant createPrintSPV(ExprPtrVariant expr);
StmtPtrVariant createBlockSPV(std::vector<StmtPtrVariant> statements);
StmtPtrVariant createVarSPV(Token varName, std::optional<ExprPtrVariant> initializer);
StmtPtrVariant createIfSPV(ExprPtrVariant condition, StmtPtrVariant thenBranch, std::optional<StmtPtrVariant> elseBranch);
StmtPtrVariant createWhileSPV(ExprPtrVariant condition, StmtPtrVariant loopBody);
StmtPtrVariant createForSPV(std::optional<StmtPtrVariant> initializer,
                            std::optional<ExprPtrVariant> condition,
                            std::optional<ExprPtrVariant> increment,
                            StmtPtrVariant loopBody);
StmtPtrVariant createFuncSPV(Token fName, FuncExprPtr funcExpr);
StmtPtrVariant createRetSPV(Token ret, std::optional<ExprPtrVariant> value);
StmtPtrVariant createClassSPV(Token className, std::optional<ExprPtrVariant> superClass, std::vector<StmtPtrVariant> methods);

/*

    Expression class definitions

*/
class LiteralExpr final : public Expr
{
public:
    Literal val;
    LiteralExpr(Literal val);
};

class BinaryExpr final : public Expr
{
public:
    ExprPtrVariant left;
    Token op;
    ExprPtrVariant right;
    BinaryExpr(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

class UnaryExpr final : public Expr
{
public:
    Token op;
    ExprPtrVariant right;
    UnaryExpr(Token op, ExprPtrVariant right);
};

class GroupingExpr final : public Expr
{
public:
    ExprPtrVariant expr;
    GroupingExpr(ExprPtrVariant expr);
};

class AssignmentExpr final : public Expr
{
public:
    Token name;
    ExprPtrVariant right;
    AssignmentExpr(Token name, ExprPtrVariant right);
};

class FunctionExpr final : public Expr
{
public:
    std::vector<Token> parameters;
    std::vector<StmtPtrVariant> body;
    FunctionExpr(std::vector<Token> parameters, std::vector<StmtPtrVariant> body);
};

class CallExpr final : public Expr
{
public:
    ExprPtrVariant callee;
    Token paren;
    std::vector<ExprPtrVariant> arguments;
    CallExpr(ExprPtrVariant callee, Token paren,
             std::vector<ExprPtrVariant> arguments);
};

class ConditionalExpr final : public Expr
{
public:
    ExprPtrVariant condition;
    ExprPtrVariant thenBranch;
    ExprPtrVariant elseBranch;
    ConditionalExpr(ExprPtrVariant condition, ExprPtrVariant thenBranch,
                    ExprPtrVariant elseBranch);
};

class LogicalExpr final : public Expr
{
public:
    ExprPtrVariant left;
    Token op;
    ExprPtrVariant right;
    LogicalExpr(ExprPtrVariant left, Token op, ExprPtrVariant right);
};

/*

     Statement class definitions

*/

class ExprStmt final : public Expr
{
public:
    ExprPtrVariant expression;
    explicit ExprStmt(ExprPtrVariant expr);
};

class PrintStmt final : public Expr
{
public:
    ExprPtrVariant expression;
    explicit PrintStmt(ExprPtrVariant expression);
};

class BlockStmt final : public Expr
{
public:
    std::vector<StmtPtrVariant> statements;
    explicit BlockStmt(std::vector<StmtPtrVariant> statements);
};

class VarStmt final : public Expr
{
public:
    Token varName;
    std::optional<ExprPtrVariant> initializer;
    explicit VarStmt(Token varName, std::optional<ExprPtrVariant> initializer);
};

class IfStmt final : public Expr
{
public:
    ExprPtrVariant condition;
    StmtPtrVariant thenBranch;
    std::optional<StmtPtrVariant> elseBranch;
    explicit IfStmt(ExprPtrVariant condition, StmtPtrVariant thenBranch,
                    std::optional<StmtPtrVariant> elseBranch);
};

class WhileStmt final : public Expr
{
public:
    ExprPtrVariant condition;
    StmtPtrVariant loopBody;
    explicit WhileStmt(ExprPtrVariant condition, StmtPtrVariant loopBody);
};

class ForStmt final : public Expr
{
public:
    std::optional<StmtPtrVariant> initializer;
    std::optional<ExprPtrVariant> condition;
    std::optional<ExprPtrVariant> increment;
    StmtPtrVariant loopBody;
    explicit ForStmt(std::optional<StmtPtrVariant> initializer,
                     std::optional<ExprPtrVariant> condition,
                     std::optional<ExprPtrVariant> increment,
                     StmtPtrVariant loopBody);
};

class FuncStmt : public Expr
{
public:
    Token funcName;
    FuncExprPtr funcExpr;
    FuncStmt(Token funcName, FuncExprPtr funcExpr);
};

class RetStmt : public Expr
{
public:
    Token ret;
    std::optional<ExprPtrVariant> value;
    RetStmt(Token ret, std::optional<ExprPtrVariant> value);
};

class ClassStmt : public Expr
{
public:
    Token className;
    std::optional<ExprPtrVariant> superClass;
    std::vector<StmtPtrVariant> methods;
    ClassStmt(Token className, std::optional<ExprPtrVariant> superClass,
              std::vector<StmtPtrVariant> methods);
};