//
// Created by kemal on 11/7/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include "Parser.h"
#include "MockErrorPrinter.h"
#include "Program.h"
#include "Statement.h"
#include "NumericLiteral.h"
#include "BinaryExpression.h"
#include "NullLiteral.h"
#include "BooleanLiteral.h"
#include "GroupingExpression.h"
#include "UnaryExpression.h"

TEST_CASE("Correctly parses primary expressions", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "5.45232 ident 21 variableName2 prazno tacno netacno";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 7);

    std::shared_ptr<ast::NumericLiteral> numLit = std::dynamic_pointer_cast<ast::NumericLiteral>(body[0]);
    REQUIRE(numLit);
    CHECK_THAT(numLit->number, Catch::Matchers::WithinRel(5.45232));

    std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(body[1]);
    REQUIRE(ident);
    CHECK(ident->name == "ident");

    numLit = std::dynamic_pointer_cast<ast::NumericLiteral>(body[2]);
    REQUIRE(numLit);
    CHECK_THAT(numLit->number, Catch::Matchers::WithinRel(21.0));

    ident = std::dynamic_pointer_cast<ast::Identifier>(body[3]);
    REQUIRE(ident);
    CHECK(ident->name == "variableName2");

    std::shared_ptr<ast::NullLiteral> nullLiteral = std::dynamic_pointer_cast<ast::NullLiteral>(body[4]);
    REQUIRE(nullLiteral);

    std::shared_ptr<ast::BooleanLiteral> booleanLiteral = std::dynamic_pointer_cast<ast::BooleanLiteral>(body[5]);
    REQUIRE(booleanLiteral);
    CHECK(booleanLiteral->value);

    booleanLiteral = std::dynamic_pointer_cast<ast::BooleanLiteral>(body[6]);
    REQUIRE(booleanLiteral);
    CHECK_FALSE(booleanLiteral->value);
}

TEST_CASE("Basic binary expression", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "5 + 10";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::BinaryExpression> binExpr = std::dynamic_pointer_cast<ast::BinaryExpression>(body[0]);
    REQUIRE(binExpr);
    std::shared_ptr<ast::NumericLiteral> left = std::dynamic_pointer_cast<ast::NumericLiteral>(binExpr->left);
    REQUIRE(left);
    CHECK(left->number == 5);
    std::shared_ptr<ast::NumericLiteral> right = std::dynamic_pointer_cast<ast::NumericLiteral>(binExpr->right);
    REQUIRE(right);
    CHECK(right->number == 10);
}

TEST_CASE("Groups expression", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "2 * (3 - 1)";
    ast::Program program = parser.parse(source);
    std::vector<std::shared_ptr<ast::Statement>> body = program.body;
    REQUIRE(body.size() == 1);
    std::shared_ptr<ast::BinaryExpression> binExpr = std::dynamic_pointer_cast<ast::BinaryExpression>(body[0]);
    REQUIRE(binExpr);
    std::shared_ptr<ast::GroupingExpression> groupingExpression = std::dynamic_pointer_cast<ast::GroupingExpression>(
            binExpr->right);
    REQUIRE(groupingExpression);
    std::shared_ptr<ast::BinaryExpression> rhs = std::dynamic_pointer_cast<ast::BinaryExpression>(
            groupingExpression->expr);
    REQUIRE(rhs);
    CHECK(rhs->_operator->value == "-");
}

TEST_CASE("Handles invalid group expressions", "[Parser][GroupingExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    const std::string source = "(5 + 10";
    parser.parse(source);
    REQUIRE(printer.numberOfTimesCalled == 1);
    REQUIRE(parser.hadError);

}

TEST_CASE("Parses unary expressions", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);

    SECTION("Parses bang unary", "[Parser]") {
        const std::string source = "!tacno";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);

        std::shared_ptr<ast::UnaryExpression> unary = std::dynamic_pointer_cast<ast::UnaryExpression>(body[0]);
        REQUIRE(unary);
        CHECK(unary->_operator->value == "!");
        std::shared_ptr<ast::BooleanLiteral> booleanLiteral = std::dynamic_pointer_cast<ast::BooleanLiteral>(
                unary->expr);
        REQUIRE(booleanLiteral);
        CHECK(booleanLiteral->value);
    }SECTION("Parses minus unary") {
        const std::string source = "-(2 + 5)";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::UnaryExpression> unary = std::dynamic_pointer_cast<ast::UnaryExpression>(body[0]);
        REQUIRE(unary);
        CHECK(unary->_operator->value == "-");
        std::shared_ptr<ast::GroupingExpression> groupExpr = std::dynamic_pointer_cast<ast::GroupingExpression>(
                unary->expr);
        REQUIRE(groupExpr);
        std::shared_ptr<ast::BinaryExpression> binaryExpr = std::dynamic_pointer_cast<ast::BinaryExpression>(
                groupExpr->expr);
        REQUIRE(binaryExpr);
        CHECK(binaryExpr->_operator->value == "+");
    }
}

TEST_CASE("Parses comparison expressions", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    SECTION("Parses < expressions") {
        const std::string source = "2 < 5";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "<");
    }SECTION("Parser > expressions") {
        const std::string source = "2 > 5";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == ">");
    }SECTION("Parser <= expressions") {
        const std::string source = "2 <= 5";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "<=");
    }SECTION("Parser >= expressions") {
        const std::string source = "2 >= 5";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == ">=");
    }SECTION("Parses chained comparison") {
        const std::string source = "var1 <= var2 < var3";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "<");
        std::shared_ptr<ast::BinaryExpression> secondBinary = std::dynamic_pointer_cast<ast::BinaryExpression>(
                binaryExpression->left);
        REQUIRE(secondBinary);
        CHECK(secondBinary->_operator->value == "<=");
        std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(secondBinary->left);
        REQUIRE(ident);
        CHECK(ident->name == "var1");
        ident = std::dynamic_pointer_cast<ast::Identifier>(secondBinary->right);
        REQUIRE(ident);
        CHECK(ident->name == "var2");
        ident = std::dynamic_pointer_cast<ast::Identifier>(binaryExpression->right);
        REQUIRE(ident);
        CHECK(ident->name == "var3");
    }
}

TEST_CASE("Parses equality expressions", "[Parser]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    SECTION("Parses == expressions") {
        const std::string source = "2 == 5";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "==");
        std::shared_ptr<ast::NumericLiteral> numLit = std::dynamic_pointer_cast<ast::NumericLiteral>(
                binaryExpression->left);
        REQUIRE(numLit);
        CHECK_THAT(numLit->number, Catch::Matchers::WithinRel(2.0));
        numLit = std::dynamic_pointer_cast<ast::NumericLiteral>(binaryExpression->right);
        REQUIRE(numLit);
        CHECK_THAT(numLit->number, Catch::Matchers::WithinRel(5.0));
    }SECTION("Parses != expressions") {
        const std::string source = "tacno != netacno";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "!=");
        std::shared_ptr<ast::BooleanLiteral> boolLit = std::dynamic_pointer_cast<ast::BooleanLiteral>(
                binaryExpression->left);
        REQUIRE(boolLit);
        CHECK(boolLit->value);
        boolLit = std::dynamic_pointer_cast<ast::BooleanLiteral>(binaryExpression->right);
        REQUIRE(boolLit);
        CHECK_FALSE(boolLit->value);
    }SECTION("Parses chained equality") {
        const std::string source = "var1 == var2 != var3";
        ast::Program program = parser.parse(source);
        std::vector<std::shared_ptr<ast::Statement>> body = program.body;
        REQUIRE(body.size() == 1);
        std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(
                body[0]);
        REQUIRE(binaryExpression);
        CHECK(binaryExpression->_operator->value == "!=");
        std::shared_ptr<ast::BinaryExpression> secondBinary = std::dynamic_pointer_cast<ast::BinaryExpression>(
                binaryExpression->left);
        REQUIRE(secondBinary);
        CHECK(secondBinary->_operator->value == "==");
        std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(secondBinary->left);
        REQUIRE(ident);
        CHECK(ident->name == "var1");
        ident = std::dynamic_pointer_cast<ast::Identifier>(secondBinary->right);
        REQUIRE(ident);
        CHECK(ident->name == "var2");
        ident = std::dynamic_pointer_cast<ast::Identifier>(binaryExpression->right);
        REQUIRE(ident);
        CHECK(ident->name == "var3");
    }
}