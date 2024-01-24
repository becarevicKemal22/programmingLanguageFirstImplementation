//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_INTERPRETER_H
#define MATURSKI_INTERPRETER_H

#include "RuntimeValue.h"
#include "Callable.h"
#include "ErrorPrinter.h"
#include "Environment.h"
#include "../Visitor/Visitor.h"


class Interpreter : public Visitor<RuntimeValuePtr> {
public:
    Interpreter(ErrorPrinter& printer);
    RuntimeValuePtr execute(const ast::Statement* statement);
    RuntimeValuePtr visitProgram(const ast::Program* stmt) override;
    RuntimeValuePtr visitStatement(const ast::Statement* stmt) override;
    RuntimeValuePtr visitExprStatement(const ast::ExprStatement* stmt) override;
    RuntimeValuePtr visitFunctionDeclaration(const ast::FunctionDeclaration* stmt) override;
    RuntimeValuePtr visitPrintStatement(const ast::PrintStatement* stmt) override;
    RuntimeValuePtr visitVarDeclarationStatement(const ast::VarDeclaration* stmt) override;
    RuntimeValuePtr visitBlockStatement(const ast::BlockStatement* stmt) override;
    RuntimeValuePtr visitIfStatement(const ast::IfStatement* stmt) override;
    RuntimeValuePtr visitWhileStatement(const ast::WhileStatement* stmt) override;
    RuntimeValuePtr visitReturnStatement(const ast::ReturnStatement* stmt) override;
    void executeBlock(std::vector<std::shared_ptr<ast::Statement>> statements, std::shared_ptr<Environment> environment);

    RuntimeValuePtr visitExpression(const ast::Expression* expr) override;
    RuntimeValuePtr visitNumericLiteral(const ast::NumericLiteral* expr) override;
    RuntimeValuePtr visitBooleanLiteral(const ast::BooleanLiteral* expr) override;
    RuntimeValuePtr visitStringLiteral(const ast::StringLiteral* expr) override;
    RuntimeValuePtr visitNullLiteral(const ast::NullLiteral* expr) override;
    RuntimeValuePtr visitIdentifierExpression(const ast::Identifier* expr) override;
    RuntimeValuePtr visitGroupingExpression(const ast::GroupingExpression* expr) override;
    RuntimeValuePtr visitUnaryExpression(const ast::UnaryExpression* expr) override;
    RuntimeValuePtr visitBinaryExpression(const ast::BinaryExpression* expr) override;
    RuntimeValuePtr visitAssignmentExpression(const ast::AssignmentExpression* expr) override;
    RuntimeValuePtr visitLogicalExpression(const ast::LogicalExpression* expr) override;
    RuntimeValuePtr visitCallExpression(const ast::CallExpression* expr) override;
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
