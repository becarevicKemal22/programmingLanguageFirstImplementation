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
#include "LogicalExpression.h"
#include "AssignmentExpression.h"
#include "BlockStatement.h"
#include "IfStatement.h"
#include "WhileStatement.h"
#include "exceptions/ExpectedXBeforeY.h"
#include "exceptions/UninitializedConst.h"
#include "exceptions/InvalidLValue.h"

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
        catch(InvalidLValue& e){
            printer.highlightTokenError(*e.token, e.getMessage());
            hadError = true;
            // No sync is needed because an invalid lhs doesn't leave the parser in an invalid state, as the rest of the statement has been parsed correctly, so the parser can continue normally.
        }
        catch(ExpectedXBeforeY& e){
            printer.expectedXBeforeY(e.previousToken, e.expectedWhat, e.afterToken, e.beforeWhat);
            hadError = true;
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
    if(atType(TokenType::Ako)){
        return ifStatement();
    }
    if(atType(TokenType::Inace)){
        printer.highlightTokenError(at(), "Expected 'ako' before 'inace'");
        throw std::runtime_error("Parser error.");
    }
    if(atType(TokenType::Dok)){
        return whileStatement();
    }
    if(atType(TokenType::Za)){
        return forStatement();
    }
    if(atType(TokenType::OpenBrace)){
        return std::make_shared<ast::BlockStatement>(block());
    }
    return expressionStatement();
}

std::shared_ptr<ast::Statement> Parser::ifStatement() {
    advance();
    ExprPtr condition = expression();
    if(!consume(TokenType::Onda)){
        throw ExpectedXBeforeY(previous(), "onda", at(), at().value);
    }

    StmtPtr thenBranch = statement();
    StmtPtr elseBranch = nullptr;
    if(atType(TokenType::Inace)){
        advance();
        elseBranch = statement();
    }

    return std::make_shared<ast::IfStatement>(condition, thenBranch, elseBranch);
}

std::shared_ptr<ast::Statement> Parser::whileStatement() {
    advance();
    if(!consume(TokenType::OpenParen)){
        throw ExpectedXBeforeY(previous(), "(", at(), at().value);
    }
    ExprPtr condition = expression();
    if(!consume(TokenType::ClosedParen)){
        throw ExpectedXBeforeY(previous(), ")", at(), at().value);
    }
    StmtPtr body = statement();
    return std::make_shared<ast::WhileStatement>(condition, body);
}

StmtPtr Parser::forStatement() {
    advance();
    if(!consume(TokenType::OpenParen)){
        throw ExpectedXBeforeY(previous(), "(", at(), at().value);
    }
    StmtPtr initializer = nullptr;
    if(atType(TokenType::Semicolon)){
        advance();
    } else if(atType(TokenType::Var)){
        initializer = varDeclarationStatement();
    } else {
        initializer = expressionStatement();
    }

    ExprPtr condition = nullptr;
    if(!atType(TokenType::Semicolon)){
        condition = expression();
    }
    if(!consume(TokenType::Semicolon)){
        throw ExpectedXBeforeY(previous(), ";", at(), at().value);
    }

    ExprPtr increment = nullptr;
    if(!atType(TokenType::ClosedParen)){
        increment = expression();
    }
    if(!consume(TokenType::ClosedParen)){
        throw ExpectedXBeforeY(previous(), ")", at(), at().value);
    }

    StmtPtr body = statement();
    /*
     * print a;
     *
     *
     */
    if(increment != nullptr){
        std::vector<std::shared_ptr<ast::Statement>> newBody = {body, increment};
        body = std::make_shared<ast::BlockStatement>(newBody);
    }

    if(condition == nullptr) {
        std::shared_ptr<Token> trueToken = std::make_shared<Token>(TokenType::Tacno, "tacno", 0, 0);
        condition = std::make_shared<ast::BooleanLiteral>(trueToken);
    }

    body = std::make_shared<ast::WhileStatement>(condition, body);

    if(initializer != nullptr){
        std::vector<std::shared_ptr<ast::Statement>> newBody = {initializer, body};
        body = std::make_shared<ast::BlockStatement>(newBody);
    }

    return body;
}


std::vector<std::shared_ptr<ast::Statement>> Parser::block(){
    advance();
    std::vector<std::shared_ptr<ast::Statement>> statements{};
    while(!atType(TokenType::ClosedBrace) && !atType(TokenType::Eof)){
        statements.push_back(declaration());
    }

    if(!consume(TokenType::ClosedBrace)){
        throw ExpectedXBeforeY(previous(), "}", at(), at().value);
    }
    return statements;
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
    return assignmentExpression();
}

ExprPtr Parser::assignmentExpression() {
    ExprPtr expr = orExpression();

    if(atType(TokenType::Equal)){
        std::shared_ptr<Token> equals = advance();
        ExprPtr value = assignmentExpression();

        std::shared_ptr<ast::Identifier> ident = std::dynamic_pointer_cast<ast::Identifier>(expr);
        if(ident != nullptr){
            std::shared_ptr<Token> identifier = ident->token;
            return std::make_shared<ast::AssignmentExpression>(identifier, value);
        }
        throw InvalidLValue(getMostRelevantToken(expr.get()), "lvalue required as left operand of assignment");
    }
    return expr;
}

ExprPtr Parser::orExpression() {
    ExprPtr expr = andExpression();
    while(atType(TokenType::LogicalOr)){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = andExpression();
        expr = std::make_shared<ast::LogicalExpression>(expr, _operator, right);
    }
    return expr;
}

ExprPtr Parser::andExpression() {
    ExprPtr expr = equalityExpression();
    while(atType(TokenType::LogicalAnd)){
        std::shared_ptr<Token> _operator = advance();
        ExprPtr right = equalityExpression();
        expr = std::make_shared<ast::LogicalExpression>(expr, _operator, right);
    }
    return expr;
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

std::shared_ptr<Token> Parser::getMostRelevantToken(ast::Expression* expr){
    if(auto binaryExpr = dynamic_cast<ast::BinaryExpression*>(expr)){
        return binaryExpr->_operator;
    }
    if(auto unaryExpr = dynamic_cast<ast::UnaryExpression*>(expr)){
        return unaryExpr->_operator;
    }
    if(auto groupingExpr = dynamic_cast<ast::GroupingExpression*>(expr)){
        return getMostRelevantToken(groupingExpr->expr.get());
    }
    if(auto literal = dynamic_cast<ast::NumericLiteral*>(expr)){
        return literal->token;
    }
    if(auto literal = dynamic_cast<ast::BooleanLiteral*>(expr)){
        return literal->token;
    }
    if(auto literal = dynamic_cast<ast::NullLiteral*>(expr)){
        return literal->token;
    }
    if(auto literal = dynamic_cast<ast::StringLiteral*>(expr)){
        return literal->token;
    }
    if(auto literal = dynamic_cast<ast::Identifier*>(expr)){
        return literal->token;
    }
    if(auto literal = dynamic_cast<ast::AssignmentExpression*>(expr)){
        return literal->identifier;
    }
    throw std::logic_error("Unknown expression type");
}
