//
// Created by kemal on 11/11/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"

TEST_CASE("Computes arithmetic operations", "[interpreter][binaryExpression][arithmetic]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Computes addition"){
        std::string source = "1 + 2";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(3.0));
        REQUIRE(result->stringify() == "3");
    }
    SECTION("Computes subtraction"){
        std::string source = "1 - 2";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(-1.0));
        REQUIRE(result->stringify() == "-1");
    }
    SECTION("Computes multiplication"){
        std::string source = "2 * 3";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(6.0));
        REQUIRE(result->stringify() == "6");
    }
    SECTION("Computes division"){
        std::string source = "6 / 3";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(2.0));
        REQUIRE(result->stringify() == "2");
    }
    SECTION("Computes remainder"){
        std::string source = "7 % 3";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(1.0));
        REQUIRE(result->stringify() == "1");
    }
    SECTION("Computes complex arithmetic expression"){
        std::string source = "(6 / 3 + 5)/2 - (10 % 3)";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(2.5));
        REQUIRE(result->stringify() == "2.5");
    }
}