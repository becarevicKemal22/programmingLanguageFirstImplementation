//
// Created by kemal on 11/15/2023.
//

#ifndef MATURSKI_BLOCKSTATEMENT_H
#define MATURSKI_BLOCKSTATEMENT_H

#include <iostream>
#include "Statement.h"
#include "Token.h"
#include "Expression.h"

namespace ast{
    class BlockStatement : public Statement {
    public:
        BlockStatement(std::vector<std::shared_ptr<Statement>> statements) : Statement(), statements(statements){}
        std::vector<std::shared_ptr<Statement>> statements;

        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitBlockStatement(this);
        }
        void print() override {
            std::cout << "{ \n";
            for(auto stmt : statements){
                stmt->print();
            }
            std::cout << "}\n";
        }
    };
}

#endif //MATURSKI_BLOCKSTATEMENT_H
