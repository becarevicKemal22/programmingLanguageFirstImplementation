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
