//
// Created by kemal on 11/8/2023.
//

#ifndef MATURSKI_GROUPINGEXPRESSION_H
#define MATURSKI_GROUPINGEXPRESSION_H

#include <iostream>
#include "Expression.h"

namespace ast{
    class GroupingExpression : public Expression {
    public:
        explicit GroupingExpression(std::shared_ptr<Expression> expr) : Expression(), expr(expr){}
        std::shared_ptr<Expression> expr;
        void print() override {
            std::cout << "( ";
            expr->print();
            std::cout << ") ";
        }
    };
}

#endif //MATURSKI_GROUPINGEXPRESSION_H
