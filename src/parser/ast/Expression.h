//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_EXPRESSION_H
#define MATURSKI_EXPRESSION_H

#include "Statement.h"
#include "../../lexer/Token.h"
#include "../visitor/Visitor.h"

namespace ast {
    typedef std::shared_ptr<Token> TokenPtr;
    class Expression : public Statement {
    public:
        Expression() : Statement() {}
        virtual ~Expression() = default;
        virtual void accept(Visitor* visitor) const{
            visitor->visitExpression(this);
        };
        TokenPtr token;
    };
}

#endif //MATURSKI_EXPRESSION_H
