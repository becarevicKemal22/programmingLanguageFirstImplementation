//
// Created by kemal on 05/11/2023.
//

#ifndef MATURSKI_ERRORPRINTER_H
#define MATURSKI_ERRORPRINTER_H

#include <string>
#include <vector>
#include "Token.h"

class ErrorPrinter {
public:
    explicit ErrorPrinter(const std::string& source);
    virtual ~ErrorPrinter() = default;
    virtual void printLexerError(unsigned int line, unsigned int offset, std::string message) = 0;
    virtual void expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken, std::string beforeWhat) = 0;
    virtual void wrongTypeArgument(Token wrongToken, std::string toWhat, std::string whichType = "") = 0;
    virtual void invalidOperands(Token left, Token op, Token right, std::string toWhat, std::string leftType, std::string rightType) = 0;
    virtual void highlightTokenError(Token tokenToHighlight, std::string message) = 0;
protected:
    std::vector<std::string> lines = {};
    void extractLines(const std::string& source);
};


#endif //MATURSKI_ERRORPRINTER_H
