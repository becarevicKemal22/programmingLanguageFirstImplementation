//
// Created by kemal on 04/11/2023.
//

#ifndef MATURSKI_LEXER_H
#define MATURSKI_LEXER_H

#include <vector>
#include "Token.h"
#include "ErrorPrinter.h"

class Lexer {
public:
    explicit Lexer(std::string source) : source(source) {};
    std::string source;
    std::vector<Token> tokens{};
    std::vector<Token> tokenize(ErrorPrinter& printer);
    void print() const;
private:
    char at(){
        return source[currentChar];
    }
    char peek(){
        return source[currentChar + 1];
    }
    void pushToken(TokenType type, std::string value){
        tokens.emplace_back(type, value, line, (charIndexOnLine + 1) - value.length());
    }
    void pushToken(TokenType type, char c){
        tokens.emplace_back(type, std::string(1, c), line, charIndexOnLine);
    }
    void handleComment();
    void advance();
    void newLine();
    unsigned int currentChar = 0;
    unsigned int line = 1;
    std::string lineStr = "";
    unsigned int charIndexOnLine = 0;
};

#endif //MATURSKI_LEXER_H
