//
// Created by kemal on 1/16/2024.
//

#ifndef MATURSKI_CALLEXPRESSION_H
#define MATURSKI_CALLEXPRESSION_H

#include <iostream>
#include <vector>
#include "Expression.h"
#include "Interpreter.h"
#include "RuntimeValue.h"

namespace ast {
    class CallExpression : public Expression {
    public:
        CallExpression(std::shared_ptr<Expression> callee, TokenPtr paren,
                       std::vector<std::shared_ptr<ast::Expression>> arguments)
                : Expression(), callee(callee), paren(paren), arguments(arguments) {}

        std::shared_ptr<Expression> callee;
        TokenPtr paren;
        std::vector<std::shared_ptr<ast::Expression>> arguments;

        void print() override {
            std::cout << "CallExpr ";
            callee->print();
            std::cout << "( ";
            for (auto expr: arguments) expr->print();
            std::cout << ") ";
        }

        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitCallExpression(this);
        };
        void accept(Resolver* visitor) const override {
            return visitor->visitCallExpression(this);
        }
    };
}

#endif //MATURSKI_CALLEXPRESSION_H
