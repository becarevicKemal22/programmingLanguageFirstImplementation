//
// Created by kemal on 04/11/2023.
//

#ifndef MATURSKI_LEXER_H
#define MATURSKI_LEXER_H

#include <vector>
#include <Token.h>
#include <ErrorPrinter.h>

class Lexer {
public:
    explicit Lexer(std::string source) : source(source) {};
    std::string source;
    std::vector<Token> tokens{};
    virtual void tokenize(const ErrorPrinter& printer);
    void print();
private:
    char at(){
        return source[currentChar];
    }
    void pushToken(TokenType type, std::string value){
        tokens.emplace_back(type, value, line, charOnLine);
    }
    void pushToken(TokenType type, char c){
        tokens.emplace_back(type, std::string(1, c), line, charOnLine);
    }
    void handleComment();
    void advance();
    void newLine();
    unsigned int currentChar = 0;
    unsigned int line = 1;
    std::string lineStr = "";
    unsigned int charOnLine = 1;
};

#endif //MATURSKI_LEXER_H
