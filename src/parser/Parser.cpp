//
// Created by kemal on 06/11/2023.
//

#include "Parser.h"
#include "Lexer.h"
#include "BooleanLiteral.h"
#include "NullLiteral.h"
#include "GroupingExpression.h"
#include "UnaryExpression.h"
#include "StringLiteral.h"
#include "PrintStatement.h"
#include "ExprStatement.h"
#include "Expression.h"
#include "VarDeclaration.h"
#include "exceptions/UninitializedConst.h"

ast::Program Parser::parse(const std::string &source) {
    ast::Program program;
    Lexer lexer(source);
    tokens = lexer.tokenize(printer);
    while(!atType(TokenType::Eof)){
        try{
            program.body.push_back(declaration());
        }catch(UninitializedConst& e){
            printer.highlightTokenError(*e.token, e.getMessage());
            hadError = true;
            synchronize();
        }
        catch(std::runtime_error& e) {
            hadError = true;
            synchronize();
        }
    }
    return program;
}

StmtPtr Parser::declaration() {
    if(match({TokenType::Var, TokenType::Konst})){
        return varDeclarationStatement();
    }
    return statement();
}

StmtPtr Parser::varDeclarationStatement() {
    std::shared_ptr<Token> keyword = advance();
    bool isConst = keyword->type == TokenType::Konst;
    std::shared_ptr<Token> identifier;
    if(consume(TokenType::Identifikator)){
        identifier = std::make_shared<Token>(previous());
    }else{
        printer.expectedXBeforeY(previous(), "identifier", at(), at().value);
        throw std::runtime_error("Parser error.");
    }
    ExprPtr initializer = nullptr;
    if(!atType(TokenType::Equal) && isConst){
        throw UninitializedConst(previous(), "Variable declared as 'konst' must be initialized");
    }
    if(atType(TokenType::Equal)){
        advance();
        initializer = expression();
    }
    if(!consume(TokenType::Semicolon)){
        printer.expectedXBeforeY(previous(), ";", at(), at().value);
        throw std::runtime_error("Parser error.");
    }
    return std::make_shared<ast::VarDeclaration>(identifier, initializer, isConst);
}

std::shared_ptr<ast::Statement> Parser::statement(){
    if(atType(TokenType::Print)){
        return printStatement();
    }
    return expressionStatement();
}

StmtPtr Parser::printStatement(){
    advance();
    ExprPtr valueToPrint = expression();
    if(!consume(TokenType::Semicolon)){
        printer.expectedXBeforeY(previous(), ";", at(), at().value);
        throw std::runtime_error("Parser error.");
    }
    return std::make_shared<ast::PrintStatement>(valueToPrint);
}

StmtPtr Parser::expressionStatement(){
    ExprPtr expr = expression();
    if(!consume(TokenType::Semicolon)){
        printer.expectedXBeforeY(previous(), ";", at(), at().value);
        throw std::runtime_error("Parser error.");
    }
    return std::make_shared<ast::ExprStatement>(expr);
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
    }else if(atType(TokenType::String)){
        return std::make_shared<ast::StringLiteral>(advance());
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
        printer.expectedXBeforeY(previous(), "expression", at(), at().value);
        throw std::runtime_error("Parser error.");
    }
}

void Parser::synchronize() {
    if(atType(TokenType::Eof)){
        return;
    }
    advance();
    while(!atType(TokenType::Eof)){
        if(previous().type == TokenType::Semicolon){
            return;
        }
        switch (at().type) {
            // Fali klasa funkcija for i return
            case TokenType::Var:
            case TokenType::Konst:
            case TokenType::Ako:
            case TokenType::Dok:
            case TokenType::Print:
                return;
            default:
                advance();
        }
    }
}