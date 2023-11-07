//
// Created by kemal on 05/11/2023.
//

#ifndef MATURSKI_KEYWORDS_H
#define MATURSKI_KEYWORDS_H

#include <unordered_map>
#include <string>
#include "TokenType.h"

const std::unordered_map<std::string, TokenType> KEYWORDS = {
        {"var", TokenType::Var},
        {"konst", TokenType::Konst},
        {"ako", TokenType::Ako},
        {"dok", TokenType::Dok},
};

#endif //MATURSKI_KEYWORDS_H
