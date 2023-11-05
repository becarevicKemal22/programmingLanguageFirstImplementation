//
// Created by kemal on 05/11/2023.
//

#include <sstream>
#include <iostream>
#include "ErrorPrinter.h"

using std::cout;

const std::string ANSI_RED = "\033[31m";
const std::string ANSI_RESET = "\033[0m";

ErrorPrinter::ErrorPrinter(const std::string &source) {
    extractLines(source);
}

void ErrorPrinter::extractLines(const std::string &source) {
    std::istringstream ss(source);
    std::string line;
    while(std::getline(ss, line, '\n')){
        lines.push_back(line);
    }
}

void ErrorPrinter::printError(unsigned int line, unsigned int offset, std::string message) const {
    cout << ANSI_RED << "Error on line " << line << ": " << ANSI_RESET << message << "\n \t";
    cout << line << " | " << lines.at(line - 1) << "\n";
    std::string lineNo = std::to_string(line);
    int numOfDigits = lineNo.length();
    int totalOffset = offset - 1;
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