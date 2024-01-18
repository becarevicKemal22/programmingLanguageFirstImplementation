//
// Created by kemal on 1/16/2024.
//

#include "ClockFunction.h"

RuntimeValuePtr clockNative(Interpreter* interpreter, std::vector<RuntimeValuePtr> args){
    return std::make_shared<NumericValue>(static_cast<double>(clock()) / CLOCKS_PER_SEC);
}

int clockArity(){
    return 0;
}

std::shared_ptr<Callable> makeClockCallable(){
    return std::make_shared<Callable>(
            ValueType::Function,
            clockNative,
            clockArity
    );
}