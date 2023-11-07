//
// Created by kemal on 04/11/2023.
//

#ifndef MATURSKI_TOKENTYPE_H
#define MATURSKI_TOKENTYPE_H

enum class TokenType{
    Eof,
    OpenParen, ClosedParen, OpenBrace, ClosedBrace, OpenBracket, ClosedBracket,
    Var, Konst, Ako, Dok, Identifikator, Broj, Prazno, Tacno, Netacno,
    BinarniOperator,
    Semicolon, Colon, Comma, Dot,
    Equal, DoubleEqual
};

#endif //MATURSKI_TOKENTYPE_H