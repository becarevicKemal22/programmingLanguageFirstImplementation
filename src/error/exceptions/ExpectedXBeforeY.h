//
// Created by kemal on 11/17/2023.
//

#ifndef MATURSKI_EXPECTEDXBEFOREY_H
#define MATURSKI_EXPECTEDXBEFOREY_H

#include <exception>
#include <iostream>
#include <memory>
#include "Token.h"

class ExpectedXBeforeY : public std::exception {
    std::string message;
public:
    ExpectedXBeforeY(Token previousToken, std::string expectedWhat, Token afterToken, std::string beforeWhat)
            : previousToken(previousToken), expectedWhat(expectedWhat),
              afterToken(afterToken), beforeWhat(beforeWhat), message("") {
    }

    Token previousToken, afterToken;
    std::string expectedWhat, beforeWhat;

    const char *what() {
        return message.c_str();
    }

    std::string getMessage() {
        return message;
    }
};

#endif //MATURSKI_EXPECTEDXBEFOREY_H
