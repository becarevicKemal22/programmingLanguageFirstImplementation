//
// Created by kemal on 11/11/2023.
//

#include "Interpreter.h"
#include "NumericLiteral.h"
#include "Statement.h"
#include "Program.h"
#include "NumericValue.h"
#include "BooleanValue.h"
#include "BooleanLiteral.h"
#include "NullLiteral.h"
#include "NullValue.h"
#include "GroupingExpression.h"
#include "UnaryExpression.h"

RuntimeValuePtr Interpreter::visitProgram(const ast::Program *program) {
    RuntimeValuePtr lastEvaluated = nullptr;
    for (auto statement : program->body) {
        try{
            lastEvaluated = statement->accept(this);
        }catch(std::exception& e){
            std::cout << e.what() << std::endl;
            exit(1);
        }
    }
    if(!lastEvaluated){
        return std::make_shared<NullValue>();
    }
    return lastEvaluated;
}

RuntimeValuePtr Interpreter::visitStatement(const ast::Statement *expr) {
    throw std::logic_error("Interpreter called on statement base class.");
}

RuntimeValuePtr Interpreter::visitExpression(const ast::Expression *expr) {
    throw std::logic_error("Interpreter called on expression base class.");
}

RuntimeValuePtr Interpreter::visitNumericLiteral(const ast::NumericLiteral *expr) {
    return std::make_shared<NumericValue>(expr->number);
}

RuntimeValuePtr Interpreter::visitBooleanLiteral(const ast::BooleanLiteral *expr) {
    return std::make_shared<BooleanValue>(expr->value);
}

RuntimeValuePtr Interpreter::visitNullLiteral(const ast::NullLiteral *expr) {
    return std::make_shared<NullValue>();
}

RuntimeValuePtr Interpreter::visitGroupingExpression(const ast::GroupingExpression *expr) {
    return evaluate(expr->expr.get());
}

RuntimeValuePtr Interpreter::visitUnaryExpression(const ast::UnaryExpression *expr) {
    RuntimeValuePtr right = evaluate(expr->right.get());
    switch(expr->_operator->type){
        case TokenType::Minus:
            if(right->type != ValueType::Number){
                printer.wrongTypeArgument(getMostRelevantToken(expr->right.get()), "unary expression",
                                          stringifyRuntimeType(right->type));
                error("Unary minus operator can only be applied to numeric values.");
            }
            return std::make_shared<NumericValue>(-std::dynamic_pointer_cast<NumericValue>(right)->value);
        case TokenType::Bang:
            return std::make_shared<BooleanValue>(!isTruthy(right));
        default:
            error("Unknown unary operator.");
    }
}

RuntimeValuePtr Interpreter::visitBinaryExpression(const ast::BinaryExpression *expr) {
    RuntimeValuePtr left = evaluate(expr->left.get());
    RuntimeValuePtr right = evaluate(expr->right.get());
    switch(expr->_operator->type){
        case TokenType::Minus: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "binary expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<NumericValue>(leftNum->value - rightNum->value);
        }
        case TokenType::Plus: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "binary expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<NumericValue>(leftNum->value + rightNum->value);
        }
        case TokenType::Star: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "binary expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<NumericValue>(leftNum->value * rightNum->value);
        }
        case TokenType::Slash: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "binary expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<NumericValue>(leftNum->value / rightNum->value);
        }
        case TokenType::Percent: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "binary expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<NumericValue>(int(leftNum->value) % int(rightNum->value));
        }
        case TokenType::Greater: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "comparison expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<BooleanValue>(leftNum->value > rightNum->value);
        }
        case TokenType::GreaterEqual: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "comparison expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<BooleanValue>(leftNum->value >= rightNum->value);
        }
        case TokenType::Less: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "comparison expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<BooleanValue>(leftNum->value < rightNum->value);
        }
        case TokenType::LessEqual: {
            if(!areOperandsNumeric(left, right)){
                printer.invalidOperands(getMostRelevantToken(expr->left.get()), *expr->_operator.get(), getMostRelevantToken(expr->right.get()), "comparison expression", stringifyRuntimeType(left->type), stringifyRuntimeType(right->type));
                error("Minus operator can only be applied to numeric values.");
            }
            std::shared_ptr<NumericValue> leftNum = std::dynamic_pointer_cast<NumericValue>(left);
            std::shared_ptr<NumericValue> rightNum = std::dynamic_pointer_cast<NumericValue>(right);
            return std::make_shared<BooleanValue>(leftNum->value <= rightNum->value);
        }
        case TokenType::DoubleEqual: {
            return std::make_shared<BooleanValue>(isEqual(left, right));
        }
        case TokenType::BangEqual: {
            return std::make_shared<BooleanValue>(!isEqual(left, right));
        }
        default:
            error("Unknown binary operator.");
    }
}

RuntimeValuePtr Interpreter::evaluate(ast::Expression *expr) {
    return expr->accept(this);
}

bool Interpreter::isTruthy(RuntimeValuePtr value) {
    if(std::dynamic_pointer_cast<NullValue>(value)) return false;
    if(std::dynamic_pointer_cast<BooleanValue>(value)) return std::dynamic_pointer_cast<BooleanValue>(value)->value;
    if(std::dynamic_pointer_cast<NumericValue>(value)) return std::dynamic_pointer_cast<NumericValue>(value)->value != 0;
    return true;
}

bool Interpreter::areOperandsNumeric(RuntimeValuePtr left, RuntimeValuePtr right) {
    return (left->type == ValueType::Number) && (right->type == ValueType::Number);
}

Token Interpreter::getMostRelevantToken(ast::Expression* expr){
    if(auto binaryExpr = dynamic_cast<ast::BinaryExpression*>(expr)){
        return *binaryExpr->_operator;
    }
    if(auto unaryExpr = dynamic_cast<ast::UnaryExpression*>(expr)){
        return *unaryExpr->_operator;
    }
    if(auto groupingExpr = dynamic_cast<ast::GroupingExpression*>(expr)){
        return getMostRelevantToken(groupingExpr->expr.get());
    }
    if(auto literal = dynamic_cast<ast::NumericLiteral*>(expr)){
        return *literal->token;
    }
    if(auto literal = dynamic_cast<ast::BooleanLiteral*>(expr)){
        return *literal->token;
    }
    if(auto literal = dynamic_cast<ast::NullLiteral*>(expr)){
        return *literal->token;
    }
    error("Unknown expression type.");
}

bool Interpreter::isEqual(RuntimeValuePtr left, RuntimeValuePtr right){
    if(left->type == ValueType::Null && right->type == ValueType::Null) return true;
    if(left->type == ValueType::Null || right->type == ValueType::Null) return false;
    if(left->type == ValueType::Number && right->type == ValueType::Number){
        return std::dynamic_pointer_cast<NumericValue>(left)->value == std::dynamic_pointer_cast<NumericValue>(right)->value;
    }
    if(left->type == ValueType::Boolean && right->type == ValueType::Boolean){
        return std::dynamic_pointer_cast<BooleanValue>(left)->value == std::dynamic_pointer_cast<BooleanValue>(right)->value;
    }
    return false;
}

void Interpreter::error(std::string message){
    hadRuntimeError = true;
    throw std::runtime_error(message);
}