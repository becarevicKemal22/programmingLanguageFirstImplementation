//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_VISITOR_H
#define MATURSKI_VISITOR_H

// AST PRINTER AND VISITOR CLASSES ARE NOT IN USE. DO NOT MODIFY.

namespace ast{
    class Statement;
    class Expression;
    class BinaryExpression;
    class NumericLiteral;
    class Identifier;
};

class Visitor {
public:
    virtual void visitStatement(const ast::Statement* statement) const = 0;
    virtual void visitExpression(const ast::Expression* expression) const = 0;
    virtual void visitBinaryExpression(const ast::BinaryExpression* expression) const = 0;
    virtual void visitNumericLiteral(const ast::NumericLiteral* numericLiteral) const = 0;
    virtual void visitIdentifier(const ast::Identifier* identifier) const = 0;
};

#endif //MATURSKI_VISITOR_H
