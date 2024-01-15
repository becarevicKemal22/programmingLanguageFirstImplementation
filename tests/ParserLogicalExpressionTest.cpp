//
// Created by kemal on 1/15/2024.
//

#include <catch2/catch_test_macros.hpp>

#include <memory>
#include "Parser.h"
#include "MockErrorPrinter.h"
#include "Program.h"
#include "LogicalExpression.h"
#include "BypassExpressionStatement.h"
#include "BooleanLiteral.h"

TEST_CASE("Parses logical or", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "netacno || tacno;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::LogicalExpression> binExpr = bypassExpressionStatement<ast::LogicalExpression>(body[0]);
    REQUIRE(binExpr);
    REQUIRE(binExpr->_operator->type == TokenType::LogicalOr);
    std::shared_ptr<ast::BooleanLiteral> left = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->left);
    REQUIRE(left);
    REQUIRE(left->value == false);
    std::shared_ptr<ast::BooleanLiteral> right = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->right);
    REQUIRE(right);
    CHECK(right->value == true);
}

TEST_CASE("Parses chained logical or", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "netacno || tacno || netacno;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::LogicalExpression> binExpr = bypassExpressionStatement<ast::LogicalExpression>(body[0]);
    REQUIRE(binExpr);
    REQUIRE(binExpr->_operator->type == TokenType::LogicalOr);
    std::shared_ptr<ast::LogicalExpression> left = std::dynamic_pointer_cast<ast::LogicalExpression>(binExpr->left);
    REQUIRE(left);
    REQUIRE(left->_operator->type == TokenType::LogicalOr);
    std::shared_ptr<ast::BooleanLiteral> leftLeft = std::dynamic_pointer_cast<ast::BooleanLiteral>(left->left);
    REQUIRE(leftLeft);
    REQUIRE(leftLeft->value == false);
    std::shared_ptr<ast::BooleanLiteral> leftRight= std::dynamic_pointer_cast<ast::BooleanLiteral>(left->right);
    REQUIRE(leftRight);
    REQUIRE(leftRight->value == true);
    std::shared_ptr<ast::BooleanLiteral> right = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->right);
    REQUIRE(right);
    REQUIRE(right->value == false);
}

TEST_CASE("Parses logical and", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "netacno && tacno;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::LogicalExpression> binExpr = bypassExpressionStatement<ast::LogicalExpression>(body[0]);
    REQUIRE(binExpr);
    REQUIRE(binExpr->_operator->type == TokenType::LogicalAnd);
    std::shared_ptr<ast::BooleanLiteral> left = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->left);
    REQUIRE(left);
    REQUIRE(left->value == false);
    std::shared_ptr<ast::BooleanLiteral> right = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->right);
    REQUIRE(right);
    CHECK(right->value == true);
}

TEST_CASE("Parses chained logical and", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "netacno && tacno && netacno;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::LogicalExpression> binExpr = bypassExpressionStatement<ast::LogicalExpression>(body[0]);
    REQUIRE(binExpr);
    REQUIRE(binExpr->_operator->type == TokenType::LogicalAnd);
    std::shared_ptr<ast::LogicalExpression> left = std::dynamic_pointer_cast<ast::LogicalExpression>(binExpr->left);
    REQUIRE(left);
    REQUIRE(left->_operator->type == TokenType::LogicalAnd);
    std::shared_ptr<ast::BooleanLiteral> leftLeft = std::dynamic_pointer_cast<ast::BooleanLiteral>(left->left);
    REQUIRE(leftLeft);
    REQUIRE(leftLeft->value == false);
    std::shared_ptr<ast::BooleanLiteral> leftRight= std::dynamic_pointer_cast<ast::BooleanLiteral>(left->right);
    REQUIRE(leftRight);
    REQUIRE(leftRight->value == true);
    std::shared_ptr<ast::BooleanLiteral> right = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->right);
    REQUIRE(right);
    REQUIRE(right->value == false);
}

TEST_CASE("Parses mixed logical expression", "[Parser][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "netacno || tacno && netacno;";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::LogicalExpression> binExpr = bypassExpressionStatement<ast::LogicalExpression>(body[0]);
    REQUIRE(binExpr);
    REQUIRE(binExpr->_operator->type == TokenType::LogicalOr);
    std::shared_ptr<ast::BooleanLiteral> left = std::dynamic_pointer_cast<ast::BooleanLiteral>(binExpr->left);
    REQUIRE(left);
    REQUIRE(left->value == false);
    std::shared_ptr<ast::LogicalExpression> right = std::dynamic_pointer_cast<ast::LogicalExpression>(binExpr->right);
    REQUIRE(right);
    REQUIRE(right->_operator->type == TokenType::LogicalAnd);
    std::shared_ptr<ast::BooleanLiteral> rightLeft = std::dynamic_pointer_cast<ast::BooleanLiteral>(right->left);
    REQUIRE(rightLeft);
    REQUIRE(rightLeft->value == true);
    std::shared_ptr<ast::BooleanLiteral> rightRight = std::dynamic_pointer_cast<ast::BooleanLiteral>(right->right);
    REQUIRE(rightRight);
    REQUIRE(rightRight->value == false);
}