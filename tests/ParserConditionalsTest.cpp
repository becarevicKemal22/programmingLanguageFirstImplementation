//
// Created by kemal on 1/14/2024.
//

#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "IfStatement.h"
#include "BypassExpressionStatement.h"
#include "MockErrorPrinter.h"
#include "Parser.h"
#include "VarDeclaration.h"
#include "AssignmentExpression.h"
#include "PrintStatement.h"
#include "BlockStatement.h"

TEST_CASE("Parses if statement", "[parser][conditional][statement]"){
    std::string source = "ako x == 5 onda {"
                         ""
                         "}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::IfStatement> ifStatement = std::dynamic_pointer_cast<ast::IfStatement>(program.body[0]);
    REQUIRE(ifStatement);
    std::shared_ptr<ast::BinaryExpression> condition = std::dynamic_pointer_cast<ast::BinaryExpression>(ifStatement->condition);
    REQUIRE(condition);

    std::shared_ptr<ast::BlockStatement> thenBlock = std::dynamic_pointer_cast<ast::BlockStatement>(ifStatement->thenBranch);
    REQUIRE(thenBlock);
    REQUIRE(thenBlock->statements.size() == 0);

    REQUIRE(ifStatement->elseBranch == nullptr);
}

TEST_CASE("Parses if-else statement", "[parser][conditional][statement]"){
    std::string source = "ako x == 5 onda print x;"
                         "inace {}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::IfStatement> ifStatement = std::dynamic_pointer_cast<ast::IfStatement>(program.body[0]);
    REQUIRE(ifStatement);
    std::shared_ptr<ast::BinaryExpression> condition = std::dynamic_pointer_cast<ast::BinaryExpression>(ifStatement->condition);
    REQUIRE(condition);

    std::shared_ptr<ast::PrintStatement> printStmt = std::dynamic_pointer_cast<ast::PrintStatement>(ifStatement->thenBranch);
    REQUIRE(printStmt);
    std::shared_ptr<ast::BlockStatement> elseBlock = std::dynamic_pointer_cast<ast::BlockStatement>(ifStatement->elseBranch);
    REQUIRE(elseBlock);
    REQUIRE(elseBlock->statements.size() == 0);
}

TEST_CASE("Throws error on else statement without if statement"){
    std::string source = "inace print x;";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Throws error on missing 'onda'"){
    std::string source = "ako x == 10 {}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Throws error on missing condition"){
    std::string source = "ako onda {}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}