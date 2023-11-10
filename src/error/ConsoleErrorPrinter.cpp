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

void ConsoleErrorPrinter::printLexerError(unsigned int line, unsigned int offset, std::string message) {
    errorOnLine(line, message);
    printSourceLine(line, std::to_string(line).length());
    printSupportPointerTypeLine(line, offset);
}

void ConsoleErrorPrinter::expectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken,
                                           std::string beforeWhat) {
    std::string message = "Expected '" + expectedWhat + "' before '" + beforeWhat + "'";
    errorOnLine(previousToken.line, message);
    int prev = std::to_string(previousToken.line).length();
    int after = std::to_string(afterToken.line).length();
    int maxW = prev > after ? prev : after;
    int missingCharLocation = previousToken.charOffset + previousToken.value.length();
    int lineDiff = afterToken.line - previousToken.line;
    if(lineDiff == 0){
        printSourceLineWithHighlightedToken(previousToken.line, maxW, afterToken, ANSI_GREEN);
        printSupportLineWithHighlightedToken(maxW, afterToken, ANSI_GREEN, missingCharLocation);
        printMissingCharHint(maxW, expectedWhat, ANSI_GREEN, missingCharLocation);
    }else{
        printSourceLine(previousToken.line, maxW);
        printSupportMissingCharPointerLine(maxW, ANSI_RED, missingCharLocation);
        printMissingCharHint(maxW, expectedWhat, ANSI_GREEN, missingCharLocation);
        if(lineDiff > 1){
            if(lineDiff == 2){
                printLineDivider(maxW, afterToken.line - 1);
                cout << "\n";
            }else{
                cout << "\t" << "...\n";
                printLineDivider(maxW, afterToken.line - 1);
                cout << "\n";
            }
        }

        printSourceLineWithHighlightedToken(afterToken.line, maxW, afterToken, ANSI_GREEN);
        printSupportLineWithHighlightedToken(maxW, afterToken, ANSI_GREEN);
    }
}

void ConsoleErrorPrinter::errorOnLine(unsigned int line, std::string message) {
    cout << ANSI_RED << "Error on line " << line << ": " << ANSI_RESET << message << "\n";
}

void ConsoleErrorPrinter::printSourceLine(unsigned int line, int maxW) {
    cout << "\t" << std::setw(maxW) << std::right << line << std::setfill(' ') << std::left << " | " << lines.at(line - 1) << "\n";
}

void ConsoleErrorPrinter::printSupportPointerTypeLine(unsigned int line, unsigned int charToPoint) {
    std::string lineNo = std::to_string(line);
    int numOfDigits = lineNo.length();
    cout << "\t";
    for(int i = 0; i < numOfDigits; i++){
        cout << " ";
    }
    std::string pointer;
    for(int i = 0; i < charToPoint; i++){
        pointer += "~";
    }
    pointer += "^";
    cout << " | " << ANSI_RED << pointer << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printSourceLineWithHighlightedToken(unsigned int line, unsigned int maxW, Token tokenToHighlight, std::string ANSI_COLOR_CODE){
    cout << "\t" << std::setw(maxW) << std::right << line << std::setfill(' ') << std::left << " | ";
    std::string lineStr = lines.at(line - 1);
    size_t length = lineStr.length();
    unsigned int startChar = tokenToHighlight.charOffset;
    unsigned int endChar = startChar + tokenToHighlight.value.length();
    for(int i = 0; i < length; i++){
        if(i == startChar){
            cout << ANSI_COLOR_CODE;
        }else if(i == endChar){
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
    for(int i = 0; i < startChar; i++){
        if(i == missingCharPointIndex){
            cout << ANSI_RED << "^" << ANSI_RESET;
        }else{
            cout << " ";
        }
    }
    cout << ANSI_COLOR_CODE;
    for(int i = startChar; i < endChar; i++){
        if(i == missingCharPointIndex){
            cout << ANSI_RED << "^" << ANSI_COLOR_CODE;
        }else{
            cout << "~";
        }
    }
    cout << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printMissingCharHint(unsigned int maxW, std::string expected, std::string ANSI_COLOR_CODE, int missingCharIndex){
    cout << "\t" << std::setw(maxW) << " " << " | ";
    for(int i = 0; i < missingCharIndex; i++){
        cout << " ";
    }
    cout << ANSI_COLOR_CODE << expected << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printSupportMissingCharPointerLine(unsigned int maxW, std::string ANSI_COLOR_CODE, int missingCharIndex){
    cout << "\t" << std::setw(maxW) << " " << " | ";
    for(int i = 0; i < missingCharIndex; i++){
        cout << " ";
    }
    cout << ANSI_COLOR_CODE << "^" << ANSI_RESET << "\n";
}

void ConsoleErrorPrinter::printLineDivider(unsigned int maxW, int lineNo){
    if(lineNo == -1){
        cout << "\t" << std::setw(maxW) << " " << " | ";
        return;
    }
    cout << "\t" << std::setw(maxW) << std::right << lineNo << std::setfill(' ') << std::left << " | ";
}