//
// Created by kemal on 11/11/2023.
//

#ifndef MATURSKI_NUMERICVALUE_H
#define MATURSKI_NUMERICVALUE_H

#include "RuntimeValue.h"

class NumericValue : public RuntimeValue {
public:
    explicit NumericValue(double value) : RuntimeValue(), value(value){
        type = ValueType::Number;
    }
    std::string stringify() override {
        std::string str = std::to_string(value);
        str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
        str.erase ( str.find_last_not_of('.') + 1, std::string::npos );
        return str;
    }
    double value;
};

#endif //MATURSKI_NUMERICVALUE_H
