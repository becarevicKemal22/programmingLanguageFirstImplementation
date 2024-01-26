//
// Created by kemal on 1/25/2024.
//

#ifndef MATURSKI_RESOLVER_H
#define MATURSKI_RESOLVER_H

#include <memory>
#include <unordered_map>
#include <stack>

#include "Visitor.h"
#include "Interpreter.h"

class Resolver : public Visitor<void> {
    using ScopeStack = std::stack<std::unordered_map<std::string, bool>> ;

    Interpreter& interpreter;
    ScopeStack scopes;

    void resolve(std::vector<std::shared_ptr<ast::Statement>> statements);
    void resolve(std::shared_ptr<ast::Statement> statement);
    void resolveLocal(const ast::Expression* expr, const std::string& name);
    void resolveFunction(const ast::FunctionDeclaration* function);

    void beginScope(){
        scopes.emplace();
    }

    void endScope(){
        scopes.pop();
    }

    void declare(std::shared_ptr<Token> identifier);
    void define(std::shared_ptr<Token> identifier);

public:
    Resolver(Interpreter& interpreter) : interpreter(interpreter) {}

    void visitProgram(const ast::Program* stmt) override;
    void visitStatement(const ast::Statement* stmt) override;
    void visitExprStatement(const ast::ExprStatement* stmt) override;
    void visitFunctionDeclaration(const ast::FunctionDeclaration* stmt) override;
    void visitPrintStatement(const ast::PrintStatement* stmt) override;
    void visitVarDeclarationStatement(const ast::VarDeclaration* stmt) override;
    void visitBlockStatement(const ast::BlockStatement* stmt) override;
    void visitIfStatement(const ast::IfStatement* stmt) override;
    void visitWhileStatement(const ast::WhileStatement* stmt) override;
    void visitReturnStatement(const ast::ReturnStatement* stmt) override;

    void visitExpression(const ast::Expression* expr) override;
    void visitNumericLiteral(const ast::NumericLiteral* expr) override;
    void visitBooleanLiteral(const ast::BooleanLiteral* expr) override;
    void visitStringLiteral(const ast::StringLiteral* expr) override;
    void visitNullLiteral(const ast::NullLiteral* expr) override;
    void visitIdentifierExpression(const ast::Identifier* expr) override;
    void visitGroupingExpression(const ast::GroupingExpression* expr) override;
    void visitUnaryExpression(const ast::UnaryExpression* expr) override;
    void visitBinaryExpression(const ast::BinaryExpression* expr) override;
    void visitAssignmentExpression(const ast::AssignmentExpression* expr) override;
    void visitLogicalExpression(const ast::LogicalExpression* expr) override;
    void visitCallExpression(const ast::CallExpression* expr) override;
};


#endif //MATURSKI_RESOLVER_H
