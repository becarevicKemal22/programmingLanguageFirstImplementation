//
// Created by kemal on 04/11/2023.
//

#include <iostream>
#include "Lexer.h"

using std::string;

void Lexer::tokenize(const ErrorPrinter& printer) {
    while (source[currentChar] != '\0') {
        char c = source[currentChar];
        if (c == '(') {
            pushToken(TokenType::OpenParen, c);
        } else if (c == ')') {
            pushToken(TokenType::ClosedParen, c);
        } else if (c == '{') {
            pushToken(TokenType::OpenBrace, c);
        } else if (c == '}') {
            pushToken(TokenType::ClosedBrace, c);
        } else if (c == '[') {
            pushToken(TokenType::OpenBracket, c);
        } else if (c == ']') {
            pushToken(TokenType::ClosedBracket, c);
        } else if (c == '+' || c == '-' || c == '*' || c == '%') {
            pushToken(TokenType::BinarniOperator, c);
        } else if (c == '/') {
            if (source[currentChar + 1] == '/') {
                handleComment();
            } else {
                pushToken(TokenType::BinarniOperator, c);
            }
        } else if (c == ';') {
            pushToken(TokenType::Semicolon, c);
        } else if (c == ':') {
            pushToken(TokenType::Colon, c);
        } else if (c == ',') {
            pushToken(TokenType::Comma, c);
        } else if (c == '.') {
            pushToken(TokenType::Dot, c);
        } else if (c == '=') {
            if (source[currentChar + 1] == '=') {
                pushToken(TokenType::DoubleEqual, "==");
                advance();
            } else {
                pushToken(TokenType::Equal, "=");
            }
        } else if (c == '\n' || c == '\r') {
            newLine();
        } else if (c == ' ' || c == '\t') {
        } else{
            std::string message = "Unexpected token '";
            message += c;
            message += "' found.";
            printer.printError(line, charOnLine, message);
            exit(1);
        }
        advance();
    }

    pushToken(TokenType::Eof, "");
}

void Lexer::print() {
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
    charOnLine++;
}

void Lexer::newLine(){
    line++;
    charOnLine = 0;
}