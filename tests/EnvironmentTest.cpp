//
// Created by kemal on 11/14/2023.
//

#include <catch2/catch_test_macros.hpp>

#include "Environment.h"
#include "StringValue.h"
#include "NullValue.h"
#include "exceptions/UndeclaredVariable.h"
#include "exceptions/VariableRedeclaration.h"
#include "exceptions/ConstReassignment.h"

std::shared_ptr<Token> makeToken(std::string name){
    return std::make_shared<Token>(TokenType::Identifikator, name, 1, 0);
}

TEST_CASE("Correctly sets a variable"){
    Environment env;
    std::shared_ptr<StringValue> value = std::make_shared<StringValue>("Mystring");

    env.define(makeToken("myVar"), value, false);
    std::shared_ptr<Token> token = std::make_shared<Token>(TokenType::Identifikator, "myVar", 1, 0);
    RuntimeValuePtr val = env.get(token);
    std::shared_ptr<StringValue> castValue = std::dynamic_pointer_cast<StringValue>(val);
    REQUIRE(castValue);
    REQUIRE(castValue->value == "Mystring");
}

TEST_CASE("Throws UndeclaredVariable exception on invalid variable identifier"){
    Environment env;
    std::shared_ptr<Token> token = makeToken("myVar");
    REQUIRE_THROWS_AS(env.get(token), UndeclaredVariable);
}

TEST_CASE("Throws VariableRedeclaration exception when variable is redeclared"){
    Environment env;
    std::shared_ptr<StringValue> value = std::make_shared<StringValue>("Mystring");
    std::shared_ptr<StringValue> value2 = std::make_shared<StringValue>("Mystring2");
    env.define(makeToken("myVar"), value, false);
    REQUIRE_THROWS_AS(env.define(makeToken("myVar"), value2, false), VariableRedeclaration);
}

TEST_CASE("Throws error when trying to reassign const"){
    Environment env;
    env.define(makeToken("constant"), {}, true);
}

TEST_CASE("Correctly assigns a variable"){
    Environment env;
    std::shared_ptr<NullValue> value = std::make_shared<NullValue>();
    std::shared_ptr<Token> token = makeToken("var");
    env.define(token, value, false);
    std::shared_ptr<StringValue> value2 = std::make_shared<StringValue>("Mystring");
    REQUIRE_NOTHROW(env.assign(token, value2));
    RuntimeValuePtr val = env.get(token);
    std::shared_ptr<StringValue> castValue = std::dynamic_pointer_cast<StringValue>(val);
    REQUIRE(castValue);
    REQUIRE(castValue->value == "Mystring");
}

TEST_CASE("Throws on undeclared variable reassignment"){
    Environment env;
    std::shared_ptr<NullValue> value = std::make_shared<NullValue>();
    REQUIRE_THROWS_AS(env.assign(makeToken("var"), value), UndeclaredVariable);
}

TEST_CASE("Throws when constant is tried to be reassigned"){
    Environment env;
    std::shared_ptr<NullValue> nullValue = std::make_shared<NullValue>();
    std::shared_ptr<Token> token = makeToken("konstanta");
    env.define(token, nullValue, true);
    REQUIRE_THROWS_AS(env.assign(token, nullValue), ConstReassignment);
}