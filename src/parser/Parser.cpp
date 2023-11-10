//
// Created by kemal on 06/11/2023.
//

#include "Parser.h"
#include "Lexer.h"
#include "BooleanLiteral.h"
#include "NullLiteral.h"
#include "GroupingExpression.h"

ast::Program Parser::parse(const std::string &source) {
    ast::Program program;
    Lexer lexer(source);
    tokens = lexer.tokenize(printer);
    while(!atType(TokenType::Eof)){
        program.body.push_back(statement());
    }
    return program;
}

std::shared_ptr<ast::Statement> Parser::statement(){
    return expression();
}

ExprPtr Parser::expression(){
    return additiveExpression();
}

ExprPtr Parser::additiveExpression() {
    ExprPtr expr = multiplicativeExpression();
    while(at().value == "+" || at().value == "-"){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = multiplicativeExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, _operator, right);
    }
    return expr;
}

ExprPtr Parser::multiplicativeExpression() {
    ExprPtr expr = primaryExpression();
    while(at().value == "*" || at().value == "/" || at().value == "%"){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = primaryExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, _operator, right);
    }
    return expr;
}

ExprPtr Parser::primaryExpression(){
    if(atType(TokenType::Broj)){
        return std::make_shared<ast::NumericLiteral>(advance());
    }else if(atType(TokenType::Identifikator)){
        return std::make_shared<ast::Identifier>(advance());
    }else if(atType(TokenType::Prazno)){
        return std::make_shared<ast::NullLiteral>(advance());
    }else if(atType(TokenType::Tacno) || atType(TokenType::Netacno)){
        return std::make_shared<ast::BooleanLiteral>(advance());
    }else if(atType(TokenType::OpenParen)){
        advance();
        std::shared_ptr<ast::GroupingExpression> expr = std::make_shared<ast::GroupingExpression>(expression());
        if(!atType(TokenType::ClosedParen)){
            printer.expectedXBeforeY(previous(), ")", at(), at().value);
            throw std::runtime_error("Parser error.");
        }else{
            advance();
        }
        return expr;
    }

    else{
        printer.printLexerError(at().line, at().charOffset, "Unexpected token found.");
        throw std::runtime_error("Parsing error.");
    }
}