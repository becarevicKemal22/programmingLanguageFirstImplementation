//
// Created by kemal on 11/14/2023.
//

#ifndef MATURSKI_UNINITIALIZEDCONST_H
#define MATURSKI_UNINITIALIZEDCONST_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"

class UninitializedConst : public std::exception {
    std::string message;
public:
    UninitializedConst(std::shared_ptr<Token> token, std::string msg) : message(msg), token(token){}
    UninitializedConst(Token token, std::string msg) : message(msg), token(std::make_shared<Token>(token)){}
    std::shared_ptr<Token> token;
    const char* what() {
        return message.c_str();
    }
    std::string getMessage(){
        return message;
    }
};

#endif //MATURSKI_UNINITIALIZEDCONST_H
