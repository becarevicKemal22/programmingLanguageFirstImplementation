//
// Created by kemal on 06/11/2023.
//

#ifndef MATURSKI_CONSOLEERRORPRINTER_H
#define MATURSKI_CONSOLEERRORPRINTER_H

#include "ErrorPrinter.h"

class ConsoleErrorPrinter : public ErrorPrinter {
public:
    explicit ConsoleErrorPrinter(const std::string& source) : ErrorPrinter(source) {}
    ~ConsoleErrorPrinter() override = default;
    void printError(unsigned int line, unsigned int offset, std::string message) override;
};


#endif //MATURSKI_CONSOLEERRORPRINTER_H
