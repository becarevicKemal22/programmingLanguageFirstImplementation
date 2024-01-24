//
// Created by kemal on 11/7/2023.
//

#ifndef MATURSKI_IDENTIFIER_H
#define MATURSKI_IDENTIFIER_H

#include <string>
#include <iostream>
#include "Expression.h"
#include "../../Visitor/Visitor.h"
#include "Token.h"

namespace ast{
    class Identifier : public Expression {
    public:
        Identifier(TokenPtr token) : Expression() {
            this->token = token;
            name = token->value;
        }
        std::string name;
        TokenPtr token;
        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitIdentifierExpression(this);
        };
        void print() override {
            std::cout << name << " ";
        }
    };
}

#endif //MATURSKI_IDENTIFIER_H
