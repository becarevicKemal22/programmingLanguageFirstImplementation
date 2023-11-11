//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_CONSOLEERRORPRINTER_H
#define MATURSKI_CONSOLEERRORPRINTER_H

#include "ErrorPrinter.h"
#include "Token.h"

class ConsoleErrorPrinter : public ErrorPrinter {
public:
    explicit ConsoleErrorPrinter(const std::string& source) : ErrorPrinter(source) {}
    ~ConsoleErrorPrinter() override = default;
    void printLexerError(unsigned int line, unsigned int offset, std::string message) override;
    void expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken, std::string beforeWhat) override;
    void wrongTypeArgument(Token wrongToken, std::string toWhat, std::string whichType) override;
    void invalidOperands(Token left, Token op, Token right, std::string toWhat, std::string leftType, std::string rightType) override;
private:
    void errorOnLine(unsigned int line, std::string message);
    void printSourceLine(unsigned int line, int maxW);
    void printSupportPointerTypeLine(unsigned int line, unsigned int charToPoint);
    void printSourceLineWithHighlightedToken(unsigned int line, unsigned int maxW, Token tokenToHighlight, std::string ANSI_COLOR_CODE);
    void printSourceLineWithHighlightedTokens(unsigned int line, unsigned int maxW, std::vector<Token> tokensToHighlight, std::vector<std::string> ANSI_COLOR_CODES);
    void printSupportLineWithHighlightedToken(unsigned int maxW, Token tokenToHighlight, std::string ANSI_COLOR_CODE, int missingCharPointIndex = -1);
    void printSupportLineWithHighlightedTokens(unsigned int maxW, std::vector<Token> tokensToHighlight, std::vector<std::string> ANSI_COLOR_CODES, std::vector<char> highlightChars);
    void printMissingCharHint(unsigned int maxW, std::string expected, std::string ANSI_COLOR_CODE, int missingCharIndex);
    void printSupportMissingCharPointerLine(unsigned int maxW, std::string ANSI_COLOR_CODE, int missingCharIndex);
    void printLineDivider(unsigned int maxW, int lineNo = -1);
    void handleLineDifference(unsigned int lineDifference, unsigned int maxW, unsigned int afterTokenLineNumber);
};


#endif //MATURSKI_CONSOLEERRORPRINTER_H
