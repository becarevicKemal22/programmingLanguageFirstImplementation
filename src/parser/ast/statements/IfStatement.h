//
// Created by kemal on 1/14/2024.
//

#ifndef MATURSKI_IFSTATEMENT_H
#define MATURSKI_IFSTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Token.h"
#include "Expression.h"

namespace ast {
    class IfStatement : public Statement {
    public:
        IfStatement(std::shared_ptr<ast::Expression> condition, std::shared_ptr<ast::Statement> thenBranch,
                    std::shared_ptr<ast::Statement> elseBranch)
                : Statement(), condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

        std::shared_ptr<ast::Expression> condition;
        std::shared_ptr<ast::Statement> thenBranch, elseBranch;

        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitIfStatement(this);
        }
        void accept(Resolver* visitor) const override {
            return visitor->visitIfStatement(this);
        }

        void print() override {
            std::cout << "ako ";
            condition->print();
            thenBranch->print();
            if(elseBranch){
                std::cout << "inace ";
                elseBranch->print();
                std::cout << "\n";
            }
        }
    };
}

#endif //MATURSKI_IFSTATEMENT_H
