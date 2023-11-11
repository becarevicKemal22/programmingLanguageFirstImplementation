//
// Created by kemal on 06/11/2023.
//

#include "MockErrorPrinter.h"

void MockErrorPrinter::printLexerError(unsigned int line, unsigned int offset, std::string message) {
    numberOfTimesCalled++;
}

void MockErrorPrinter::expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken, std::string beforeWhat){
    numberOfTimesCalled++;
}

void MockErrorPrinter::wrongTypeArgument(Token wrongToken, std::string toWhat, std::string whichType){
    numberOfTimesCalled++;
}

void MockErrorPrinter::invalidOperands(Token left, Token op, Token right, std::string toWhat, std::string leftType, std::string rightType){
    numberOfTimesCalled++;
}