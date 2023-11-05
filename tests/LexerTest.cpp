//
// Created by kemal on 05/11/2023.
//

#include <catch2/catch_test_macros.hpp>

#include <Lexer.h>
#include <ErrorPrinter.h>

TEST_CASE("Returns correct token", "[Lexer]"){
    std::string source = "(){}[]+-*/;:.,= ==";
    ErrorPrinter printer(source);
    Lexer lexer(source);
    lexer.tokenize(printer);
    REQUIRE(lexer.tokens.size() == 17);
    REQUIRE(lexer.tokens[0].type == TokenType::OpenParen);
    REQUIRE(lexer.tokens[1].type == TokenType::ClosedParen);
    REQUIRE(lexer.tokens[2].type == TokenType::OpenBrace);
    REQUIRE(lexer.tokens[3].type == TokenType::ClosedBrace);
    REQUIRE(lexer.tokens[4].type == TokenType::OpenBracket);
    REQUIRE(lexer.tokens[5].type == TokenType::ClosedBracket);
    REQUIRE(lexer.tokens[6].type == TokenType::BinarniOperator);
    REQUIRE(lexer.tokens[7].type == TokenType::BinarniOperator);
    REQUIRE(lexer.tokens[8].type == TokenType::BinarniOperator);
    REQUIRE(lexer.tokens[9].type == TokenType::BinarniOperator);
    REQUIRE(lexer.tokens[10].type == TokenType::Semicolon);
    REQUIRE(lexer.tokens[11].type == TokenType::Colon);
    REQUIRE(lexer.tokens[12].type == TokenType::Dot);
    REQUIRE(lexer.tokens[13].type == TokenType::Comma);
    REQUIRE(lexer.tokens[14].type == TokenType::Equal);
    REQUIRE(lexer.tokens[15].type == TokenType::DoubleEqual);
    REQUIRE(lexer.tokens[16].type == TokenType::Eof);
}

TEST_CASE("Ignores commments", "[comments]"){
    std::string source = "{} // Comment \n [";
    ErrorPrinter printer(source);
    Lexer lexer(source);
    lexer.tokenize(printer);
    REQUIRE(lexer.tokens.size() == 4);
    REQUIRE(lexer.tokens[2].type == TokenType::OpenBracket);
}
//
//TEST(LexerTest, PrintsErrorOnUnexpectedToken){
//    std::string source = "a";
//    MockErrorPrinter printer(source);
//    Lexer lexer(source);
//    EXPECT_CALL(printer, printError).Times(1).WillOnce(Return());
//    EXPECT_EXIT(lexer.tokenize(printer), testing::ExitedWithCode(1), "");
//}