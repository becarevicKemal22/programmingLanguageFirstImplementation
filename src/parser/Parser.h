//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_PARSER_H
#define MATURSKI_PARSER_H

#include <vector>
#include "ErrorPrinter.h"
#include "Program.h"
#include "Token.h"
#include "Expression.h"

typedef std::shared_ptr<ast::Expression> ExprPtr;
typedef std::shared_ptr<ast::Statement> StmtPtr;

class Parser {
public:
    explicit Parser(ErrorPrinter& printer) : printer(printer) {}
    ast::Program parse(const std::string& source);
    bool hadError = false;
private:
    ErrorPrinter& printer;
    std::vector<Token> tokens = {};
    unsigned int current = 0;
    Token at(){
        return tokens[current];
    }
    Token previous(){
        return tokens[current - 1];
    }
    bool atType(TokenType type){
        return tokens[current].type == type;
    }
    bool consume(TokenType type){
        if(atType(type)){
            advance();
            return true;
        }else{
            return false;
        }
    }
    std::shared_ptr<Token> advance(){
        std::shared_ptr<Token> tk = std::make_shared<Token>(at());
        current++;
        return tk;
    }
    bool match(std::vector<TokenType> types){
        for(auto type : types){
            if(atType(type)){
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<Token> getMostRelevantToken(ast::Expression* expr);

    StmtPtr declaration();
    StmtPtr varDeclarationStatement();
    StmtPtr statement();
    StmtPtr printStatement();
    StmtPtr ifStatement();
    StmtPtr expressionStatement();
    ExprPtr expression();
    ExprPtr assignmentExpression();
    ExprPtr equalityExpression();
    ExprPtr comparisonExpression();
    ExprPtr additiveExpression();
    ExprPtr multiplicativeExpression();
    ExprPtr unaryExpression();
    ExprPtr primaryExpression();
    void synchronize();
    std::vector<std::shared_ptr<ast::Statement>> block();
};


#endif //MATURSKI_PARSER_H
