//
// Created by kemal on 11/13/2023.
//

#ifndef MATURSKI_UNDECLAREDVARIABLE_H
#define MATURSKI_UNDECLAREDVARIABLE_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"

class UndeclaredVariable : public std::exception {
    std::string message;
public:
    UndeclaredVariable(std::shared_ptr<Token> token, std::string msg) : message(msg), token(token){}
    std::shared_ptr<Token> token;
    const char* what() {
        return message.c_str();
    }
    std::string getMessage(){
        return message;
    }
};

#endif //MATURSKI_UNDECLAREDVARIABLE_H
