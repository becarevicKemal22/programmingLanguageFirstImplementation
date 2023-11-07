//
// Created by kemal on 11/7/2023.
//

#ifndef MATURSKI_IDENTIFIER_H
#define MATURSKI_IDENTIFIER_H

#include <string>
#include "Expression.h"
#include "Visitor.h"
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
        void accept(Visitor* visitor) const override {
            visitor->visitIdentifier(this);
        }
    };
}

#endif //MATURSKI_IDENTIFIER_H
