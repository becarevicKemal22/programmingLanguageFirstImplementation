//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_EXPRESSION_H
#define MATURSKI_EXPRESSION_H

#include "Statement.h"
#include "Token.h"
#include "Interpreter.h"

namespace ast {
    typedef std::shared_ptr<Token> TokenPtr;

    class Expression : public Statement {
    public:
        Expression() : Statement() {}
        virtual ~Expression() = default;
        RuntimeValuePtr accept(Interpreter* visitor) const override{
            return visitor->visitExpression(this);
        };
        void accept(Resolver* visitor) const override{
            return visitor->visitExpression(this);
        };
        virtual void print() override {};
    };
    typedef std::shared_ptr<Expression> ExprPtr;
}

#endif //MATURSKI_EXPRESSION_H
