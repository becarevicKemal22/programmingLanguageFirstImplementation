//
// Created by kemal on 06/11/2023.
//

#include "MockErrorPrinter.h"

void MockErrorPrinter::printError(unsigned int line, unsigned int offset, std::string message) {
    numberOfTimesCalled++;
}