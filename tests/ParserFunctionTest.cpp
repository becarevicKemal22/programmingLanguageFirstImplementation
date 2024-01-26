//
// Created by kemal on 1/17/2024.
//

#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "MockErrorPrinter.h"
#include "Parser.h"
#include "FunctionDeclaration.h"
#include "PrintStatement.h"
#include "CallExpression.h"
#include "BypassExpressionStatement.h"
#include "Identifier.h"
#include "StringLiteral.h"
#include "ReturnStatement.h"
#include "BinaryExpression.h"

TEST_CASE("Parses function declaration statement", "[parser][function][statement]"){
    std::string source = "funkcija f(){}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.empty());
    REQUIRE(functionDeclaration->body.empty());
}

TEST_CASE("Parses function declaration statement with params", "[parser][function][statement]"){
    std::string source = "funkcija f(x,y){}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.size() == 2);
    REQUIRE(functionDeclaration->params[0]->value == "x");
    REQUIRE(functionDeclaration->params[1]->value == "y");
    REQUIRE(functionDeclaration->body.empty());
}

TEST_CASE("Parses function declaration statement with body", "[parser][function][statement]"){
    std::string source = "funkcija f(){"
                         "    print x;"
                         "}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.empty());
    REQUIRE(functionDeclaration->body.size() == 1);
    std::shared_ptr<ast::PrintStatement> printStatement = std::dynamic_pointer_cast<ast::PrintStatement>(functionDeclaration->body[0]);
    REQUIRE(printStatement);
}

TEST_CASE("Has error when no identifier is provided", "[parser][function][statement]"){
    std::string source = "funkcija (x){}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Requires block after function declaration", "[parser][function][statement]"){
    std::string source = "funkcija f()";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Requires parenthesis after function name", "[parser][function][statement]"){
    std::string source = "funkcija f{}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Parses function call", "[parser][function][expression]"){
    std::string source = "f();";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::CallExpression> callExpression = bypassExpressionStatement<ast::CallExpression>(program.body[0]);
    REQUIRE(callExpression);
    std::shared_ptr<ast::Identifier> identifier = std::dynamic_pointer_cast<ast::Identifier>(callExpression->callee);
    REQUIRE(identifier);
    REQUIRE(identifier->name == "f");
    REQUIRE(callExpression->arguments.empty());
}

TEST_CASE("Parses function call with arguments", "[parser][function][expression]"){
    std::string source = "f(\"test\");";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::CallExpression> callExpression = bypassExpressionStatement<ast::CallExpression>(program.body[0]);
    REQUIRE(callExpression);
    std::shared_ptr<ast::Identifier> identifier = std::dynamic_pointer_cast<ast::Identifier>(callExpression->callee);
    REQUIRE(identifier);
    REQUIRE(identifier->name == "f");
    REQUIRE(callExpression->arguments.size() == 1);
    std::shared_ptr<ast::StringLiteral> literal = std::dynamic_pointer_cast<ast::StringLiteral>(callExpression->arguments[0]);
    REQUIRE(literal);
    REQUIRE(literal->value == "test");
}

TEST_CASE("Parses function call with another call as argument", "[parser][function][expression]"){
    std::string source = "f(g());";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::CallExpression> callExpression = bypassExpressionStatement<ast::CallExpression>(program.body[0]);
    REQUIRE(callExpression);
    std::shared_ptr<ast::Identifier> identifier = std::dynamic_pointer_cast<ast::Identifier>(callExpression->callee);
    REQUIRE(identifier);
    REQUIRE(identifier->name == "f");
    REQUIRE(callExpression->arguments.size() == 1);
    std::shared_ptr<ast::CallExpression> innerCall = std::dynamic_pointer_cast<ast::CallExpression>(callExpression->arguments[0]);
    REQUIRE(innerCall);
    std::shared_ptr<ast::Identifier> innerIdentifier = std::dynamic_pointer_cast<ast::Identifier>(innerCall->callee);
    REQUIRE(innerIdentifier);
    REQUIRE(innerIdentifier->name == "g");
    REQUIRE(innerCall->arguments.empty());
}

TEST_CASE("Parses function with empty return statement", "[parser][function][return]"){
    std::string source = "funkcija f(){vrati;}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.empty());
    REQUIRE(functionDeclaration->body.size() == 1);
    std::shared_ptr<ast::ReturnStatement> returnStatement = std::dynamic_pointer_cast<ast::ReturnStatement>(functionDeclaration->body[0]);
    REQUIRE(returnStatement);
    REQUIRE(returnStatement->value == nullptr);
}

TEST_CASE("Parses function with return of identifier", "[parser][function][return]"){
    std::string source = "funkcija f(){vrati a;}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.empty());
    REQUIRE(functionDeclaration->body.size() == 1);
    std::shared_ptr<ast::ReturnStatement> returnStatement = std::dynamic_pointer_cast<ast::ReturnStatement>(functionDeclaration->body[0]);
    REQUIRE(returnStatement);
    std::shared_ptr<ast::Identifier> identifier = std::dynamic_pointer_cast<ast::Identifier>(returnStatement->value);
    REQUIRE(identifier);
    REQUIRE(identifier->name == "a");
}

TEST_CASE("Parses function with return of binary expression", "[parser][function][return]"){
    std::string source = "funkcija f(){vrati a > b;}";
    MockErrorPrinter printer;
    Parser parser(printer);
    ast::Program program = parser.parse(source);
    REQUIRE(program.body.size() == 1);
    std::shared_ptr<ast::FunctionDeclaration> functionDeclaration = std::dynamic_pointer_cast<ast::FunctionDeclaration>(program.body[0]);
    REQUIRE(functionDeclaration);
    REQUIRE(functionDeclaration->name->value == "f");
    REQUIRE(functionDeclaration->params.empty());
    REQUIRE(functionDeclaration->body.size() == 1);
    std::shared_ptr<ast::ReturnStatement> returnStatement = std::dynamic_pointer_cast<ast::ReturnStatement>(functionDeclaration->body[0]);
    REQUIRE(returnStatement);
    std::shared_ptr<ast::BinaryExpression> binaryExpression = std::dynamic_pointer_cast<ast::BinaryExpression>(returnStatement->value);
    REQUIRE(binaryExpression);
    std::shared_ptr<ast::Identifier> identifierA = std::dynamic_pointer_cast<ast::Identifier>(binaryExpression->left);
    REQUIRE(identifierA);
    REQUIRE(identifierA->name == "a");
    std::shared_ptr<ast::Identifier> identifierB = std::dynamic_pointer_cast<ast::Identifier>(binaryExpression->right);
    REQUIRE(identifierB);
    REQUIRE(identifierB->name == "b");
    REQUIRE(binaryExpression->_operator->type == TokenType::Greater);
}

TEST_CASE("Requires semicolon after empty return"){
    std::string source = "funkcija f(){vrati}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}

TEST_CASE("Requires semicolon after identifier return"){
    std::string source = "funkcija f(){vrati a}";
    MockErrorPrinter printer;
    Parser parser(printer);
    REQUIRE_NOTHROW(parser.parse(source));
    REQUIRE(parser.hadError);
    REQUIRE(printer.numberOfTimesCalled);
}