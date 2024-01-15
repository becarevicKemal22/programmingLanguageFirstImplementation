//
// Created by kemal on 04/11/2023.
//

#ifndef MATURSKI_TOKENTYPE_H
#define MATURSKI_TOKENTYPE_H

enum class TokenType{
    Eof,
    OpenParen, ClosedParen, OpenBrace, ClosedBrace, OpenBracket, ClosedBracket,
    Var, Konst, Ako, Inace, Onda, Dok, Print, Identifikator, Broj, String, Prazno, Tacno, Netacno,
    Plus, Minus, Star, Slash, Percent,
    Semicolon, Colon, Comma, Dot, Bang, BangEqual, Less, LessEqual, Greater, GreaterEqual,
    Equal, DoubleEqual
};

#endif //MATURSKI_TOKENTYPE_H