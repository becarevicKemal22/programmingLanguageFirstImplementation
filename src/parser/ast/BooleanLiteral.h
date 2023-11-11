//
// Created by kemal on 11/8/2023.
//

#ifndef MATURSKI_BOOLEANLITERAL_H
#define MATURSKI_BOOLEANLITERAL_H

#include <iostream>
#include "Expression.h"
#include "RuntimeValue.h"
#include "Interpreter.h"

namespace ast{
    class BooleanLiteral : public Expression {
    public:
        BooleanLiteral(TokenPtr token) : Expression() {
            this->token = token;
            value = token->type == TokenType::Tacno;
        }
        bool value;
        TokenPtr token;
        void print() override {
            std::cout << token->value << " ";
        }
        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitBooleanLiteral(this);
        };
    };
}

#endif //MATURSKI_BOOLEANLITERAL_H
