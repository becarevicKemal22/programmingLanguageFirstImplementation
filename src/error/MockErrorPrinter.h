//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_MOCKERRORPRINTER_H
#define MATURSKI_MOCKERRORPRINTER_H

#include "ErrorPrinter.h"

class MockErrorPrinter : public ErrorPrinter{
public:
    MockErrorPrinter() : ErrorPrinter("") {}
    ~MockErrorPrinter() override = default;
    void printLexerError(unsigned int line, unsigned int offset, std::string message) override;
    void expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken, std::string beforeWhat) override;
    void wrongTypeArgument(Token wrongToken, std::string toWhat, std::string whichType) override;
    void invalidOperands(Token left, Token op, Token right, std::string toWhat, std::string leftType, std::string rightType) override;
    unsigned int numberOfTimesCalled = 0; // For testing purposes
};


#endif //MATURSKI_MOCKERRORPRINTER_H
