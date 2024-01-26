//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_NUMERICLITERAL_H
#define MATURSKI_NUMERICLITERAL_H

#include <iostream>
#include "Expression.h"
#include "Token.h"
#include "Interpreter.h"
#include "RuntimeValue.h"

namespace ast{
    class NumericLiteral : public Expression {
    public:
        explicit NumericLiteral(std::shared_ptr<Token> token) {
            this->token = token;
            number = std::stod(token->value);
        }
        double number;
        TokenPtr token;
        ~NumericLiteral() override = default;
        RuntimeValuePtr accept(Interpreter* visitor) const override{
            return visitor->visitNumericLiteral(this);
        }
        void accept(Resolver* visitor) const override{
            return visitor->visitNumericLiteral(this);
        }
        void print() override {
            std::cout << number << " ";
        }
    };
}

#endif //MATURSKI_NUMERICLITERAL_H
