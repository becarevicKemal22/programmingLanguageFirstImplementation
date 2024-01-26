//
// Created by kemal on 1/25/2024.
//

#include "Resolver.h"
#include "BlockStatement.h"
#include "VarDeclaration.h"
#include "Identifier.h"
#include "AssignmentExpression.h"
#include "FunctionDeclaration.h"
#include "IfStatement.h"
#include "PrintStatement.h"
#include "ReturnStatement.h"
#include "WhileStatement.h"
#include "BinaryExpression.h"
#include "CallExpression.h"
#include "GroupingExpression.h"
#include "BooleanLiteral.h"
#include "NullLiteral.h"
#include "NumericLiteral.h"
#include "StringLiteral.h"
#include "LogicalExpression.h"
#include "UnaryExpression.h"
#include "Program.h"
#include "ExprStatement.h"

void Resolver::resolve(std::shared_ptr<ast::Statement> statement) {
    statement->accept(this);
}

void Resolver::resolve(std::vector<std::shared_ptr<ast::Statement>> statements) {
    for (auto &statement : statements) {
        resolve(statement);
    }
}

void Resolver::resolveLocal(const ast::Expression *expr, const std::string &name) {
    ScopeStack scopesCopy(scopes);
    while (!scopesCopy.empty()) {
        auto &scope = scopesCopy.top();
        if (scope.find(name) != scope.end()) {
            interpreter.resolve(expr, scopes.size() - scopesCopy.size());
            return;
        }
        scopesCopy.pop();
    }
}

void Resolver::resolveFunction(const ast::FunctionDeclaration *function) {
    beginScope();
    for (auto &param : function->params) {
        declare(param);
        define(param);
    }
    resolve(function->body);
    endScope();
}

void Resolver::declare(std::shared_ptr<Token> identifier) {
    if (scopes.empty()) return;
    auto &scope = scopes.top();
    scope.emplace(identifier->value, false);
}

void Resolver::define(std::shared_ptr<Token> identifier) {
    if (scopes.empty()) return;
    auto &scope = scopes.top();
    scope[identifier->value] = true;
}

void Resolver::visitBlockStatement(const ast::BlockStatement *stmt) {
    beginScope();
    resolve(stmt->statements);
    endScope();
}

void Resolver::visitVarDeclarationStatement(const ast::VarDeclaration *stmt) {
    declare(stmt->identifier);
    if(stmt->initializer != nullptr){
        resolve(stmt->initializer);
    }
    define(stmt->identifier);
}

void Resolver::visitIdentifierExpression(const ast::Identifier *expr) {
    if(!scopes.empty()){
        auto &scope = scopes.top();
        if(scope.find(expr->name) != scope.end() && !scope[expr->name]){
            interpreter.printer.highlightTokenError(*expr->token, "Cannot read local variable in its own initializer.");
        }
    }
    resolveLocal(expr, expr->name);
}

void Resolver::visitAssignmentExpression(const ast::AssignmentExpression *expr) {
    resolve(expr->value);
    resolveLocal(expr, expr->identifier->value);
}

void Resolver::visitFunctionDeclaration(const ast::FunctionDeclaration *stmt) {
    declare(stmt->name);
    define(stmt->name);
    resolveFunction(stmt);
}

void Resolver::visitIfStatement(const ast::IfStatement *stmt) {
    resolve(stmt->condition);
    resolve(stmt->thenBranch);
    if(stmt->elseBranch != nullptr){
        resolve(stmt->elseBranch);
    }
}

void Resolver::visitPrintStatement(const ast::PrintStatement *stmt) {
    resolve(stmt->expr);
}

void Resolver::visitReturnStatement(const ast::ReturnStatement *stmt) {
//    if(!scopes.empty() && scopes.top().empty()){
//        interpreter->printer.highlightTokenError(*stmt->keyword, "Cannot return from top-level code.");
//    }
    if(stmt->value != nullptr){
        resolve(stmt->value);
    }
}

void Resolver::visitWhileStatement(const ast::WhileStatement *stmt) {
    resolve(stmt->condition);
    resolve(stmt->body);
}

void Resolver::visitBinaryExpression(const ast::BinaryExpression *expr) {
    resolve(expr->left);
    resolve(expr->right);
}

void Resolver::visitCallExpression(const ast::CallExpression *expr) {
    resolve(expr->callee);
    for(auto &arg : expr->arguments){
        resolve(arg);
    }
}

void Resolver::visitGroupingExpression(const ast::GroupingExpression *expr) {
    resolve(expr->expr);
}

void Resolver::visitBooleanLiteral(const ast::BooleanLiteral *expr) {}
void Resolver::visitNullLiteral(const ast::NullLiteral *expr) {}
void Resolver::visitNumericLiteral(const ast::NumericLiteral *expr) {}
void Resolver::visitStringLiteral(const ast::StringLiteral *expr) {}

void Resolver::visitLogicalExpression(const ast::LogicalExpression *expr) {
    resolve(expr->left);
    resolve(expr->right);
}

void Resolver::visitUnaryExpression(const ast::UnaryExpression *expr) {
    resolve(expr->right);
}

void Resolver::visitProgram(const ast::Program *stmt) {
    resolve(stmt->body);
}

void Resolver::visitStatement(const ast::Statement *stmt) {
    throw "Resolver::visitStatement() should not be called.";
}

void Resolver::visitExprStatement(const ast::ExprStatement *stmt) {
    resolve(stmt->expr);
}

void Resolver::visitExpression(const ast::Expression *expr) {
    throw "Resolver::visitExpression() should not be called.";
}
