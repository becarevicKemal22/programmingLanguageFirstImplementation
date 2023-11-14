//
// Created by kemal on 11/13/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "Parser.h"
#include "Lexer.h"
#include "MockErrorPrinter.h"
#include "VarDeclaration.h"

TEST_CASE("Parses valid variable declarations", "[Parser][Declaration][Variables]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    SECTION("'Var' variable declaration with initializer"){
        std::string source = "var x = 5;";
        ast::Program program = parser.parse(source);
        REQUIRE_FALSE(parser.hadError);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::VarDeclaration> declaration = std::dynamic_pointer_cast<ast::VarDeclaration>(body[0]);
        REQUIRE(declaration);
        REQUIRE(declaration->identifier->value == "x");
        REQUIRE(!declaration->isConst);
        std::shared_ptr<ast::NumericLiteral> initializer = std::dynamic_pointer_cast<ast::NumericLiteral>(declaration->initializer);
        REQUIRE(initializer);
        REQUIRE_THAT(initializer->number, Catch::Matchers::WithinRel(5.0));
    }
    SECTION("'Var' variable declaration with binary expression initializer"){
        std::string source = "var myVar = 5 + 2 / 10;";
        ast::Program program = parser.parse(source);
        REQUIRE_FALSE(parser.hadError);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::VarDeclaration> declaration = std::dynamic_pointer_cast<ast::VarDeclaration>(body[0]);
        REQUIRE(declaration);
        REQUIRE(declaration->identifier->value == "myVar");
        REQUIRE(!declaration->isConst);
        std::shared_ptr<ast::BinaryExpression> initializer = std::dynamic_pointer_cast<ast::BinaryExpression>(declaration->initializer);
        REQUIRE(initializer);
        REQUIRE(initializer->_operator->value == "+");
        std::shared_ptr<ast::BinaryExpression> rhs = std::dynamic_pointer_cast<ast::BinaryExpression>(initializer->right);
        REQUIRE(rhs);
        REQUIRE(rhs->_operator->value == "/");
    }
    SECTION("'Var' variable declaration with no initializer"){
        std::string source = "var emptyVar;";
        ast::Program program = parser.parse(source);
        REQUIRE_FALSE(parser.hadError);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::VarDeclaration> declaration = std::dynamic_pointer_cast<ast::VarDeclaration>(body[0]);
        REQUIRE(declaration);
        REQUIRE(declaration->identifier->value == "emptyVar");
        REQUIRE(declaration->initializer == nullptr);
        REQUIRE(!declaration->isConst);
    }
    SECTION("'Konst' variable declaration"){
        std::string source = "konst konstVar = 5;";
        ast::Program program = parser.parse(source);
        REQUIRE_FALSE(parser.hadError);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::VarDeclaration> declaration = std::dynamic_pointer_cast<ast::VarDeclaration>(body[0]);
        REQUIRE(declaration);
        REQUIRE(declaration->identifier->value == "konstVar");
        REQUIRE(declaration->isConst);
        std::shared_ptr<ast::NumericLiteral> initializer = std::dynamic_pointer_cast<ast::NumericLiteral>(declaration->initializer);
        REQUIRE(initializer);
    }
}

TEST_CASE("Prints errors on invalid variable declarations", "[Parser][Declaration][Variables][Errors]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    SECTION("Prints error when variable declaration is not ended with semicolon (w/ initializer)") {
        std::string source = "var x = 5";
        ast::Program program = parser.parse(source);
        REQUIRE(parser.hadError);
    }
    SECTION("Prints error when variable declaration is not ended with semicolon (wo/ initializer)"){
        std::string source = "var x";
        ast::Program program = parser.parse(source);
        REQUIRE(parser.hadError);
    }
    SECTION("Prints error when no identifier is provided"){
        std::string source = "var;";
        ast::Program program = parser.parse(source);
        REQUIRE(parser.hadError);
    }
    SECTION("Prints error when no identifier is provided with initializer"){
        std::string source = "var  = 5;";
        ast::Program program = parser.parse(source);
        REQUIRE(parser.hadError);
    }
    SECTION("Prints error when no initializer is provided after equals token"){
        std::string source = "var x = ;";
        ast::Program program = parser.parse(source);
        REQUIRE(parser.hadError);
    }

}