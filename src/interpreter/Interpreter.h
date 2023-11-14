//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_INTERPRETER_H
#define MATURSKI_INTERPRETER_H

#include "RuntimeValue.h"
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
}

class Interpreter {
public:
    Interpreter(ErrorPrinter& printer) : printer(printer) {};
    RuntimeValuePtr visitProgram(const ast::Program* stmt);
    RuntimeValuePtr visitStatement(const ast::Statement* stmt);
    RuntimeValuePtr visitExprStatement(const ast::ExprStatement* stmt);
    RuntimeValuePtr visitPrintStatement(const ast::PrintStatement* stmt);
    RuntimeValuePtr visitVarDeclarationStatement(const ast::VarDeclaration* stmt);

    RuntimeValuePtr visitExpression(const ast::Expression* expr);
    RuntimeValuePtr visitNumericLiteral(const ast::NumericLiteral* expr);
    RuntimeValuePtr visitBooleanLiteral(const ast::BooleanLiteral* expr);
    RuntimeValuePtr visitStringLiteral(const ast::StringLiteral* expr);
    RuntimeValuePtr visitNullLiteral(const ast::NullLiteral* expr);
    RuntimeValuePtr visitIdentifierExpression(const ast::Identifier* expr);
    RuntimeValuePtr visitGroupingExpression(const ast::GroupingExpression* expr);
    RuntimeValuePtr visitUnaryExpression(const ast::UnaryExpression* expr);
    RuntimeValuePtr visitBinaryExpression(const ast::BinaryExpression* expr);
    bool hadRuntimeError = false;
    Environment environment{};
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
