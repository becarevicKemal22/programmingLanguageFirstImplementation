//
// Created by kemal on 11/10/2023.
//

#ifndef MATURSKI_UNARYEXPRESSION_H
#define MATURSKI_UNARYEXPRESSION_H

#include <iostream>
#include <memory>
#include "Expression.h"
#include "Interpreter.h"
#include "RuntimeValue.h"

namespace ast{
    class UnaryExpression : public Expression {
    public:
        UnaryExpression(TokenPtr _operator, std::shared_ptr<Expression> expr) : Expression(), _operator(_operator), right(expr) {}
        TokenPtr _operator;
        std::shared_ptr<Expression> right;
        void print() override {
            std::cout << _operator->value;
            right->print();
        }
        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitUnaryExpression(this);
        }
    };
}

#endif //MATURSKI_UNARYEXPRESSION_H
