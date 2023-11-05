//
// Created by kemal on 04/11/2023.
//

#ifndef MATURSKI_TOKEN_H
#define MATURSKI_TOKEN_H

#include <TokenType.h>
#include <string>

class Token {
public:
    Token(TokenType type, std::string value, unsigned int line, unsigned int charOffset) : type(type), value(value), line(line), charOffset(charOffset){}
    TokenType type;
    std::string value;
    unsigned int line;
    unsigned int charOffset;
};


#endif //MATURSKI_TOKEN_H
