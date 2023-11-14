//
// Created by kemal on 11/14/2023.
//

#ifndef MATURSKI_CONSTREASSIGNMENT_H
#define MATURSKI_CONSTREASSIGNMENT_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"

class ConstReassignment : public std::exception {
    std::string message;
public:
    ConstReassignment(std::shared_ptr<Token> token, std::string msg) : message(msg), token(token){}
    std::shared_ptr<Token> token;
    const char* what() {
        return message.c_str();
    }
    std::string getMessage(){
        return message;
    }
};

#endif //MATURSKI_CONSTREASSIGNMENT_H
