//
// Created by kemal on 11/13/2023.
//

#include <memory>
#include "Environment.h"
#include "RuntimeValue.h"
#include "NullValue.h"
#include "exceptions/UndeclaredVariable.h"
#include "exceptions/VariableRedeclaration.h"
#include "exceptions/ConstReassignment.h"

void Environment::define(std::shared_ptr<Token> name, RuntimeValuePtr value, bool isConstant) {
    auto it = variables.find(name->value);
    if(it != variables.end()){
        throw VariableRedeclaration(name, "Redeclaration of '" + name->value + "'");
    }

    if(value == nullptr){
        variables.insert({name->value, {std::make_shared<NullValue>(), isConstant}});
    }
    variables.insert({name->value, {value, isConstant}});
}

RuntimeValuePtr Environment::get(std::shared_ptr<Token> name){
    auto it = variables.find(name->value);
    if(it != variables.end()){
        return it->second.first;
    }
    std::string message = "Use of undeclared identifier '" + name->value + "'";
    throw UndeclaredVariable(name, message);
}

void Environment::assign(std::shared_ptr<Token> name, RuntimeValuePtr value) {
    auto it = variables.find(name->value);
    if(it == variables.end()){
        throw UndeclaredVariable(name, "Use of undeclared identifier '" + name->value + "'");
    }
    if(it->second.second){
        throw ConstReassignment(name, "Can't assign to konst variable '" + name->value + "'");
    }
    variables[name->value] = {value, false};
}