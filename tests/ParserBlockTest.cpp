//
// Created by kemal on 11/17/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "BlockStatement.h"
#include "Statement.h"
#include "BypassExpressionStatement.h"
#include "MockErrorPrinter.h"
#include "Parser.h"
#include "VarDeclaration.h"
#include "AssignmentExpression.h"
#include "PrintStatement.h"

TEST_CASE("Parses block statement", "[parser][block][statement]"){
    std::string source = "{"
                         "  var a = 5;"
                         "  a = 10;"
                         "  print a;"
                         "}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::BlockStatement> blockStatement = std::dynamic_pointer_cast<ast::BlockStatement>(program.body[0]);
    REQUIRE(blockStatement);
    REQUIRE(blockStatement->statements.size() == 3);
    std::shared_ptr<ast::VarDeclaration> varDeclaration = std::dynamic_pointer_cast<ast::VarDeclaration>(blockStatement->statements[0]);
    REQUIRE(varDeclaration);
    REQUIRE(varDeclaration->identifier->value == "a");
    std::shared_ptr<ast::AssignmentExpression> assignmentExpression = bypassExpressionStatement<ast::AssignmentExpression>(blockStatement->statements[1]);
    REQUIRE(assignmentExpression);
    std::shared_ptr<ast::PrintStatement> printStatement = std::dynamic_pointer_cast<ast::PrintStatement>(blockStatement->statements[2]);
    REQUIRE(printStatement);
}

TEST_CASE("Requires end } at block statement", "[parser][block][statement]"){
    std::string source = "{"
                         "  var a = 5;"
                         "  a = 10;"
                         "  print a;";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}