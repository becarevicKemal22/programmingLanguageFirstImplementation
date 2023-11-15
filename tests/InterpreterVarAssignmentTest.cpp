//
// Created by kemal on 11/15/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"

TEST_CASE("Correctly assigns variables") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    std::string source = "var a = 5; a = 10;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    auto it = interpreter.environment.variables.find("a");
    REQUIRE(it != interpreter.environment.variables.end());
    REQUIRE(it->second.second == false);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(it->second.first);
    REQUIRE(value);
    REQUIRE_THAT(value->value, Catch::Matchers::WithinRel(10.0));
}

TEST_CASE("Handles assignment errors") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Handles undeclared variable assignment") {
        std::string source = "a = 10;";
        ast::Program program = parser.parse(source);
        REQUIRE_NOTHROW(interpreter.visitProgram(&program));
        REQUIRE(printer.numberOfTimesCalled);
    }
    SECTION("Handles konst reassignment") {
        std::string source = "konst a = 10; a = 5;";
        ast::Program program = parser.parse(source);
        REQUIRE_NOTHROW(interpreter.visitProgram(&program));
        REQUIRE(printer.numberOfTimesCalled);
    }
}