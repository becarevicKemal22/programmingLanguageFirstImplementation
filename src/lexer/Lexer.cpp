//
// Created by kemal on 04/11/2023.
//

#include <iostream>
#include <stdexcept>
#include "Lexer.h"
#include "Keywords.h"

using std::string;

bool isNumericDigit(char c);

std::vector<Token> Lexer::tokenize(ErrorPrinter& printer) {
    while (source[currentChar] != '\0') {
        char c = source[currentChar];
        if (c == '(') {
            pushToken(TokenType::OpenParen, c);
            advance();
        } else if (c == ')') {
            pushToken(TokenType::ClosedParen, c);
            advance();
        } else if (c == '{') {
            pushToken(TokenType::OpenBrace, c);
            advance();
        } else if (c == '}') {
            pushToken(TokenType::ClosedBrace, c);
            advance();
        } else if (c == '[') {
            pushToken(TokenType::OpenBracket, c);
            advance();
        } else if (c == ']') {
            pushToken(TokenType::ClosedBracket, c);
            advance();
        } else if (c == '+' || c == '-' || c == '*' || c == '%') {
            pushToken(TokenType::BinarniOperator, c);
            advance();
        } else if (c == '/') {
            if (source[currentChar + 1] == '/') {
                handleComment();
            } else {
                pushToken(TokenType::BinarniOperator, c);
                advance();
            }
        } else if (c == ';') {
            pushToken(TokenType::Semicolon, c);
            advance();
        } else if (c == ':') {
            pushToken(TokenType::Colon, c);
            advance();
        } else if (c == ',') {
            pushToken(TokenType::Comma, c);
            advance();
        } else if (c == '.') {
            pushToken(TokenType::Dot, c);
            advance();
        } else if (c == '=') {
            if (source[currentChar + 1] == '=') {
                pushToken(TokenType::DoubleEqual, "==");
                advance();
                advance();
            } else {
                pushToken(TokenType::Equal, "=");
                advance();
            }
        } else if (c == '\n' || c == '\r') {
            newLine();
        } else if (c == ' ') {
            advance();
        } else if (c == '\t'){
            advance();
            charIndexOnLine += 3;
        } else if (isalnum(c)){
            if(isalpha(c)){
                std::string identifier;
                identifier += c;
                while((isalnum(source[currentChar + 1]) || source[currentChar + 1] == '_') && source[currentChar + 1] != '\0'){
                    advance();
                    identifier += source[currentChar];
                }
                TokenType type = TokenType::Identifikator;
                auto it = KEYWORDS.find(identifier);
                if(it != KEYWORDS.end()){
                    type = it->second;
                }
                pushToken(type, identifier);
                advance();
            }else{
                std::string number;
                number += c;
                while((isNumericDigit(source[currentChar + 1]) || (source[currentChar + 1 ] == '.' && isNumericDigit(source[currentChar + 2]))) && source[currentChar + 1] != '\0'){
                    advance();
                    number += source[currentChar];
                }
                pushToken(TokenType::Broj, number);
                advance();
            }
        }
        else{
            std::string message = "Unexpected token '";
            message += c;
            message += "' found.";
            printer.printLexerError(line, charIndexOnLine, message);
            throw std::runtime_error(message);
        }
    }

    pushToken(TokenType::Eof, "");
    return tokens;
}

void Lexer::print() const {
    for (const auto token: tokens) {
        std::cout << "TokenValue: " << token.value << ", Line: " << token.line << "CharOffset: " << token.charOffset
                  << "\n";
    }
}

void Lexer::handleComment(){
    while (source[currentChar] != '\n') {
        currentChar++;
        if (source[currentChar] == '\0') {
            currentChar--;
            break;
        }
    }
    newLine();
}

void Lexer::advance(){
    currentChar++;
    charIndexOnLine++;
}

void Lexer::newLine(){
    line++;
    currentChar++;
    charIndexOnLine = 0;
}

bool isNumericDigit(char c){
    return c >= '0' && c <= '9';
}