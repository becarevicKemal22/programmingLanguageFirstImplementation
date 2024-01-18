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
        {"inace", TokenType::Inace},
        {"onda", TokenType::Onda},
        {"dok", TokenType::Dok},
        {"za", TokenType::Za},
        {"prazno", TokenType::Prazno},
        {"tacno", TokenType::Tacno},
        {"netacno", TokenType::Netacno},
        {"print", TokenType::Print},
        {"funkcija", TokenType::Funkcija},
        {"vrati", TokenType::Vrati},
};

#endif //MATURSKI_KEYWORDS_H
