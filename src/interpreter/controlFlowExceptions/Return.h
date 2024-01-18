//
// Created by kemal on 1/17/2024.
//

#ifndef MATURSKI_RETURN_H
#define MATURSKI_RETURN_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"
#include "RuntimeValue.h"

class Return : public std::exception {
    std::shared_ptr<RuntimeValue> value;
public:
    Return(std::shared_ptr<RuntimeValue> value){
        this->value = value;
    }
    const char* what() {
        return "Return";
    }
    std::shared_ptr<RuntimeValue> getValue(){
        return value;
    }
};

#endif //MATURSKI_RETURN_H
