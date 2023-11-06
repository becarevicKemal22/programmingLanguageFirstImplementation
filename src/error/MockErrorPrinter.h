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
    void printError(unsigned int line, unsigned int offset, std::string message) override;
    unsigned int numberOfTimesCalled = 0; // For testing purposes
};


#endif //MATURSKI_MOCKERRORPRINTER_H
