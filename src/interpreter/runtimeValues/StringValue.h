//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_STRINGVALUE_H
#define MATURSKI_STRINGVALUE_H

#include <string>
#include "RuntimeValue.h"

class StringValue : public RuntimeValue {
public:
    explicit StringValue(std::string value) : RuntimeValue(), value(value){
        type = ValueType::String;
    }
    std::string stringify() override {
        return value;
    }
    std::string value;
};

#endif //MATURSKI_STRINGVALUE_H
