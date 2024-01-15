//
// Created by kemal on 11/17/2023.
//

#ifndef MATURSKI_BYPASSEXPRESSIONSTATEMENT_H
#define MATURSKI_BYPASSEXPRESSIONSTATEMENT_H

#include <memory>
#include "Statement.h"
#include "ExprStatement.h"

template <typename T>
std::shared_ptr<T> bypassExpressionStatement(std::shared_ptr<ast::Statement> stmt){
    std::shared_ptr<ast::ExprStatement> exprStatement = std::dynamic_pointer_cast<ast::ExprStatement>(stmt);
    if(!exprStatement){
        throw std::domain_error("Statement is not of type ExprStatement. Aborting further downcasting");
    }
    return std::dynamic_pointer_cast<T>(exprStatement->expr);
}

#endif //MATURSKI_BYPASSEXPRESSIONSTATEMENT_H
