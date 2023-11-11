//
// Created by kemal on 11/11/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"

TEST_CASE("Negates number value", "[interpreter][unary][number]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    SECTION("Negates integer number value"){
        std::string source = "-1";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(-1.0));
        REQUIRE(result->stringify() == "-1");
    }
    SECTION("Negates double number value"){
        std::string source = "-1.234";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Number);
        std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(result);
        REQUIRE_THAT(numericValue->value, Catch::Matchers::WithinRel(-1.234));
        REQUIRE(result->stringify() == "-1.234");
    }
}