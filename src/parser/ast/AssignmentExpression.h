//
// Created by kemal on 11/14/2023.
//

#ifndef MATURSKI_ASSIGNMENTEXPRESSION_H
#define MATURSKI_ASSIGNMENTEXPRESSION_H

#include <iostream>
#include <memory>
#include "Expression.h"
#include "Interpreter.h"
#include "RuntimeValue.h"

namespace ast{
    class AssignmentExpression : public Expression {
    public:
        AssignmentExpression(TokenPtr identifier, std::shared_ptr<Expression> value) : Expression(), identifier(identifier), value(value) {}
        TokenPtr identifier;
        std::shared_ptr<Expression> value;
        void print() override {
            std::cout << "Assignment( " << identifier->value << " = ";
            value->print();
            std::cout << ")\n";
        }
        RuntimeValuePtr accept(Interpreter *visitor) const override {
            return visitor->visitAssignmentExpression(this);
        }
        void accept(Resolver *visitor) const override {
            return visitor->visitAssignmentExpression(this);
        }
    };
}

#endif //MATURSKI_ASSIGNMENTEXPRESSION_H
