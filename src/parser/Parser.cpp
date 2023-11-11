//
// Created by kemal on 06/11/2023.
//

#include "Parser.h"
#include "Lexer.h"
#include "BooleanLiteral.h"
#include "NullLiteral.h"
#include "GroupingExpression.h"
#include "UnaryExpression.h"

ast::Program Parser::parse(const std::string &source) {
    ast::Program program;
    Lexer lexer(source);
    tokens = lexer.tokenize(printer);
    while(!atType(TokenType::Eof)){
        try{
            program.body.push_back(statement());
        }catch(std::runtime_error& e) {
            hadError = true;
            synchronize();
        }
    }
    return program;
}

std::shared_ptr<ast::Statement> Parser::statement(){
    return expression();
}

ExprPtr Parser::expression(){
    return equalityExpression();
}

ExprPtr Parser::equalityExpression() {
    ExprPtr expr = comparisonExpression();

    while(match({TokenType::DoubleEqual, TokenType::BangEqual})){
        std::shared_ptr<Token> op = advance();
        ExprPtr right = comparisonExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::comparisonExpression() {
    ExprPtr expr = additiveExpression();

    while(match({TokenType::Greater, TokenType::GreaterEqual, TokenType::Less, TokenType::LessEqual})){
        std::shared_ptr<Token> op = advance();
        ExprPtr right = additiveExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, op, right);
    }
    return expr;
}

ExprPtr Parser::additiveExpression() {
    ExprPtr expr = multiplicativeExpression();
    while(match({TokenType::Plus, TokenType::Minus})){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = multiplicativeExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, _operator, right);
    }
    return expr;
}

ExprPtr Parser::multiplicativeExpression() {
    ExprPtr expr = unaryExpression();
    while(match({TokenType::Star, TokenType::Slash, TokenType::Percent})){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = unaryExpression();
        expr = std::make_shared<ast::BinaryExpression>(expr, _operator, right);
    }
    return expr;
}

ExprPtr Parser::unaryExpression(){
    if(at().value == "!" || at().value == "-"){
        std::shared_ptr<Token> op = advance();
        ExprPtr right = unaryExpression();
        return std::make_shared<ast::UnaryExpression>(op, right);
    }
    return primaryExpression();
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
        printer.printLexerError(at().line, at().charOffset, "Expected expression.");
        throw std::runtime_error("Parser error.");
    }
}

void Parser::synchronize() {
    advance();
    while(!atType(TokenType::Eof)){
        if(at().type == TokenType::Semicolon){
            return;
        }
        switch (at().type) {
            // Fali klasa funkcija for print i return
            case TokenType::Var:
            case TokenType::Konst:
            case TokenType::Ako:
            case TokenType::Dok:
                return;
            default:
                advance();
        }
    }
}