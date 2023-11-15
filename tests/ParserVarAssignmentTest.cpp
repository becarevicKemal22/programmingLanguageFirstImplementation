//
// Created by kemal on 11/14/2023.
//

#include <catch2/catch_test_macros.hpp>

#include <vector>
#include <memory>
#include "MockErrorPrinter.h"
#include "Parser.h"
#include "AssignmentExpression.h"
#include "StringLiteral.h"
#include "ExprStatement.h"

template <typename T>
std::shared_ptr<T> bypassExpressionStatement(std::shared_ptr<ast::Statement> stmt){
    std::shared_ptr<ast::ExprStatement> exprStatement = std::dynamic_pointer_cast<ast::ExprStatement>(stmt);
    if(!exprStatement){
        throw std::domain_error("Statement is not of type ExprStatement. Aborting further downcasting");
    }
    return std::dynamic_pointer_cast<T>(exprStatement->expr);
}

TEST_CASE("Parses variable assignment"){
    std::string source = "myVar = \"string\";";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);

    std::shared_ptr<ast::AssignmentExpression> expr = bypassExpressionStatement<ast::AssignmentExpression>(body[0]);
    REQUIRE(expr);
    REQUIRE(expr->identifier->value == "myVar");
    REQUIRE(std::dynamic_pointer_cast<ast::StringLiteral>(expr->value));
}

TEST_CASE("Requires value to be provided with assignment"){
    std::string source = "myVar = ;";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled == 1);
}

TEST_CASE("Requires semicolon after assignment"){
    std::string source = "myVar = 10";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled == 1);
}

TEST_CASE("Reports invalid assignment target"){
    std::string source = "\"string\" = \"other\";";
    MockErrorPrinter printer;
    Parser parser(printer);
    parser.parse(source);
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled == 2); // 2 because it also prints an expected expression before ';' error
}