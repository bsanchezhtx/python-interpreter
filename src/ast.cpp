/*
    code and solution to use unique_ptr adapted from https://github.com/aakshintala/cpplox/blob/master/cpplox/AST/NodeTypes.h
*/

#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "ast.hpp"

/*

    Expression constructor definitions

*/

LiteralExpr::LiteralExpr(Literal val)
    : val(std::move(val)) {}

BinaryExpr::BinaryExpr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

UnaryExpr::UnaryExpr(Token op, ExprPtrVariant right)
    : op(std::move(op)), right(std::move(right)) {}

GroupingExpr::GroupingExpr(ExprPtrVariant expr)
    : expr(std::move(expr)) {}

AssignmentExpr::AssignmentExpr(Token name, ExprPtrVariant right)
    : name(std::move(name)), right(std::move(right)) {}

FunctionExpr::FunctionExpr(std::vector<Token> parameters,
                           std::vector<StmtPtrVariant> body)
    : parameters(std::move(parameters)), body(std::move(body)) {}

CallExpr::CallExpr(ExprPtrVariant callee, Token paren,
                   std::vector<ExprPtrVariant> arguments)
    : callee(std::move(callee)),
      paren(std::move(paren)),
      arguments(std::move(arguments)) {}

ConditionalExpr::ConditionalExpr(ExprPtrVariant condition,
                                 ExprPtrVariant thenBranch,
                                 ExprPtrVariant elseBranch)
    : condition(std::move(condition)),
      thenBranch(std::move(thenBranch)),
      elseBranch(std::move(elseBranch)) {}

LogicalExpr::LogicalExpr(ExprPtrVariant left, Token op, ExprPtrVariant right)
    : left(std::move(left)), op(std::move(op)), right(std::move(right)) {}

/*

    Function implementation for expression helpers

*/

ExprPtrVariant createLiteralEPV(Literal literal)
{
    return std::make_unique<LiteralExpr>(std::move(literal));
}

ExprPtrVariant createBinaryEPV(ExprPtrVariant left, Token op, ExprPtrVariant right)

{
    return std::make_unique<BinaryExpr>(std::move(left), op, std::move(right));
}

ExprPtrVariant createUnaryEPV(Token op, ExprPtrVariant right)
{
    return std::make_unique<UnaryExpr>(op, std::move(right));
}

ExprPtrVariant createGroupingEPV(ExprPtrVariant right)
{
    return std::make_unique<GroupingExpr>(std::move(right));
}

ExprPtrVariant createAssignmentEPV(Token varName, ExprPtrVariant expr)
{
    return std::make_unique<AssignmentExpr>(varName, std::move(expr));
}

ExprPtrVariant createFunctionEPV(std::vector<Token> params, std::vector<StmtPtrVariant> fnBody)
{
    return std::make_unique<FunctionExpr>(std::move(params), std::move(fnBody));
}

ExprPtrVariant createCallEPV(ExprPtrVariant callee, Token paren, std::vector<ExprPtrVariant> arguments)
{
    return std::make_unique<CallExpr>(std::move(callee), std::move(paren),
                                      std::move(arguments));
}

ExprPtrVariant createConditionalEPV(ExprPtrVariant condition, ExprPtrVariant then, ExprPtrVariant elseBranch)
{
    return std::make_unique<ConditionalExpr>(
        std::move(condition), std::move(then), std::move(elseBranch));
}

ExprPtrVariant createLogicalEPV(ExprPtrVariant left, Token op, ExprPtrVariant right)
{
    return std::make_unique<LogicalExpr>(std::move(left), op, std::move(right));
}

/*

    Statement constructor definitions

*/

ExprStmt::ExprStmt(ExprPtrVariant expr) : expression(std::move(expr)) {}

PrintStmt::PrintStmt(ExprPtrVariant expr) : expression(std::move(expr)) {}

BlockStmt::BlockStmt(std::vector<StmtPtrVariant> statements)
    : statements(std::move(statements)) {}

VarStmt::VarStmt(Token varName, std::optional<ExprPtrVariant> initializer)
    : varName(std::move(varName)), initializer(std::move(initializer)) {}

IfStmt::IfStmt(ExprPtrVariant condition, StmtPtrVariant thenBranch,
               std::optional<StmtPtrVariant> elseBranch)
    : condition(std::move(condition)),
      thenBranch(std::move(thenBranch)),
      elseBranch(std::move(elseBranch)) {}

WhileStmt::WhileStmt(ExprPtrVariant condition, StmtPtrVariant loopBody)
    : condition(std::move(condition)), loopBody(std::move(loopBody)) {}

ForStmt::ForStmt(std::optional<StmtPtrVariant> initializer,
                 std::optional<ExprPtrVariant> condition,
                 std::optional<ExprPtrVariant> increment,
                 StmtPtrVariant loopBody)
    : initializer(std::move(initializer)),
      condition(std::move(condition)),
      increment(std::move(increment)),
      loopBody(std::move(loopBody)) {}

FuncStmt::FuncStmt(Token funcName, FuncExprPtr funcExpr)
    : funcName(std::move(funcName)), funcExpr(std::move(funcExpr)) {}

RetStmt::RetStmt(Token ret, std::optional<ExprPtrVariant> value)
    : ret(std::move(ret)), value(std::move(value)) {}

ClassStmt::ClassStmt(Token className, std::optional<ExprPtrVariant> superClass,
                     std::vector<StmtPtrVariant> methods)
    : className(std::move(className)),
      superClass(std::move(superClass)),
      methods(std::move(methods)) {}

/*

    Function implementations for statement helpers

*/

StmtPtrVariant createExprSPV(ExprPtrVariant expr)
{
    return std::make_unique<ExprStmt>(std::move(expr));
}

StmtPtrVariant createPrintSPV(ExprPtrVariant expr)
{
    return std::make_unique<PrintStmt>(std::move(expr));
}

StmtPtrVariant createBlockSPV(std::vector<StmtPtrVariant> statements)
{
    return std::make_unique<BlockStmt>(std::move(statements));
}

StmtPtrVariant createVarSPV(Token varName, std::optional<ExprPtrVariant> initializer)

{
    return std::make_unique<VarStmt>(varName, std::move(initializer));
}

StmtPtrVariant createIfSPV(ExprPtrVariant condition, StmtPtrVariant thenBranch, std::optional<StmtPtrVariant> elseBranch)
{
    return std::make_unique<IfStmt>(std::move(condition), std::move(thenBranch),
                                    std::move(elseBranch));
}

StmtPtrVariant createWhileSPV(ExprPtrVariant condition, StmtPtrVariant loopBody)

{
    return std::make_unique<WhileStmt>(std::move(condition), std::move(loopBody));
}

StmtPtrVariant createForSPV(std::optional<StmtPtrVariant> initializer,
                            std::optional<ExprPtrVariant> condition,
                            std::optional<ExprPtrVariant> increment,
                            StmtPtrVariant loopBody)
{
    return std::make_unique<ForStmt>(std::move(initializer), std::move(condition),
                                     std::move(increment), std::move(loopBody));
}

StmtPtrVariant createFuncSPV(Token fName, FuncExprPtr funcExpr)
{
    return std::make_unique<FuncStmt>(std::move(fName), std::move(funcExpr));
}

StmtPtrVariant createRetSPV(Token ret, std::optional<ExprPtrVariant> value)

{
    return std::make_unique<RetStmt>(std::move(ret), std::move(value));
}

StmtPtrVariant createClassSPV(Token className, std::optional<ExprPtrVariant> superClass, std::vector<StmtPtrVariant> methods)
{
    return std::make_unique<ClassStmt>(std::move(className),
                                       std::move(superClass), std::move(methods));
}
