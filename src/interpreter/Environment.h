//
// Created by kemal on 11/13/2023.
//

#ifndef MATURSKI_ENVIRONMENT_H
#define MATURSKI_ENVIRONMENT_H

#include <memory>
#include <unordered_map>
#include <utility>
#include "RuntimeValue.h"
#include "Token.h"

class Environment {
public:
    Environment() : parent(nullptr) {};
    explicit Environment(Environment* parent) : parent(parent) {}
    explicit Environment(std::shared_ptr<Environment> parent) : parent(parent.get()) {}
    std::unordered_map<std::string, std::pair<RuntimeValuePtr, bool>> variables{}; // Holds a map of variable names bound to a std::pair that holds the runtime value and whether the variable is constant
    Environment* parent; /** Holds the parent environment of the env. If this is nullptr, it means that the environment is the global one. */
    /**
     * Makes a new variable in the environment
     * @param name shared_ptr<Token> variable that contains the token of the variable identifier
     * @param value std::shared_ptr<RuntimeValue> that can either hold a value or be nullptr. In case it is nullptr, variable will be initialized to a NullValue. Important to note is that it does not check if a const variable has tried to be initialized without a value. That is something that must be checked beforehand.
     * @param isConstant bool value that defines whether the variable should be a constant or not.
     * @throws VariableRedeclaration if name parameter already matches an existing value in the environment.
     */
    void define(std::shared_ptr<Token> name, RuntimeValuePtr value, bool isConstant);
    /**
     *
     * @param name String variable that provides the identifier of the desired variable
     * @return std::shared_ptr<RuntimeValue> if it has been found in the environment or some parent environment
     * @throws UndeclaredVariable Throws if provided an identifier of a non-existing variable
     */
    RuntimeValuePtr get(std::shared_ptr<Token> name);

    /**
     * Assigns a value to an existing variable
     * @param name shared_ptr<Token> pointer that holds the identifier of the variable
     * @param value shared_ptr<RuntimeValue> pointer that holds the value to be for assignment
     * @throws UndeclaredVariable Throws if provided an identifier of a non-existing variable
     * @throws ConstReassignment Throws if assign is called on a constant variable
     */
    void assign(std::shared_ptr<Token> name, RuntimeValuePtr value);
};


#endif //MATURSKI_ENVIRONMENT_H
