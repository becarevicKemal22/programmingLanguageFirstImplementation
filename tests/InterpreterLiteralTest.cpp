//
// Created by kemal on 11/11/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <memory>
#include <string>
#include "Interpreter.h"
#include "Parser.h"
#include "NullLiteral.h"
#include "NullValue.h"
#include "MockErrorPrinter.h"
#include "NumericValue.h"

TEST_CASE("Outputs null literals", "[interpreter][literal][null]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Returns null literal when prazno is input"){
        std::string source = "prazno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Null);
        REQUIRE(result->stringify() == "prazno");
    }
    SECTION("Returns null when source is empty"){
        std::string source = "";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Null);
        REQUIRE(result->stringify() == "prazno");
    }
}

TEST_CASE("Outputs numeric literals", "[interpreter][literal][number]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    SECTION("Returns number value when integer is input"){
        std::string source = "1;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(1.0));
        REQUIRE(result->stringify() == "1");
    }
    SECTION("Returns number value when double is input"){
        std::string source = "1.234;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(1.234));
        REQUIRE(result->stringify() == "1.234");
    }
}

TEST_CASE("Outputs boolean literals", "[interpreter][literal][boolean]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    SECTION("Returns true value when tacno is input"){
        std::string source = "tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        REQUIRE(result->stringify() == "tacno");
    }
    SECTION("Returns false value when netacno is input"){
        std::string source = "netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        REQUIRE(result->stringify() == "netacno");
    }
}

TEST_CASE("Outputs string literals", "[interpreter][literal][string]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    SECTION("Returns string value"){
        std::string source = "\"Some string\";";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::String);
        REQUIRE(result->stringify() == "Some string");
    }
}