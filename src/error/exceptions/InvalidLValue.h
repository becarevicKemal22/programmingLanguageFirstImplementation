//
// Created by kemal on 11/15/2023.
//

#ifndef MATURSKI_INVALIDLVALUE_H
#define MATURSKI_INVALIDLVALUE_H

#include <exception>
#include <string>
#include <memory>
#include "Token.h"

class InvalidLValue : public std::exception {
    std::string message;
public:
    InvalidLValue(std::shared_ptr<Token> token, std::string msg) : message(msg), token(token){}
    std::shared_ptr<Token> token;
    const char* what() {
        return message.c_str();
    }
    std::string getMessage(){
        return message;
    }
};

#endif //MATURSKI_INVALIDLVALUE_H
