//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_NUMERICLITERAL_H
#define MATURSKI_NUMERICLITERAL_H

#include "Expression.h"
#include "../../lexer/Token.h"
#include "../visitor/Visitor.h"

namespace ast{
    class NumericLiteral : public Expression {
    public:
        explicit NumericLiteral(std::shared_ptr<Token> token) {
            this->token = token;
            number = std::stod(token->value);
        }
        double number;
        ~NumericLiteral() override = default;
        void accept(Visitor* visitor) const override{
            visitor->visitNumericLiteral(this);
        }
    };
}

#endif //MATURSKI_NUMERICLITERAL_H