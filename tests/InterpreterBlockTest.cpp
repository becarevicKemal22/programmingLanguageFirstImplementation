//
// Created by kemal on 11/17/2023.
//

#include <catch2/catch_test_macros.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"
#include "BooleanValue.h"

TEST_CASE("Correctly interprets block statement", "[interpreter][block]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = netacno;"
                         "{"
                         "a = tacno;"
                         "}";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Boolean);
    std::shared_ptr<BooleanValue> value = std::dynamic_pointer_cast<BooleanValue>(a->second.first);
    REQUIRE(value->value == true);
}

TEST_CASE("Correctly shadows variables", "[interpreter][block][scope]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    std::string source = "var a = netacno;"
                         "{"
                         "var a = tacno;"
                         "}";
    ast::Program program = parser.parse(source);
    interpreter.visitProgram(&program);
    std::shared_ptr<Environment> env = interpreter.environment;
    auto a = env->variables.find("a");
    REQUIRE(a->second.first->type == ValueType::Boolean);
    std::shared_ptr<BooleanValue> value = std::dynamic_pointer_cast<BooleanValue>(a->second.first);
    REQUIRE(value->value == false);
}