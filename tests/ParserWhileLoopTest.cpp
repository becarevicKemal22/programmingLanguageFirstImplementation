//
// Created by kemal on 1/16/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <memory>
#include "Parser.h"
#include "MockErrorPrinter.h"
#include "Program.h"
#include "WhileStatement.h"
#include "BlockStatement.h"
#include "PrintStatement.h"

TEST_CASE("Parses while loop with block", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "dok(x > 10) {}";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::WhileStatement> whileStmt = std::dynamic_pointer_cast<ast::WhileStatement>(body[0]);
    REQUIRE(whileStmt);
    std::shared_ptr<ast::BinaryExpression> condition = std::dynamic_pointer_cast<ast::BinaryExpression>(whileStmt->condition);
    REQUIRE(condition);
    REQUIRE(condition->_operator->type == TokenType::Greater);
    std::shared_ptr<ast::BlockStatement> whileBody = std::dynamic_pointer_cast<ast::BlockStatement>(whileStmt->body);
    REQUIRE(whileBody);
    REQUIRE(whileBody->statements.empty());
}

TEST_CASE("Parses while loop with single statement", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "dok(x > 10) print x;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::WhileStatement> whileStmt = std::dynamic_pointer_cast<ast::WhileStatement>(body[0]);
    REQUIRE(whileStmt);
    std::shared_ptr<ast::BinaryExpression> condition = std::dynamic_pointer_cast<ast::BinaryExpression>(whileStmt->condition);
    REQUIRE(condition);
    REQUIRE(condition->_operator->type == TokenType::Greater);
    std::shared_ptr<ast::PrintStatement> print = std::dynamic_pointer_cast<ast::PrintStatement>(whileStmt->body);
    REQUIRE(print);
}