//
// Created by kemal on 1/14/2024.
//

#include <catch2/catch_test_macros.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"

TEST_CASE("Executes then block if condition is true", "[interpreter][conditionals]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = 15;"
                         "ako a > 10 onda a = 20;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 20);
}

TEST_CASE("Does not execute else block when condition is false"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = 15;"
                         "ako a < 10 onda a = 20;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 15);
}

TEST_CASE("Does not execute else statement when condition is true"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = 15;"
                         "ako a > 10 onda a = 20;"
                         "inace a = 0;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 20);
}

TEST_CASE("Executes else statement when condition is false"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = 15;"
                         "ako a < 10 onda a = 20;"
                         "inace a = 0;";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(value->value == 0);
}