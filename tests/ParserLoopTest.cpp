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
#include "BypassExpressionStatement.h"
#include "VarDeclaration.h"
#include "AssignmentExpression.h"
#include "BinaryExpression.h"

TEST_CASE("Parses while loop with block", "[Parser][Loop][While]") {
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

TEST_CASE("Parses while loop with single statement", "[Parser][Loop][While]") {
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

TEST_CASE("Parses basic for loop", "[Parser][Loop][For]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "za(var i = 0; i < 10; i = i + 1){print i;}";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::BlockStatement> enclosingBlock = std::dynamic_pointer_cast<ast::BlockStatement>(body[0]);
    REQUIRE(enclosingBlock);
    std::shared_ptr<ast::VarDeclaration> initializer = std::dynamic_pointer_cast<ast::VarDeclaration>(enclosingBlock->statements[0]);
    REQUIRE(initializer);
    std::shared_ptr<ast::WhileStatement> whileStmt = std::dynamic_pointer_cast<ast::WhileStatement>(enclosingBlock->statements[1]);
    REQUIRE(whileStmt);
    std::shared_ptr<ast::BlockStatement> whileBody = std::dynamic_pointer_cast<ast::BlockStatement>(whileStmt->body);
    REQUIRE(whileBody);
    std::shared_ptr<ast::AssignmentExpression> increment = std::dynamic_pointer_cast<ast::AssignmentExpression>(whileBody->statements[1]);
    REQUIRE(increment);

}