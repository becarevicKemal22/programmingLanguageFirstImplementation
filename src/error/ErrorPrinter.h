//
// Created by kemal on 05/11/2023.
//

#ifndef MATURSKI_ERRORPRINTER_H
#define MATURSKI_ERRORPRINTER_H

#include <string>
#include <vector>

class ErrorPrinter {
public:
    explicit ErrorPrinter(const std::string& source);
    virtual ~ErrorPrinter() = default;
    void printError(unsigned int line, unsigned int offset, std::string message);
    unsigned int numberOfPrintedErrors = 0; // For testing purposes
private:
    std::vector<std::string> lines;
    void extractLines(const std::string& source);
};


#endif //MATURSKI_ERRORPRINTER_H
