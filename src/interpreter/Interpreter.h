//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_INTERPRETER_H
#define MATURSKI_INTERPRETER_H

#include "RuntimeValue.h"
#include "Callable.h"
#include "ErrorPrinter.h"
#include "Environment.h"

namespace ast {
    class Program;
    class Expression;
    class NumericLiteral;
    class Statement;
    class BooleanLiteral;
    class NullLiteral;
    class Identifier;
    class GroupingExpression;
    class UnaryExpression;
    class BinaryExpression;
    class StringLiteral;
    class ExprStatement;
    class PrintStatement;
    class VarDeclaration;
    class AssignmentExpression;
    class BlockStatement;
    class IfStatement;
    class WhileStatement;
    class LogicalExpression;
    class CallExpression;
    class FunctionDeclaration;
    class ReturnStatement;
}

class Interpreter {
public:
    Interpreter(ErrorPrinter& printer);
    RuntimeValuePtr execute(const ast::Statement* statement);
    RuntimeValuePtr visitProgram(const ast::Program* stmt);
    RuntimeValuePtr visitStatement(const ast::Statement* stmt);
    RuntimeValuePtr visitExprStatement(const ast::ExprStatement* stmt);
    RuntimeValuePtr visitFunctionDeclaration(const ast::FunctionDeclaration* stmt);
    RuntimeValuePtr visitPrintStatement(const ast::PrintStatement* stmt);
    RuntimeValuePtr visitVarDeclarationStatement(const ast::VarDeclaration* stmt);
    RuntimeValuePtr visitBlockStatement(const ast::BlockStatement* stmt);
    RuntimeValuePtr visitIfStatement(const ast::IfStatement* stmt);
    RuntimeValuePtr visitWhileStatement(const ast::WhileStatement* stmt);
    RuntimeValuePtr visitReturnStatement(const ast::ReturnStatement* stmt);
    void executeBlock(std::vector<std::shared_ptr<ast::Statement>> statements, std::shared_ptr<Environment> environment);

    RuntimeValuePtr visitExpression(const ast::Expression* expr);
    RuntimeValuePtr visitNumericLiteral(const ast::NumericLiteral* expr);
    RuntimeValuePtr visitBooleanLiteral(const ast::BooleanLiteral* expr);
    RuntimeValuePtr visitStringLiteral(const ast::StringLiteral* expr);
    RuntimeValuePtr visitNullLiteral(const ast::NullLiteral* expr);
    RuntimeValuePtr visitIdentifierExpression(const ast::Identifier* expr);
    RuntimeValuePtr visitGroupingExpression(const ast::GroupingExpression* expr);
    RuntimeValuePtr visitUnaryExpression(const ast::UnaryExpression* expr);
    RuntimeValuePtr visitBinaryExpression(const ast::BinaryExpression* expr);
    RuntimeValuePtr visitAssignmentExpression(const ast::AssignmentExpression* expr);
    RuntimeValuePtr visitLogicalExpression(const ast::LogicalExpression* expr);
    RuntimeValuePtr visitCallExpression(const ast::CallExpression* expr);
    bool hadRuntimeError = false;
    std::shared_ptr<Environment> globals;
    std::shared_ptr<Environment> environment;
private:
    ErrorPrinter& printer;
    RuntimeValuePtr evaluate(ast::Expression* expr);
    bool isTruthy(RuntimeValuePtr value);
    bool areOperandsNumeric(RuntimeValuePtr left, RuntimeValuePtr right);
    bool areOperandsStrings(RuntimeValuePtr left, RuntimeValuePtr right);
    bool isEqual(RuntimeValuePtr left, RuntimeValuePtr right);
    Token getMostRelevantToken(ast::Expression* expr);
    void error(std::string message);
};

#endif //MATURSKI_INTERPRETER_H
