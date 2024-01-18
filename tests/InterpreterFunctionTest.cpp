//
// Created by kemal on 1/17/2024.
//

#include <catch2/catch_test_macros.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"
#include "Function.h"

TEST_CASE("Executes empty function", "[interpreter][function]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "funkcija f(){}"
                         "f();";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto f = env->variables.find("f");
    REQUIRE(f->second.first->type == ValueType::Function);
    std::shared_ptr<Function> function = std::dynamic_pointer_cast<Function>(f->second.first);
    REQUIRE(function->timesCalled() == 1);
}

TEST_CASE("Executes function with return statement") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "funkcija f(){"
                         "    vrati 5;"
                         "}"
                         "var a = f();";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto f = env->variables.find("f");
    REQUIRE(f->second.first->type == ValueType::Function);
    std::shared_ptr<Function> function = std::dynamic_pointer_cast<Function>(f->second.first);
    REQUIRE(function->timesCalled() == 1);
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Number);
    std::shared_ptr<NumericValue> numericValue = std::dynamic_pointer_cast<NumericValue>(a->second.first);
    REQUIRE(numericValue->value == 5);
}