//
// Created by kemal on 06/11/2023.
//

#include "ConsoleErrorPrinter.h"

#include <iostream>
#include "ConsoleErrorPrinter.h"

using std::cout;

const std::string ANSI_RED = "\033[31m";
const std::string ANSI_RESET = "\033[0m";

void ConsoleErrorPrinter::printError(unsigned int line, unsigned int offset, std::string message) {
    cout << ANSI_RED << "Error on line " << line << ": " << ANSI_RESET << message << "\n \t";
    cout << line << " | " << lines.at(line - 1) << "\n";
    std::string lineNo = std::to_string(line);
    int numOfDigits = lineNo.length();
    int totalOffset = offset;
    cout << "\t";
    for(int i = 0; i < numOfDigits; i++){
        cout << " ";
    }
    cout << " | ";
    for(int i = 0; i < totalOffset; i++){
        cout << ANSI_RED <<  "~";
    }
    cout << ANSI_RED << "^" << ANSI_RESET;
}