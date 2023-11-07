//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_VISITOR_H
#define MATURSKI_VISITOR_H

namespace ast{
    class Statement;
    class Expression;
    class NumericLiteral;
};

class Visitor {
public:
    virtual void visitStatement(const ast::Statement* statement) const = 0;
    virtual void visitExpression(const ast::Expression* expression) const = 0;
    virtual void visitNumericLiteral(const ast::NumericLiteral* numericLiteral) const = 0;
};

#endif //MATURSKI_VISITOR_H
