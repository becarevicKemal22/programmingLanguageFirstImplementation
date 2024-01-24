//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_VISITOR_H
#define MATURSKI_VISITOR_H

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

template<typename T>
class Visitor {
public:
    Visitor() = default;
    virtual ~Visitor() = default;

    virtual T visitProgram(const ast::Program* stmt) = 0;
    virtual T visitStatement(const ast::Statement* stmt) = 0;
    virtual T visitExprStatement(const ast::ExprStatement* stmt) = 0;
    virtual T visitFunctionDeclaration(const ast::FunctionDeclaration* stmt) = 0;
    virtual T visitPrintStatement(const ast::PrintStatement* stmt) = 0;
    virtual T visitVarDeclarationStatement(const ast::VarDeclaration* stmt) = 0;
    virtual T visitBlockStatement(const ast::BlockStatement* stmt) = 0;
    virtual T visitIfStatement(const ast::IfStatement* stmt) = 0;
    virtual T visitWhileStatement(const ast::WhileStatement* stmt) = 0;
    virtual T visitReturnStatement(const ast::ReturnStatement* stmt) = 0;

    virtual T visitExpression(const ast::Expression* expr) = 0;
    virtual T visitNumericLiteral(const ast::NumericLiteral* expr) = 0;
    virtual T visitBooleanLiteral(const ast::BooleanLiteral* expr) = 0;
    virtual T visitStringLiteral(const ast::StringLiteral* expr) = 0;
    virtual T visitNullLiteral(const ast::NullLiteral* expr) = 0;
    virtual T visitIdentifierExpression(const ast::Identifier* expr) = 0;
    virtual T visitGroupingExpression(const ast::GroupingExpression* expr) = 0;
    virtual T visitUnaryExpression(const ast::UnaryExpression* expr) = 0;
    virtual T visitBinaryExpression(const ast::BinaryExpression* expr) = 0;
    virtual T visitAssignmentExpression(const ast::AssignmentExpression* expr) = 0;
    virtual T visitLogicalExpression(const ast::LogicalExpression* expr) = 0;
    virtual T visitCallExpression(const ast::CallExpression* expr) = 0;
};

#endif //MATURSKI_VISITOR_H
