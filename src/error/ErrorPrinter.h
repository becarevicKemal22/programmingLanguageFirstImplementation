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
    virtual void printError(unsigned int line, unsigned int offset, std::string message) = 0;
protected:
    std::vector<std::string> lines;
    void extractLines(const std::string& source);
};


#endif //MATURSKI_ERRORPRINTER_H
