//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_PARSER_H
#define MATURSKI_PARSER_H

#include <vector>
#include "../error/ErrorPrinter.h"
#include "./ast/Program.h"
#include "../lexer/Token.h"
#include "./ast/Expression.h"


class Parser {
public:
    explicit Parser(ErrorPrinter& printer) : printer(printer) {}
    ast::Program parse(const std::string& source);
private:
    ErrorPrinter& printer;
    std::vector<Token> tokens = {};
    unsigned int current = 0;
    Token at(){
        return tokens[current];
    }
    bool atType(TokenType type){
        return tokens[current].type == type;
    }
    std::shared_ptr<Token> advance(){
        std::shared_ptr<Token> tk = std::make_shared<Token>(at());
        current++;
        return tk;
    }

    std::shared_ptr<ast::Statement> statement();
    std::shared_ptr<ast::Expression> expression();
    std::shared_ptr<ast::Expression> primaryExpression();
};


#endif //MATURSKI_PARSER_H
