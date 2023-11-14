//
// Created by kemal on 11/13/2023.
//

#ifndef MATURSKI_VARDECLARATION_H
#define MATURSKI_VARDECLARATION_H

#include <iostream>
#include "Statement.h"
#include "Token.h"
#include "Expression.h"

namespace ast{
    class VarDeclaration : public Statement {
    public:
        VarDeclaration(TokenPtr identifier, ExprPtr initializer) : Statement(), identifier(identifier), initializer(initializer){

        }
        TokenPtr identifier;
        ExprPtr initializer;

        RuntimeValuePtr accept(Interpreter* visitor) const override {
            return visitor->visitVarDeclarationStatement(this);
        }
        void print() override {
            std::cout << "VarDecl( " << identifier->value << " = ";
            if(initializer){
                initializer->print();
            }else{
                cout << "prazno ";
            }
            std::cout << ")\n";
        }
    };
}

#endif //MATURSKI_VARDECLARATION_H
