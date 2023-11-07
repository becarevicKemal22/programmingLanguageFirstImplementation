//
// Created by kemal on 11/8/2023.
//

#ifndef MATURSKI_NULLLITERAL_H
#define MATURSKI_NULLLITERAL_H

#include <iostream>
#include "Expression.h"

namespace ast{
    class NullLiteral : public Expression {
    public:
        NullLiteral(TokenPtr token) : Expression(), token(token) {}
        TokenPtr token;
        void print() override {
            std::cout << "prazno ";
        }
    };
}

#endif //MATURSKI_NULLLITERAL_H
