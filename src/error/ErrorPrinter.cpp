//
// Created by kemal on 05/11/2023.
//

#include <sstream>
#include "ErrorPrinter.h"

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