//
// Created by kemal on 11/12/2023.
//

#ifndef MATURSKI_EXPRSTATEMENT_H
#define MATURSKI_EXPRSTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Expression.h"
#include "RuntimeValue.h"
#include "Interpreter.h"

namespace ast{
    class ExprStatement : public Statement {
    public:
        explicit ExprStatement(std::shared_ptr<Expression> expression) : Statement(), expr(expression) {}
        std::shared_ptr<Expression> expr;
        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitExprStatement(this);
        }
        void print() override{
            expr->print();
            std::cout << "\n";
        }
    };
}

#endif //MATURSKI_EXPRSTATEMENT_H
