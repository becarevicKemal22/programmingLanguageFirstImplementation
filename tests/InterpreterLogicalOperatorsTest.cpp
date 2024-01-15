//
// Created by kemal on 1/16/2024.
//

#include <catch2/catch_test_macros.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "BooleanValue.h"
#include "StringValue.h"
#include "NullValue.h"

TEST_CASE("Computes logical or expressions", "[interpreter][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Single true or expression") {
        std::string source = "tacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Single true or expression 2") {
        std::string source = "netacno || tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Single false or expression") {
        std::string source = "netacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained false or expression") {
        std::string source = "netacno || netacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained true or expression") {
        std::string source = "tacno || netacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Chained true or expression 2") {
        std::string source = "netacno || tacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Chained true or expression 3") {
        std::string source = "netacno || netacno || tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
}

TEST_CASE("Computes logical and expressions", "[interpreter][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Single true and expression") {
        std::string source = "tacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Single false and expression") {
        std::string source = "tacno && netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Single false and expression 2") {
        std::string source = "netacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained false and expression") {
        std::string source = "netacno && tacno && netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained false and expression 2") {
        std::string source = "netacno && tacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained false and expression 3") {
        std::string source = "tacno && netacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Chained true and expression") {
        std::string source = "tacno && tacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
}

TEST_CASE("Computes mixed logical expressions", "[interpreter][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Mixed expression 1") {
        std::string source = "netacno || tacno && netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Mixed expression 2") {
        std::string source = "netacno || tacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Mixed expression 3") {
        std::string source = "tacno || netacno && tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Mixed expression 4") {
        std::string source = "netacno && netacno || tacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
    SECTION("Mixed expression 5") {
        std::string source = "netacno && tacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(!booleanValue->value);
    }
    SECTION("Mixed expression 6") {
        std::string source = "tacno && tacno || netacno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Boolean);
        std::shared_ptr<BooleanValue> booleanValue = std::dynamic_pointer_cast<BooleanValue>(result);
        REQUIRE(booleanValue);
        REQUIRE(booleanValue->value);
    }
}

TEST_CASE("Returns runtime values with appropriate thruthyness", "[interpreter][LogicalExpression]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("String and number or expression") {
        std::string source = " \"\" || 2;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::String);
        std::shared_ptr<StringValue> stringValue = std::dynamic_pointer_cast<StringValue>(result);
        REQUIRE(stringValue);
        REQUIRE(stringValue->value == "");
    }
    SECTION("Number and null and expression") {
        std::string source = "15 && prazno;";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Null);
        std::shared_ptr<NullValue> nullValue = std::dynamic_pointer_cast<NullValue>(result);
        REQUIRE(nullValue);
    }
    SECTION("Null and string and expression") {
        std::string source = "prazno && \"\";";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::Null);
        std::shared_ptr<NullValue> nullValue = std::dynamic_pointer_cast<NullValue>(result);
        REQUIRE(nullValue);
    }
    SECTION("Null and string or expression") {
        std::string source = "prazno || \"\";";
        ast::Program program = parser.parse(source);
        RuntimeValuePtr result = interpreter.visitProgram(&program);
        REQUIRE(result->type == ValueType::String);
        std::shared_ptr<StringValue> stringValue = std::dynamic_pointer_cast<StringValue>(result);
        REQUIRE(stringValue);
        REQUIRE(stringValue->value == "");
    }
}