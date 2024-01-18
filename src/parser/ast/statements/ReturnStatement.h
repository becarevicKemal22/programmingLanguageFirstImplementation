//
// Created by kemal on 1/17/2024.
//

#ifndef MATURSKI_RETURNSTATEMENT_H
#define MATURSKI_RETURNSTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Interpreter.h"
#include "Expression.h"

namespace ast{
    class ReturnStatement : public Statement {
    public:
        ReturnStatement(std::shared_ptr<Token> keyword, std::shared_ptr<Expression> value) : Statement(), keyword(keyword), value(value) {}

        std::shared_ptr<Expression> value;
        std::shared_ptr<Token> keyword;

        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitReturnStatement(this);
        }
        void print() override{
            std::cout << "Return ";
            value->print();
            std::cout << "\n";
        }
    };
}

#endif //MATURSKI_RETURNSTATEMENT_H
