//
// Created by kemal on 06/11/2023.
//

#include <iostream>
#include <iomanip>
#include "ConsoleErrorPrinter.h"

using std::cout;

const std::string ANSI_RED = "\033[31m";
const std::string ANSI_RESET = "\033[0m";
const std::string ANSI_GREEN = "\033[32m";
const std::string ANSI_BLUE = "\033[34m";

void ConsoleErrorPrinter::printLexerError(unsigned int line, unsigned int offset, std::string message) {
    errorOnLine(line, message);
    printSourceLine(line, std::to_string(line).length());
    printSupportPointerTypeLine(line, offset);
}

void ConsoleErrorPrinter::expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken,
                                           std::string beforeWhat) {
    std::string message = "Expected '" + expectedWhat + "' before ";
    if(afterToken.type == TokenType::Eof){
        message += "end of input";
    }else{
        message += "'" + beforeWhat + "'";
    }
    errorOnLine(previousToken.line, message);
    int prev = std::to_string(previousToken.line).length();
    int after = std::to_string(afterToken.line).length();
    int maxW = prev > after ? prev : after;
    int missingCharLocation = previousToken.charOffset + previousToken.value.length();
    int lineDiff = afterToken.line - previousToken.line;
    if (lineDiff == 0) {
        printSourceLineWithHighlightedToken(previousToken.line, maxW, afterToken, ANSI_GREEN);
        printSupportLineWithHighlightedToken(maxW, afterToken, ANSI_GREEN, missingCharLocation);
        printMissingCharHint(maxW, expectedWhat, ANSI_RED, missingCharLocation);
    } else {
        printSourceLine(previousToken.line, maxW);
        printSupportMissingCharPointerLine(maxW, ANSI_RED, missingCharLocation);
        printMissingCharHint(maxW, expectedWhat, ANSI_GREEN, missingCharLocation);
        if (lineDiff > 1) {
            if (lineDiff == 2) {
                printLineDivider(maxW, afterToken.line - 1);
                cout << "\n";
            } else {
                cout << "\t" << "...\n";
                printLineDivider(maxW, afterToken.line - 1);
                cout << "\n";
            }
        }

        printSourceLineWithHighlightedToken(afterToken.line, maxW, afterToken, ANSI_GREEN);
        printSupportLineWithHighlightedToken(maxW, afterToken, ANSI_GREEN);
    }
}

void ConsoleErrorPrinter::wrongTypeArgument(Token wrongToken, std::string toWhat, std::string whichType) {
    std::string message = "Wrong type ";
    if (whichType != "") {
        message += "'" + whichType + "' ";
    }
    message += "argument to " + toWhat;
    errorOnLine(wrongToken.line, message);
    printSourceLineWithHighlightedToken(wrongToken.line, std::to_string(wrongToken.line).length(), wrongToken,
                                        ANSI_RED);
    printSupportLineWithHighlightedToken(std::to_string(wrongToken.line).length(), wrongToken, ANSI_RED);
}

void ConsoleErrorPrinter::invalidOperands(Token left, Token op, Token right, std::string toWhat, std::string leftType,
                                          std::string rightType) {
    std::string message = "Invalid operands '" + leftType + "' and '" + rightType + "' to " + toWhat;
    errorOnLine(left.line, message);
    int maxW = std::to_string(right.line).length();
    if (right.line > left.line) {
        if(left.line == op.line){
            printSourceLineWithHighlightedTokens(left.line, maxW, {left, op}, {ANSI_GREEN, ANSI_RED});
            printSupportLineWithHighlightedTokens(maxW, {left, op}, {ANSI_GREEN, ANSI_RED}, {'~', '^'});
            unsigned int lineDiff = right.line - op.line;
            handleLineDifference(lineDiff, maxW, right.line);
            printSourceLineWithHighlightedToken(right.line, maxW, right, ANSI_BLUE);
            printSupportLineWithHighlightedToken(maxW, right, ANSI_BLUE);
        }else if(op.line == right.line){
            printSourceLineWithHighlightedToken(left.line, maxW, left, ANSI_GREEN);
            printSupportLineWithHighlightedToken(maxW, left, ANSI_GREEN);
            unsigned int lineDiff = op.line - left.line;
            handleLineDifference(lineDiff, maxW, right.line);
            printSourceLineWithHighlightedTokens(op.line, maxW, {op, right}, {ANSI_RED, ANSI_BLUE});
            printSupportLineWithHighlightedTokens(maxW, {op, right}, {ANSI_RED, ANSI_BLUE}, {'^', '~'});
        } else{
            printSourceLineWithHighlightedToken(left.line, maxW, left, ANSI_GREEN);
            printSupportLineWithHighlightedToken(maxW, left, ANSI_GREEN);
            unsigned int lineDiff = op.line - left.line;
            handleLineDifference(lineDiff, maxW, op.line);
            printSourceLineWithHighlightedToken(op.line, maxW, op, ANSI_RED);
            printSupportLineWithHighlightedToken(maxW, op, ANSI_RED, op.charOffset);
            lineDiff = right.line - op.line;
            handleLineDifference(lineDiff, maxW, right.line);
            printSourceLineWithHighlightedToken(right.line, maxW, right, ANSI_BLUE);
            printSupportLineWithHighlightedToken(maxW, right, ANSI_BLUE);
        }
    } else {
        printSourceLineWithHighlightedTokens(left.line, maxW, {left, op, right}, {ANSI_GREEN, ANSI_RED, ANSI_BLUE});
        printSupportLineWithHighlightedTokens(maxW, {left, op, right}, {ANSI_GREEN, ANSI_RED, ANSI_BLUE}, {'~', '^', '~'});
    }
}

void ConsoleErrorPrinter::errorOnLine(unsigned int line, std::string message) {
    cout << ANSI_RED << "Error on line " << line << ": " << ANSI_RESET << message << "\n";
}

void ConsoleErrorPrinter::printSourceLine(unsigned int line, int maxW) {
    cout << "\t" << std::setw(maxW) << std::right << line << std::setfill(' ') << std::left << " | "
         << lines.at(line - 1) << "\n";
}

void ConsoleErrorPrinter::printSupportPointerTypeLine(unsigned int line, unsigned int charToPoint) {
    std::string lineNo = std::to_string(line);
    int numOfDigits = lineNo.length();
    cout << "\t";
    for (int i = 0; i < numOfDigits; i++) {
        cout << " ";
    }
    std::string pointer;
    for (int i = 0; i < charToPoint; i++) {
        pointer += "~";
    }
    pointer += "^";
    cout << " | " << ANSI_RED << pointer << ANSI_RESET << "\n";
}

void
ConsoleErrorPrinter::printSourceLineWithHighlightedToken(unsigned int line, unsigned int maxW, Token tokenToHighlight,
                                                         std::string ANSI_COLOR_CODE) {
    if(tokenToHighlight.type == TokenType::Eof) return;

    cout << "\t" << std::setw(maxW) << std::right << line << std::setfill(' ') << std::left << " | ";
    std::string lineStr = lines.at(line - 1);
    size_t length = lineStr.length();
    unsigned int startChar = tokenToHighlight.charOffset;
    unsigned int endChar = startChar + tokenToHighlight.value.length();
    for (int i = 0; i < length; i++) {
        if (i == startChar) {
            cout << ANSI_COLOR_CODE;
        } else if (i == endChar) {
            cout << ANSI_RESET;
        }
        cout << lineStr[i];
    }
    cout << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printSupportLineWithHighlightedToken(unsigned int maxW, Token tokenToHighlight,
                                                               std::string ANSI_COLOR_CODE, int missingCharPointIndex) {
    cout << "\t" << std::setw(maxW) << " " << " | ";
    unsigned int startChar = tokenToHighlight.charOffset;
    unsigned int endChar = startChar + tokenToHighlight.value.length();
    for (int i = 0; i < startChar; i++) {
        if (i == missingCharPointIndex) {
            cout << ANSI_RED << "^" << ANSI_RESET;
        } else {
            cout << " ";
        }
    }
    cout << ANSI_COLOR_CODE;
    for (int i = startChar; i < endChar; i++) {
        if (i == missingCharPointIndex) {
            cout << ANSI_RED << "^" << ANSI_COLOR_CODE;
        } else {
            cout << "~";
        }
    }
    cout << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printMissingCharHint(unsigned int maxW, std::string expected, std::string ANSI_COLOR_CODE,
                                               int missingCharIndex) {
    cout << "\t" << std::setw(maxW) << " " << " | ";
    for (int i = 0; i < missingCharIndex; i++) {
        cout << " ";
    }
    cout << ANSI_COLOR_CODE << expected << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printSupportMissingCharPointerLine(unsigned int maxW, std::string ANSI_COLOR_CODE,
                                                             int missingCharIndex) {
    cout << "\t" << std::setw(maxW) << " " << " | ";
    for (int i = 0; i < missingCharIndex; i++) {
        cout << " ";
    }
    cout << ANSI_COLOR_CODE << "^" << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printLineDivider(unsigned int maxW, int lineNo) {
    if (lineNo == -1) {
        cout << "\t" << std::setw(maxW) << " " << " | ";
        return;
    }
    cout << "\t" << std::setw(maxW) << std::right << lineNo << std::setfill(' ') << std::left << " | ";
}

void ConsoleErrorPrinter::printSourceLineWithHighlightedTokens(unsigned int line, unsigned int maxW,
                                                               std::vector<Token> tokensToHighlight,
                                                               std::vector<std::string> ANSI_COLOR_CODES) {
    cout << "\t" << std::setw(maxW) << std::right << line << std::setfill(' ') << std::left << " | ";
    std::string lineStr = lines.at(line - 1);
    size_t length = lineStr.length();
    unsigned int startChar = tokensToHighlight.at(0).charOffset;
    unsigned int endChar = startChar + tokensToHighlight.at(0).value.length();
    unsigned int currentTokenIndex = 0;
    for (int i = 0; i < length; i++) {
        if (i == startChar) {
            cout << ANSI_COLOR_CODES.at(currentTokenIndex);
        } else if (i == endChar) {
            cout << ANSI_RESET;
            currentTokenIndex++;
            if (currentTokenIndex < tokensToHighlight.size()) {
                startChar = tokensToHighlight.at(currentTokenIndex).charOffset;
                endChar = startChar + tokensToHighlight.at(currentTokenIndex).value.length();
            }
        }
        if(i == startChar){ // If the tokens are next to one another, the first's endChar will be the same as the next's startChar, so this handles that case as i will be equal to the last's endChar after the above code
            cout << ANSI_COLOR_CODES.at(currentTokenIndex);
        }
        cout << lineStr[i];
    }
    cout << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printSupportLineWithHighlightedTokens(unsigned int maxW, std::vector<Token> tokensToHighlight,
                                                                std::vector<std::string> ANSI_COLOR_CODES, std::vector<char> highlightChars) {
    cout << "\t" << std::setw(maxW) << " " << " | ";
    Token lastToken = tokensToHighlight.at(tokensToHighlight.size() - 1);
    unsigned int limit = lastToken.charOffset + lastToken.value.length();
    unsigned int currentToken = 0;
    unsigned int startIndex = tokensToHighlight.at(currentToken).charOffset;
    unsigned int endIndex = startIndex + tokensToHighlight.at(currentToken).value.length();
    unsigned int currentIndex = 0;
    while(currentIndex < limit){
        if(currentIndex == startIndex){
            cout << ANSI_COLOR_CODES.at(currentToken);
            char highlightChar = highlightChars.at(currentToken);
            while(currentIndex < endIndex){
                cout << highlightChar;
                currentIndex++;
            }
            cout << ANSI_RESET;
            currentToken++;
            try{
                startIndex = tokensToHighlight.at(currentToken).charOffset;
                endIndex = startIndex + tokensToHighlight.at(currentToken).value.length();
            }catch(std::exception& err){
                break;
            }
        }else{
            cout << " ";
            currentIndex++;
        }
    }
    cout << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::handleLineDifference(unsigned int lineDifference, unsigned int maxW, unsigned int afterTokenLineNumber){
    if (lineDifference > 1) {
        if (lineDifference == 2) {
            printLineDivider(maxW, afterTokenLineNumber - 1);
            cout << "\n";
        } else {
            cout << "\t" << "...\n";
            printLineDivider(maxW, afterTokenLineNumber - 1);
            cout << "\n";
        }
    }
}
