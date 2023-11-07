//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_VISITORPRINTER_H
#define MATURSKI_VISITORPRINTER_H

#include <iostream>
#include "Visitor.h"
#include "Statement.h"
#include "Expression.h"
#include "NumericLiteral.h"
#include "Identifier.h"

using std::cout;

class AstPrinter : public Visitor {
    // Statements
    void visitStatement(const ast::Statement* statement) const override{
        cout << "";
    };
    // Expressions
    void visitExpression(const ast::Expression* expression) const override{
        cout << "";
    };
    void visitNumericLiteral(const ast::NumericLiteral* numericLiteral) const override{
        cout << numericLiteral->number << " ";
    };
    void visitIdentifier(const ast::Identifier* identifier) const override {
        cout << identifier->name << " ";
    }
};

#endif //MATURSKI_VISITORPRINTER_H
