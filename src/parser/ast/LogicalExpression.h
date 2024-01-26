//
// Created by kemal on 1/15/2024.
//

#ifndef MATURSKI_LOGICALEXPRESSION_H
#define MATURSKI_LOGICALEXPRESSION_H

#include <memory>
#include <iostream>
#include "Statement.h"
#include "Expression.h"
#include "Token.h"
#include "Interpreter.h"
#include "RuntimeValue.h"

namespace ast {
    typedef std::shared_ptr<Expression> ExprPtr;

    class LogicalExpression : public Expression {
    public:
        LogicalExpression(ExprPtr left, TokenPtr op, ExprPtr right)
                : Expression(), left(left), _operator(op), right(right) {}

        ExprPtr left;
        ExprPtr right;
        TokenPtr _operator;
        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitLogicalExpression(this);
        }
        void accept(Resolver* visitor) const override {
            return visitor->visitLogicalExpression(this);
        }
        void print() override {
            std::cout << "( " << _operator->value << " ";
            left->print();
            right->print();
            std::cout << ") ";
        }
    };
}

#endif //MATURSKI_LOGICALEXPRESSION_H
