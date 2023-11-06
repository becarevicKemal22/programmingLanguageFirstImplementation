//
// Created by kemal on 05/11/2023.
//

#include <catch2/catch_test_macros.hpp>

#include <Lexer.h>
#include <MockErrorPrinter.h>

#include <iostream>

TEST_CASE("Returns correct token", "[Lexer]"){
    std::string source = "(){}[]+-*/;:.,= ==";
    MockErrorPrinter printer;
    Lexer lexer(source);
    lexer.tokenize(printer);
    CHECK(lexer.tokens.size() == 17);
    CHECK(lexer.tokens[0].type == TokenType::OpenParen);
    CHECK(lexer.tokens[1].type == TokenType::ClosedParen);
    CHECK(lexer.tokens[2].type == TokenType::OpenBrace);
    CHECK(lexer.tokens[3].type == TokenType::ClosedBrace);
    CHECK(lexer.tokens[4].type == TokenType::OpenBracket);
    CHECK(lexer.tokens[5].type == TokenType::ClosedBracket);
    CHECK(lexer.tokens[6].type == TokenType::BinarniOperator);
    CHECK(lexer.tokens[7].type == TokenType::BinarniOperator);
    CHECK(lexer.tokens[8].type == TokenType::BinarniOperator);
    CHECK(lexer.tokens[9].type == TokenType::BinarniOperator);
    CHECK(lexer.tokens[10].type == TokenType::Semicolon);
    CHECK(lexer.tokens[11].type == TokenType::Colon);
    CHECK(lexer.tokens[12].type == TokenType::Dot);
    CHECK(lexer.tokens[13].type == TokenType::Comma);
    CHECK(lexer.tokens[14].type == TokenType::Equal);
    CHECK(lexer.tokens[15].type == TokenType::DoubleEqual);
    CHECK(lexer.tokens[16].type == TokenType::Eof);
}

TEST_CASE("Ignores commments", "[Lexer]"){
    std::string source = "{} // Comment \n [";
    MockErrorPrinter printer;
    Lexer lexer(source);
    lexer.tokenize(printer);
    REQUIRE(lexer.tokens.size() == 4);
    REQUIRE(lexer.tokens[2].type == TokenType::OpenBracket);
}

TEST_CASE("Numbers lines and offsets correctly", "[Lexer]"){
    std::string source = "{ {\n    {\n\t{";
    MockErrorPrinter printer;
    Lexer lexer(source);
    lexer.tokenize(printer);
    REQUIRE(lexer.tokens.size() == 5);
    CHECK(lexer.tokens[0].line == 1);
    CHECK(lexer.tokens[0].charOffset == 0);

    CHECK(lexer.tokens[1].line == 1);
    CHECK(lexer.tokens[1].charOffset == 2);

    CHECK(lexer.tokens[2].line == 2);
    CHECK(lexer.tokens[2].charOffset == 5);

    CHECK(lexer.tokens[3].line == 3);
    CHECK(lexer.tokens[3].charOffset == 5);
}

TEST_CASE("Throws and outputs error on unrecognized token", "[Lexer]"){
    std::string source = "`";
    MockErrorPrinter printer;
    Lexer lexer(source);
    REQUIRE_THROWS(lexer.tokenize(printer));
    REQUIRE(printer.numberOfTimesCalled == 1);
}

TEST_CASE("Correctly interprets numbers", "[Lexer]"){
    std::string source = "3.25 5";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try{
        lexer.tokenize(printer);
    }catch(std::runtime_error& err){
        std::cout << err.what() << "\n";
    }
    REQUIRE(lexer.tokens.size() == 3);
    REQUIRE(lexer.tokens[0].type == TokenType::Broj);
    REQUIRE(lexer.tokens[0].value == "3.25");
    REQUIRE(lexer.tokens[1].type == TokenType::Broj);
    REQUIRE(lexer.tokens[1].value == "5");
}

TEST_CASE("Correctly tokenizes identifiers", "[Lexer]"){
    std::string source = "varijabla var2";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try{
        lexer.tokenize(printer);
    }catch(std::runtime_error& err){
        std::cout << err.what() << "\n";
    }
    REQUIRE(lexer.tokens.size() == 3);
    CHECK(lexer.tokens[0].type == TokenType::Identifikator);
    CHECK(lexer.tokens[0].value == "varijabla");
    CHECK(lexer.tokens[1].type == TokenType::Identifikator);
    CHECK(lexer.tokens[1].value == "var2");
}

TEST_CASE("Correctly tokenizes keywords", "[Lexer]"){
    std::string source = "var konst ako dok";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try{
        lexer.tokenize(printer);
    }catch(std::runtime_error& err){
        std::cout << err.what() << "\n";
    }
    REQUIRE(lexer.tokens.size() == 5);
    CHECK(lexer.tokens[0].type == TokenType::Var);
    CHECK(lexer.tokens[0].value == "var");
    CHECK(lexer.tokens[1].type == TokenType::Konst);
    CHECK(lexer.tokens[1].value == "konst");
    CHECK(lexer.tokens[2].type == TokenType::Ako);
    CHECK(lexer.tokens[2].value == "ako");
    CHECK(lexer.tokens[3].type == TokenType::Dok);
    CHECK(lexer.tokens[3].value == "dok");
}

TEST_CASE("Tokenizes variable declaration", "[Lexer]"){
    std::string source = "var var2 = 5.36;";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try{
        lexer.tokenize(printer);
    }catch(std::runtime_error& err){
        std::cout << err.what() << "\n";
    }
    REQUIRE(lexer.tokens.size() == 6);
    CHECK(lexer.tokens[0].type == TokenType::Var);
    CHECK(lexer.tokens[0].value == "var");
    CHECK(lexer.tokens[1].type == TokenType::Identifikator);
    CHECK(lexer.tokens[1].value == "var2");
    CHECK(lexer.tokens[2].type == TokenType::Equal);
    CHECK(lexer.tokens[2].value == "=");
    CHECK(lexer.tokens[3].type == TokenType::Broj);
    CHECK(lexer.tokens[3].value == "5.36");
    CHECK(lexer.tokens[4].type == TokenType::Semicolon);
    CHECK(lexer.tokens[4].value == ";");
}

TEST_CASE("Program sample", "[Lexer]"){
    std::string source = "var a = 5;\n"
                         "ako(a == 5){\n"
                         "    a = 10;\n"
                         "}";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try{
        lexer.tokenize(printer);
    }catch(std::runtime_error& err){
        std::cout << err.what() << "\n";
    }
    REQUIRE(lexer.tokens.size() == 18);
    CHECK(lexer.tokens[0].type == TokenType::Var);
    CHECK(lexer.tokens[0].value == "var");
    CHECK(lexer.tokens[1].type == TokenType::Identifikator);
    CHECK(lexer.tokens[1].value == "a");
    CHECK(lexer.tokens[2].type == TokenType::Equal);
    CHECK(lexer.tokens[2].value == "=");
    CHECK(lexer.tokens[3].type == TokenType::Broj);
    CHECK(lexer.tokens[3].value == "5");
    CHECK(lexer.tokens[4].type == TokenType::Semicolon);
    CHECK(lexer.tokens[4].value == ";");
    CHECK(lexer.tokens[5].type == TokenType::Ako);
    CHECK(lexer.tokens[5].value == "ako");
    CHECK(lexer.tokens[6].type == TokenType::OpenParen);
    CHECK(lexer.tokens[6].value == "(");
    CHECK(lexer.tokens[7].type == TokenType::Identifikator);
    CHECK(lexer.tokens[7].value == "a");
    CHECK(lexer.tokens[8].type == TokenType::DoubleEqual);
    CHECK(lexer.tokens[8].value == "==");
    CHECK(lexer.tokens[9].type == TokenType::Broj);
    CHECK(lexer.tokens[9].value == "5");
    CHECK(lexer.tokens[10].type == TokenType::ClosedParen);
    CHECK(lexer.tokens[10].value == ")");
    CHECK(lexer.tokens[11].type == TokenType::OpenBrace);
    CHECK(lexer.tokens[11].value == "{");
    CHECK(lexer.tokens[12].type == TokenType::Identifikator);
    CHECK(lexer.tokens[12].value == "a");
    CHECK(lexer.tokens[13].type == TokenType::Equal);
    CHECK(lexer.tokens[13].value == "=");
    CHECK(lexer.tokens[14].type == TokenType::Broj);
    CHECK(lexer.tokens[14].value == "10");
    CHECK(lexer.tokens[15].type == TokenType::Semicolon);
    CHECK(lexer.tokens[15].value == ";");
    CHECK(lexer.tokens[16].type == TokenType::ClosedBrace);
    CHECK(lexer.tokens[16].value == "}");
    CHECK(lexer.tokens[17].type == TokenType::Eof);
}