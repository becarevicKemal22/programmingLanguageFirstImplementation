//
// Created by kemal on 11/13/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "Interpreter.h"
#include "NumericValue.h"
#include "NullValue.h"

TEST_CASE("Correctly declares variables", "[interpreter][variable][declaration]") {
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);

    SECTION("Correctly declares variable with an initializer") {
        std::string source = "var a = 5;";
        ast::Program program = parser.parse(source);
        interpreter.visitProgram(&program);
        auto it = interpreter.environment.variables.find("a");
        REQUIRE(it != interpreter.environment.variables.end());
        REQUIRE(it->second.second == false);
        std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(it->second.first);
        REQUIRE(value);
        REQUIRE_THAT(value->value, Catch::Matchers::WithinRel(5.0));
    }
    SECTION("Correctly declares variable without an initializer"){
        std::string source = "var a;";
        ast::Program program = parser.parse(source);
        interpreter.visitProgram(&program);
        auto it = interpreter.environment.variables.find("a");
        REQUIRE(it != interpreter.environment.variables.end());
        REQUIRE(it->second.second == false);
        std::shared_ptr<NullValue> value = std::dynamic_pointer_cast<NullValue>(it->second.first);
        REQUIRE(value);
    }
    SECTION("Correctly declares constant variable"){
        std::string source = "konst a = 5;";
        ast::Program program = parser.parse(source);
        interpreter.visitProgram(&program);
        auto it = interpreter.environment.variables.find("a");
        REQUIRE(it != interpreter.environment.variables.end());
        REQUIRE(it->second.second == true);
        std::shared_ptr<NumericValue> value = std::dynamic_pointer_cast<NumericValue>(it->second.first);
        REQUIRE(value);
        REQUIRE_THAT(value->value, Catch::Matchers::WithinRel(5.0));
    }
}

TEST_CASE("Handles errors", "[interpreter][variable][declaration]"){
    MockErrorPrinter printer;
    Parser parser(printer);
    Interpreter interpreter(printer);
    SECTION("Handles variable redeclaration"){
        std::string source = "var a; var a;";
        ast::Program program = parser.parse(source);
        REQUIRE_NOTHROW(interpreter.visitProgram(&program));
        REQUIRE(printer.numberOfTimesCalled);
    }
    SECTION("Handles undefined identifiers"){
        std::string source = "print a;";
        ast::Program program = parser.parse(source);
        REQUIRE_NOTHROW(interpreter.visitProgram(&program));
        REQUIRE(printer.numberOfTimesCalled);
    }
}