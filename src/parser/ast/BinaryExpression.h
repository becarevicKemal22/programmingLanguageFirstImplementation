//
// Created by kemal on 11/7/2023.
//

#ifndef MATURSKI_BINARYEXPRESSION_H
#define MATURSKI_BINARYEXPRESSION_H

#include <memory>
#include "Statement.h"
#include "Expression.h"
#include "Token.h"
#include "Visitor.h"

namespace ast {
    typedef std::shared_ptr<Expression> ExprPtr;

    class BinaryExpression : public Expression {
    public:
        BinaryExpression(ExprPtr left, TokenPtr op, ExprPtr right)
                : Expression(), left(left), _operator(op), right(right) {}

        ExprPtr left;
        ExprPtr right;
        TokenPtr _operator;
//        void accept(Visitor* visitor) const override {
//            visitor->visitBinaryExpression(this);
//        }
        void print() override {
            std::cout << "( " << _operator->value << " ";
            left->print();
            right->print();
            std::cout << ") ";
        }
    };
}

#endif //MATURSKI_BINARYEXPRESSION_H
