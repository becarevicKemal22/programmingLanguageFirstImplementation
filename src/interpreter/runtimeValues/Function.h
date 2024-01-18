//
// Created by kemal on 1/17/2024.
//

#ifndef MATURSKI_FUNCTION_H
#define MATURSKI_FUNCTION_H

#include <vector>
#include <exception>
#include "RuntimeValue.h"
#include "Callable.h"
#include "FunctionDeclaration.h"
#include "NullValue.h"
#include "Return.h"

class Interpreter;

class Function : public Callable {
public:
    Function(std::shared_ptr<ast::FunctionDeclaration> declaration) : Callable(ValueType::Function, nullptr, nullptr) {
        this->declaration = declaration;
    }

    RuntimeValuePtr call(Interpreter *interpreter, std::vector<RuntimeValuePtr> arguments) override {
        Environment environment(interpreter->globals);
        for(int i = 0; i < declaration->params.size(); i++){
            environment.define(declaration->params[i], arguments[i], false);
        }
        try{
            interpreter->executeBlock(declaration->body, std::make_shared<Environment>(environment));
        } catch(Return& returnValue){
            timesCalled_++;  // Required from testing, should come up with better solution
            return returnValue.getValue();
        }
        timesCalled_++;  // Required from testing, should come up with better solution
        return std::make_shared<NullValue>();
    }

    int arity() override {
        return declaration->params.size();
    }

    std::string stringify() override {
        return "funkcija " + declaration->name->value + "";
    }
    // Required from testing, should come up with better solution
    unsigned int timesCalled(){
        return timesCalled_;
    }
private:
    unsigned int timesCalled_ = 0;
    std::shared_ptr<ast::FunctionDeclaration> declaration;
};

#endif //MATURSKI_FUNCTION_H
