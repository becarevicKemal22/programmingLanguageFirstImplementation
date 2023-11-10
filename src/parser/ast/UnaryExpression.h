//
// Created by kemal on 11/10/2023.
//

#ifndef MATURSKI_UNARYEXPRESSION_H
#define MATURSKI_UNARYEXPRESSION_H

#include <iostream>
#include <memory>
#include "Expression.h"

namespace ast{
    class UnaryExpression : public Expression {
    public:
        UnaryExpression(TokenPtr _operator, std::shared_ptr<Expression> expr) : Expression(), _operator(_operator), expr(expr) {}
        TokenPtr _operator;
        std::shared_ptr<Expression> expr;
        void print() override {
            std::cout << _operator->value;
            expr->print();
        }
    };
}

#endif //MATURSKI_UNARYEXPRESSION_H
