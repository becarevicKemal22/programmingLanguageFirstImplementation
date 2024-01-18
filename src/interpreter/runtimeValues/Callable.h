//
// Created by kemal on 1/16/2024.
//

#ifndef MATURSKI_CALLABLE_H
#define MATURSKI_CALLABLE_H

#include <vector>
#include <exception>
#include "RuntimeValue.h"

class Interpreter;

class Callable : public RuntimeValue {
public:

    typedef RuntimeValuePtr (*NativeFunction)(Interpreter* interpreter, std::vector<RuntimeValuePtr> arguments);
    typedef int (*ArityFunction)();
    explicit Callable(ValueType type) : RuntimeValue() {
        this->type = type;
    }
    Callable(ValueType type, NativeFunction nativeFunction, ArityFunction arityFunction) : RuntimeValue() {
        this->type = type;
        this->nativeFunction = nativeFunction;
        this->arityFunction = arityFunction;
    }
    virtual ~Callable() = default;

    virtual RuntimeValuePtr call(Interpreter* interpreter, std::vector<RuntimeValuePtr> arguments) {
        if(nativeFunction != nullptr){
            return nativeFunction(interpreter, arguments);
        }
        throw std::runtime_error("Callable call has not been implemented or assigned.");
    };
    virtual int arity() {
        if(arityFunction != nullptr){
            return arityFunction();
        }
        throw std::runtime_error("Callable arity has not been implemented or assigned.");
    }
    std::string stringify() override {
        return "Callable";
    }

    void setNativeFunction(NativeFunction nativeFunction){
        this->nativeFunction = nativeFunction;
    }
    void setArityFunction(ArityFunction arityFunction){
        this->arityFunction = arityFunction;
    }

private:
    NativeFunction nativeFunction = nullptr;
    ArityFunction arityFunction = nullptr;
};

#endif //MATURSKI_CALLABLE_H
