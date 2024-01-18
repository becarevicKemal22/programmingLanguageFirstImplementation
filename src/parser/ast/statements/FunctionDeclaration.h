//
// Created by kemal on 1/17/2024.
//

#ifndef MATURSKI_FUNCTIONDECLARATION_H
#define MATURSKI_FUNCTIONDECLARATION_H

#include <iostream>
#include <vector>
#include "Statement.h"
#include "Token.h"
#include "Expression.h"

namespace ast {
    class FunctionDeclaration : public Statement {
    public:
        FunctionDeclaration(std::shared_ptr<Token> name, std::vector<std::shared_ptr<Token>> params,
                            std::vector<std::shared_ptr<Statement>> body)
                : Statement(), name(name), params(params), body(body) {}

        std::shared_ptr<Token> name;
        std::vector<std::shared_ptr<Token>> params;
        std::vector<std::shared_ptr<Statement>> body;

        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitFunctionDeclaration(this);
        }

        void print() override {
            std::cout << "funkcija " << name->value << "(";
            for (auto param : params) {
                std::cout << param->value << ", ";
            }
            std::cout << ") {\n";
            for (auto stmt : body) {
                std::cout << "    ";
                stmt->print();
            }
            std::cout << "}\n";
        }
    };
}

#endif //MATURSKI_FUNCTIONDECLARATION_H
