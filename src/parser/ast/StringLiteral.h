//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_STRINGLITERAL_H
#define MATURSKI_STRINGLITERAL_H

#include <iostream>
#include <memory>
#include <string>
#include "Expression.h"
#include "Token.h"
#include "RuntimeValue.h"
#include "Interpreter.h"

namespace ast{
    class StringLiteral : public Expression {
    public:
        explicit StringLiteral(std::shared_ptr<Token> token) {
            this->token = token;
            std::string val = token->value.substr(0, token->value.length() - 1);
            value = val.substr(1, val.length());
        }
        std::string value;
        TokenPtr token;
        ~StringLiteral() override = default;
        RuntimeValuePtr accept(Interpreter* visitor) const override{
            return visitor->visitStringLiteral(this);
        }
        void print() override {
            std::cout << "\"" + value + "\"" << " ";
        }
    };
}

#endif //MATURSKI_STRINGLITERAL_H
