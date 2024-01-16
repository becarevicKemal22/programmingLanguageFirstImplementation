//
// Created by kemal on 1/16/2024.
//

#include <catch2/catch_test_macros.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"

TEST_CASE("Runs while loop correctly", "[interpreter][conditionals]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var x = 0;"
                         "dok(x < 10) x = x + 1;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto x = env->variables.find("x");
    REQUIRE(x->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(x->second.first);
    REQUIRE(value->value == 10);
}

TEST_CASE("Doesn't run loop on initial false condition", "[interpreter][conditionals]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var x = 0;"
                         "dok(netacno) x = \"Entered\";";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("x");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 0);
}

TEST_CASE("Runs for loop correctly"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var x = 0;"
                         "za(var i = 0; i < 10; i = i + 1) x = x + 1;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("x");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 10);
}