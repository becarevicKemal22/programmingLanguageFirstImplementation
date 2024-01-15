//
// Created by kemal on 05/11/2023.
//

#include <catch2/catch_test_macros.hpp>

#include <Lexer.h>
#include <MockErrorPrinter.h>

#include <iostream>

void checkTypeAndContent(const Lexer &lexer, int index, TokenType type, std::string content) {
    CHECK(lexer.tokens[index].type == type);
    CHECK(lexer.tokens[index].value == content);
}

TEST_CASE("Returns correct token", "[Lexer]") {
    std::string source = "(){}[]+-*/;:.,= ==!!= < <= > >=%";
    MockErrorPrinter printer;
    Lexer lexer(source);
    lexer.tokenize(printer);
    CHECK(lexer.tokens.size() == 24);

    checkTypeAndContent(lexer, 0, TokenType::OpenParen, "(");
    checkTypeAndContent(lexer, 1, TokenType::ClosedParen, ")");
    checkTypeAndContent(lexer, 2, TokenType::OpenBrace, "{");
    checkTypeAndContent(lexer, 3, TokenType::ClosedBrace, "}");
    checkTypeAndContent(lexer, 4, TokenType::OpenBracket, "[");
    checkTypeAndContent(lexer, 5, TokenType::ClosedBracket, "]");
    checkTypeAndContent(lexer, 6, TokenType::Plus, "+");
    checkTypeAndContent(lexer, 7, TokenType::Minus, "-");
    checkTypeAndContent(lexer, 8, TokenType::Star, "*");
    checkTypeAndContent(lexer, 9, TokenType::Slash, "/");
    checkTypeAndContent(lexer, 10, TokenType::Semicolon, ";");
    checkTypeAndContent(lexer, 11, TokenType::Colon, ":");
    checkTypeAndContent(lexer, 12, TokenType::Dot, ".");
    checkTypeAndContent(lexer, 13, TokenType::Comma, ",");
    checkTypeAndContent(lexer, 14, TokenType::Equal, "=");
    checkTypeAndContent(lexer, 15, TokenType::DoubleEqual, "==");
    checkTypeAndContent(lexer, 16, TokenType::Bang, "!");
    checkTypeAndContent(lexer, 17, TokenType::BangEqual, "!=");
    checkTypeAndContent(lexer, 18, TokenType::Less, "<");
    checkTypeAndContent(lexer, 19, TokenType::LessEqual, "<=");
    checkTypeAndContent(lexer, 20, TokenType::Greater, ">");
    checkTypeAndContent(lexer, 21, TokenType::GreaterEqual, ">=");
    checkTypeAndContent(lexer, 22, TokenType::Percent, "%");
    checkTypeAndContent(lexer, 23, TokenType::Eof, "");
}

TEST_CASE("Ignores commments", "[Lexer]") {
    std::string source = "{} // Comment \n [";
    MockErrorPrinter printer;
    Lexer lexer(source);
    lexer.tokenize(printer);

    REQUIRE(lexer.tokens.size() == 4);
    REQUIRE(lexer.tokens[2].type == TokenType::OpenBracket);
}

TEST_CASE("Numbers lines and offsets correctly", "[Lexer]") {
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
    CHECK(lexer.tokens[2].charOffset == 4);

    CHECK(lexer.tokens[3].line == 3);
    CHECK(lexer.tokens[3].charOffset == 4);
}

TEST_CASE("Throws and outputs error on unrecognized token", "[Lexer]") {
    std::string source = "`";
    MockErrorPrinter printer;
    Lexer lexer(source);

    REQUIRE_THROWS(lexer.tokenize(printer));
    REQUIRE(printer.numberOfTimesCalled == 1);
}

TEST_CASE("Correctly interprets numbers", "[Lexer]") {
    std::string source = "3.25 5";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 3);
    checkTypeAndContent(lexer, 0, TokenType::Broj, "3.25");
    checkTypeAndContent(lexer, 1, TokenType::Broj, "5");
}

TEST_CASE("Correctly tokenizes number and dot edge case", "[Lexer]") {
    std::string source = "12.3 45.";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 4);
    checkTypeAndContent(lexer, 0, TokenType::Broj, "12.3");
    checkTypeAndContent(lexer, 1, TokenType::Broj, "45");
    checkTypeAndContent(lexer, 2, TokenType::Dot, ".");
}

TEST_CASE("Correctly tokenizes identifiers", "[Lexer]") {
    std::string source = "varijabla var2";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 3);
    checkTypeAndContent(lexer, 0, TokenType::Identifikator, "varijabla");
    checkTypeAndContent(lexer, 1, TokenType::Identifikator, "var2");
}

TEST_CASE("Correctly tokenizes keywords", "[Lexer]") {
    std::string source = "var konst ako inace dok prazno tacno netacno print onda";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 11);
    checkTypeAndContent(lexer, 0, TokenType::Var, "var");
    checkTypeAndContent(lexer, 1, TokenType::Konst, "konst");
    checkTypeAndContent(lexer, 2, TokenType::Ako, "ako");
    checkTypeAndContent(lexer, 3, TokenType::Inace, "inace");
    checkTypeAndContent(lexer, 4, TokenType::Dok, "dok");
    checkTypeAndContent(lexer, 5, TokenType::Prazno, "prazno");
    checkTypeAndContent(lexer, 6, TokenType::Tacno, "tacno");
    checkTypeAndContent(lexer, 7, TokenType::Netacno, "netacno");
    checkTypeAndContent(lexer, 8, TokenType::Print, "print");
    checkTypeAndContent(lexer, 9, TokenType::Onda, "onda");
//    checkTypeAndContent(lexer, 10, TokenType::Print, "ili");
//    checkTypeAndContent(lexer, 11, TokenType::Print, "u");
//    checkTypeAndContent(lexer, 12, TokenType::Print, "protivnom");
}

TEST_CASE("Tokenizes strings", "[Lexer]"){
    MockErrorPrinter printer;
    SECTION("Tokenizes empty string"){
        std::string source = " \"\" ";
        Lexer lexer(source);
        try{
            lexer.tokenize(printer);
        }catch(std::exception& err){
            std::cout << err.what() << "\n";
        }
        REQUIRE(lexer.tokens.size() == 2);
        checkTypeAndContent(lexer, 0, TokenType::String, "\"\"");
        CHECK(lexer.tokens[0].charOffset == 1);
    }
    SECTION("Tokenizes normal string"){
        std::string source = " \"This is a string!\" ";
        Lexer lexer(source);
        try{
            lexer.tokenize(printer);
        }catch(std::exception& err){
            std::cout << err.what() << "\n";
        }
        REQUIRE(lexer.tokens.size() == 2);
        checkTypeAndContent(lexer, 0, TokenType::String, "\"This is a string!\"");
        CHECK(lexer.tokens[0].charOffset == 1);
    }
    SECTION("Tokenizes string with offset"){
        std::string source = "\n\t \"Offset\"";
        Lexer lexer(source);
        try{
            lexer.tokenize(printer);
        }catch(std::exception& err){
            std::cout << err.what() << "\n";
        }
        REQUIRE(lexer.tokens.size() == 2);
        checkTypeAndContent(lexer, 0, TokenType::String, "\"Offset\"");
        CHECK(lexer.tokens[0].charOffset == 5);
        CHECK(lexer.tokens[0].line == 2);
    }
    SECTION("Gives error on unterminated string"){
        std::string source = "\"Unterminated string ";
        Lexer lexer(source);
        REQUIRE_THROWS(lexer.tokenize(printer));
        REQUIRE(printer.numberOfTimesCalled == 1);
    }
}

TEST_CASE("Tokenizes variable declaration", "[Lexer]") {
    std::string source = "var var2 = 5.36;";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 6);
    checkTypeAndContent(lexer, 0, TokenType::Var, "var");
    checkTypeAndContent(lexer, 1, TokenType::Identifikator, "var2");
    checkTypeAndContent(lexer, 2, TokenType::Equal, "=");
    checkTypeAndContent(lexer, 3, TokenType::Broj, "5.36");
    checkTypeAndContent(lexer, 4, TokenType::Semicolon, ";");
}

TEST_CASE("Program sample", "[Lexer]") {
    std::string source = "var a = 5;\n"
                         "ako(a == 5){\n"
                         "    a = 10;\n"
                         "}";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 18);
    checkTypeAndContent(lexer, 0, TokenType::Var, "var");
    checkTypeAndContent(lexer, 1, TokenType::Identifikator, "a");
    checkTypeAndContent(lexer, 2, TokenType::Equal, "=");
    checkTypeAndContent(lexer, 3, TokenType::Broj, "5");
    checkTypeAndContent(lexer, 4, TokenType::Semicolon, ";");
    checkTypeAndContent(lexer, 5, TokenType::Ako, "ako");
    checkTypeAndContent(lexer, 6, TokenType::OpenParen, "(");
    checkTypeAndContent(lexer, 7, TokenType::Identifikator, "a");
    checkTypeAndContent(lexer, 8, TokenType::DoubleEqual, "==");
    checkTypeAndContent(lexer, 9, TokenType::Broj, "5");
    checkTypeAndContent(lexer, 10, TokenType::ClosedParen, ")");
    checkTypeAndContent(lexer, 11, TokenType::OpenBrace, "{");
    checkTypeAndContent(lexer, 12, TokenType::Identifikator, "a");
    checkTypeAndContent(lexer, 13, TokenType::Equal, "=");
    checkTypeAndContent(lexer, 14, TokenType::Broj, "10");
    checkTypeAndContent(lexer, 15, TokenType::Semicolon, ";");
    checkTypeAndContent(lexer, 16, TokenType::ClosedBrace, "}");
    CHECK(lexer.tokens[17].type == TokenType::Eof);

}

TEST_CASE("Correctly handles files starting with newlines", "[Lexer]") {
    std::string source = "\n"
                         "\n"
                         "test 123;";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 4);
    checkTypeAndContent(lexer, 0, TokenType::Identifikator, "test");
    CHECK(lexer.tokens[0].charOffset == 0);
    checkTypeAndContent(lexer, 1, TokenType::Broj, "123");
    CHECK(lexer.tokens[1].charOffset == 5);
}

TEST_CASE("Handles tab characters with offsets", "[Lexer]") {
    std::string source = "\ttest";
    MockErrorPrinter printer;
    Lexer lexer(source);
    try {
        lexer.tokenize(printer);
    } catch (std::runtime_error &err) {
        std::cout << err.what() << "\n";
    }

    REQUIRE(lexer.tokens.size() == 2);
    checkTypeAndContent(lexer, 0, TokenType::Identifikator, "test");
    CHECK(lexer.tokens[0].charOffset == 4);
}