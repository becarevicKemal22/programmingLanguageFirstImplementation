//
// Created by kemal on 06/11/2023.
//

#include <vector>
#include "Parser.h"
#include "../error/ErrorPrinter.h"
#include "../lexer/Token.h"
#include "../lexer/Lexer.h"
#include "./ast/Expression.h"
#include "./ast/NumericLiteral.h"

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

std::shared_ptr<ast::Expression> Parser::expression(){
    return primaryExpression();
}

std::shared_ptr<ast::Expression> Parser::primaryExpression(){
    if(atType(TokenType::Broj)){
        return std::make_shared<ast::NumericLiteral>(advance());
    }else{
        printer.printError(at().line, at().charOffset, "Unexpected token found.");
        throw std::runtime_error("Parsing error.");
    }
}