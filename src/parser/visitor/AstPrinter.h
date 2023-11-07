//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_VISITORPRINTER_H
#define MATURSKI_VISITORPRINTER_H

#include <iostream>
#include "Visitor.h"
#include "../ast/Statement.h"
#include "../ast/Expression.h"
#include "../ast/NumericLiteral.h"

using std::cout;

class AstPrinter : public Visitor {
    void visitStatement(const ast::Statement* statement) const override{
        cout << "";
    };
    void visitExpression(const ast::Expression* expression) const override{
        cout << "";
    };
    void visitNumericLiteral(const ast::NumericLiteral* numericLiteral) const override{
        cout << numericLiteral->number << " ";
    };
};

#endif //MATURSKI_VISITORPRINTER_H
