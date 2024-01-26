//
// Created by kemal on 11/12/2023.
//

#ifndef MATURSKI_PRINTSTATEMENT_H
#define MATURSKI_PRINTSTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Expression.h"
#include "RuntimeValue.h"
#include "Interpreter.h"

namespace ast{
    class PrintStatement : public Statement {
    public:
        explicit PrintStatement(std::shared_ptr<Expression> expression) : Statement(), expr(expression) {}
        std::shared_ptr<Expression> expr;
        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitPrintStatement(this);
        }
        void accept(Resolver* visitor) const override {
            return visitor->visitPrintStatement(this);
        }
        void print() override{
            std::cout << "PrintStatement( ";
            expr->print();
            std::cout << ")\n";
        }
    };
}

#endif //MATURSKI_PRINTSTATEMENT_H
