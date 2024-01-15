//
// Created by kemal on 11/14/2023.
//

#ifndef MATURSKI_VARIABLEREDECLARATION_H
#define MATURSKI_VARIABLEREDECLARATION_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"

class VariableRedeclaration : public std::exception {
    std::string message;
public:
    VariableRedeclaration(std::shared_ptr<Token> token, std::string msg) : message(msg), token(token){}
    std::shared_ptr<Token> token;
    const char* what() {
        return message.c_str();
    }
    std::string getMessage(){
        return message;
    }
};

#endif //MATURSKI_VARIABLEREDECLARATION_H
