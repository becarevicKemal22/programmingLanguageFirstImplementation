//
// Created by kemal on 1/16/2024.
//

#ifndef MATURSKI_WHILESTATEMENT_H
#define MATURSKI_WHILESTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Token.h"
#include "Expression.h"

namespace ast {
    class WhileStatement : public Statement {
    public:
        WhileStatement(std::shared_ptr<ast::Expression> condition, std::shared_ptr<ast::Statement> body)
                : Statement(), condition(condition), body(body) {}

        std::shared_ptr<ast::Expression> condition;
        std::shared_ptr<ast::Statement> body;

        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitWhileStatement(this);
        }

        void print() override {
            std::cout << "dok ";
            condition->print();
            body->print();
        }
    };
}

#endif //MATURSKI_WHILESTATEMENT_H
