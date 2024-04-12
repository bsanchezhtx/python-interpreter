

#include "prettyprinter.hpp"

std::string parenthesize(const std::string &name, const ExprPtrVariant &expr)
{
    return "(" + name + " " + PrettyPrinter::toString(expr) + ")";
}

std::string parenthesize(const std::string &name, const ExprPtrVariant &expr1, const ExprPtrVariant &expr2)
{
    return "(" + name + " " + PrettyPrinter::toString(expr1) + " " + PrettyPrinter::toString(expr2) + ")";
}

std::string printLiteralExpr(const LiteralExprPtr &expr)
{
    return std::get<0>(expr->val.get());
}

std::string printBinaryExpr(const BinaryExprPtr &expr)
{
    return parenthesize(expr->op.getLexeme(), expr->left, expr->right);
}

std::string printUnaryExpr(const UnaryExprPtr &expr)
{
    return parenthesize(expr->op.getLexeme(), expr->right);
}

std::string printGroupingExpr(const GroupingExprPtr &expr)
{
    std::string name = "group";
    return parenthesize(name, expr->expr);
}

std::string printAssignmentExpr(const AssignmentExprPtr &expr)
{
    return parenthesize("= " + expr->name.getLexeme(), expr->right) + ";";
}

std::string printCallExpr(const CallExprPtr &expr)
{
    std::string result;
    for (size_t i = 0; i < expr->arguments.size(); ++i)
    {
        if (i > 0 && i < expr->arguments.size() - 1)
            result += ", ";
        result += "(" + PrettyPrinter::toString(expr->arguments[i]) + ")";
    }
    return parenthesize("(" + result + ")", expr->callee);
}

std::string printFunctionExpr(const FuncExprPtr &expr)
{
    std::string funcStr = "(";
    for (size_t i = 0; i < expr->parameters.size(); ++i)
    {
        if (0 != i)
            funcStr += ", ";
        funcStr += expr->parameters[i].getLexeme();
    }
    funcStr += ") {\n";
    for (auto &bodyStmt : expr->body)
    {
        for (const auto &str : PrettyPrinter::toString(bodyStmt))
        {
            funcStr += str + "\n";
        }
    }
    funcStr += "\n}";
    return funcStr;
}

std::string printConditionalExpr(const ConditionalExprPtr &expr)
{
    return parenthesize(": " + parenthesize("?", expr->condition),
                        expr->thenBranch, expr->elseBranch);
}

std::string printLogicalExpr(const LogicalExprPtr &expr)
{
    return parenthesize(expr->op.getLexeme(), expr->left, expr->right);
}

std::string PrettyPrinter::toString(const ExprPtrVariant &expression)
{
    switch (expression.index())
    {
    case 0:
        return printLiteralExpr(std::get<0>(expression));
    case 1:
        return printBinaryExpr(std::get<1>(expression));
    case 2:
        return printUnaryExpr(std::get<2>(expression));
    case 3:
        return printGroupingExpr(std::get<3>(expression));
    case 4:
        return printAssignmentExpr(std::get<4>(expression));
    case 5:
        return printFunctionExpr(std::get<5>(expression));
    case 6:
        return printCallExpr(std::get<6>(expression));
    case 7:
        return printConditionalExpr(std::get<7>(expression));
    case 8:
        return printLogicalExpr(std::get<8>(expression));
    default:
        return "";
    }
}

auto printExprStmt(const ExprStmtPtr& stmt) -> std::string {
  return parenthesize("", stmt->expression) + ";";
}

auto printPrintStmt(const PrintStmtPtr& stmt) -> std::string {
  return parenthesize("print", stmt->expression) + ";";
}

auto printBlockStmt(const BlockStmtPtr& blkStmts) -> std::vector<std::string> {
  std::vector<std::string> blkStmtStrsVec;
  blkStmtStrsVec.emplace_back("{");
  for (auto& stmt : blkStmts->statements) {
    auto stmtStr = PrettyPrinter::toString(stmt);
    if (!stmtStr.empty())
      std::move(stmtStr.begin(), stmtStr.end(),
                std::back_inserter(blkStmtStrsVec));
  }
  blkStmtStrsVec.emplace_back("}");
  return blkStmtStrsVec;
}

auto printVarStmt(const VarStmtPtr& stmt) -> std::string {
  std::string str = "var " + stmt->varName.getLexeme();
  if (stmt->initializer.has_value()) {
    str = "( = ( " + str + " ) "
          + PrettyPrinter::toString(stmt->initializer.value()) + " )";
  }
  return str + ";";
}

auto printIfStmt(const IfStmtPtr& stmt) -> std::vector<std::string> {
  std::vector<std::string> ifStmtStrVec;
  ifStmtStrVec.emplace_back("( if (" + PrettyPrinter::toString(stmt->condition)
                            + ")");
  auto thenBranchVec = PrettyPrinter::toString(stmt->thenBranch);
  std::move(thenBranchVec.begin(), thenBranchVec.end(),
            std::back_inserter(ifStmtStrVec));
  if (stmt->elseBranch.has_value()) {
    ifStmtStrVec.emplace_back(" else ");
    auto elseBranchVec = PrettyPrinter::toString(stmt->elseBranch.value());
    std::move(elseBranchVec.begin(), elseBranchVec.end(),
              std::back_inserter(ifStmtStrVec));
  }
  ifStmtStrVec.emplace_back(" );");
  return ifStmtStrVec;
}

auto printWhileStmt(const WhileStmtPtr& stmt) {
  std::vector<std::string> whileStmtStrVec;
  whileStmtStrVec.emplace_back(
      "( while (" + PrettyPrinter::toString(stmt->condition) + ")");
  auto loopBodyVec = PrettyPrinter::toString(stmt->loopBody);
  std::move(loopBodyVec.begin(), loopBodyVec.end(),
            std::back_inserter(whileStmtStrVec));
  whileStmtStrVec.emplace_back(" );");
  return whileStmtStrVec;
}

auto printForStmt(const ForStmtPtr& stmt) {
  std::vector<std::string> forStmtStrVec;
  forStmtStrVec.emplace_back("( for (");
  if (stmt->initializer.has_value()) {
    auto initVec = PrettyPrinter::toString(stmt->initializer.value());
    std::move(initVec.begin(), initVec.end(),
              std::back_inserter(forStmtStrVec));
  }
  forStmtStrVec.emplace_back(
      "; "
      + (stmt->condition.has_value()
             ? PrettyPrinter::toString(stmt->condition.value())
             : std::string())
      + ";"
      + (stmt->increment.has_value()
             ? PrettyPrinter::toString(stmt->increment.value())
             : std::string())
      + ")");

  auto loopBodyVec = PrettyPrinter::toString(stmt->loopBody);
  std::move(loopBodyVec.begin(), loopBodyVec.end(),
            std::back_inserter(forStmtStrVec));
  forStmtStrVec.emplace_back(" );");
  return forStmtStrVec;
}

// Token funcName, FuncExprPtr funcExpr
auto printFunctionStmt(const FuncStmtPtr& stmt) -> std::vector<std::string> {
  std::vector<std::string> funcStrVec;
  funcStrVec.emplace_back("( ( " + stmt->funcName.getLexeme() + ") ");
  funcStrVec.emplace_back(printFunctionExpr(stmt->funcExpr));
  funcStrVec.emplace_back(")");
  return funcStrVec;
}

auto printRetStmt(const RetStmtPtr& stmt) -> std::string {
  std::string value = stmt->value.has_value()
                          ? PrettyPrinter::toString(stmt->value.value())
                          : " ";
  return "( return" + value + ");";
}

auto printClassStmt(const ClassStmtPtr& stmt) -> std::vector<std::string> {
  std::vector<std::string> strVec;
  strVec.emplace_back("(CLASS " + stmt->className.getLexeme() + " )");
  if (stmt->superClass.has_value())
    strVec.emplace_back(" < "
                        + PrettyPrinter::toString(stmt->superClass.value()));
  strVec.emplace_back("{");
  for (const StmtPtrVariant& method : stmt->methods) {
    std::vector<std::string> methodStr = PrettyPrinter::toString(method);
    std::move(methodStr.begin(), methodStr.end(), std::back_inserter(strVec));
  }
  strVec.emplace_back("}");
  return strVec;
}

auto PrettyPrinter::toString(const StmtPtrVariant& statement)
    -> std::vector<std::string> {
  switch (statement.index()) {
    case 0:  // ExprStmtPtr
      return std::vector(1, printExprStmt(std::get<0>(statement)));
    case 1:  // PrintStmtPtr
      return std::vector(1, printPrintStmt(std::get<1>(statement)));
    case 2:  // BlockStmtPtr
      return printBlockStmt(std::get<2>(statement));
    case 3:  // VarStmtPtr
      return std::vector(1, printVarStmt(std::get<3>(statement)));
    case 4:  // VarStmtPtr
      return printIfStmt(std::get<4>(statement));
    case 5:  // WhileStmtPtr
      return printWhileStmt(std::get<5>(statement));
    case 6:  // ForStmtPtr
      return printForStmt(std::get<6>(statement));
    case 7:  // ForStmtPtr
      return printFunctionStmt(std::get<7>(statement));
    case 8:  // RetStmtPtr
      return std::vector(1, printRetStmt(std::get<8>(statement)));
    case 9:  // ClassStmtPtr
      return printClassStmt(std::get<9>(statement));
    default:
      static_assert(
          std::variant_size_v<StmtPtrVariant> == 10,
          "Looks like you forgot to update the cases in "
          "PrettyPrinter::toString(const StmtPtrVariant& statement)!");
      return {};
  }
}

auto PrettyPrinter::toString(const std::vector<StmtPtrVariant>& statements)
    -> std::vector<std::string> {
  std::vector<std::string> stmtStrsVec;
  for (const auto& stmt : statements) {
    auto stmtStr = PrettyPrinter::toString(stmt);
    if (!stmtStr.empty())
      std::move(stmtStr.begin(), stmtStr.end(),
                std::back_inserter(stmtStrsVec));
  }
  return stmtStrsVec;
}