//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_INTERPRETER_H
#define MATURSKI_INTERPRETER_H

#include "RuntimeValue.h"
#include "ErrorPrinter.h"

namespace ast {
    class Program;
    class Expression;
    class NumericLiteral;
    class Statement;
    class BooleanLiteral;
    class NullLiteral;
    class GroupingExpression;
    class UnaryExpression;
    class BinaryExpression;
}

class Interpreter {
public:
    Interpreter(ErrorPrinter& printer) : printer(printer) {};
    RuntimeValuePtr visitProgram(const ast::Program* expr);
    RuntimeValuePtr visitStatement(const ast::Statement* expr);
    RuntimeValuePtr visitExpression(const ast::Expression* expr);
    RuntimeValuePtr visitNumericLiteral(const ast::NumericLiteral* expr);
    RuntimeValuePtr visitBooleanLiteral(const ast::BooleanLiteral* expr);
    RuntimeValuePtr visitNullLiteral(const ast::NullLiteral* expr);
    RuntimeValuePtr visitGroupingExpression(const ast::GroupingExpression* expr);
    RuntimeValuePtr visitUnaryExpression(const ast::UnaryExpression* expr);
    RuntimeValuePtr visitBinaryExpression(const ast::BinaryExpression* expr);
    bool hadRuntimeError = false;
private:
    ErrorPrinter& printer;
    RuntimeValuePtr evaluate(ast::Expression* expr);
    bool isTruthy(RuntimeValuePtr value);
    bool areOperandsNumeric(RuntimeValuePtr left, RuntimeValuePtr right);
    bool isEqual(RuntimeValuePtr left, RuntimeValuePtr right);
    Token getMostRelevantToken(ast::Expression* expr);
    void error(std::string message);
};

#endif //MATURSKI_INTERPRETER_H
