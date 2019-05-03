#ifndef __LEXER_H__
#define __LEXER_H__

enum class StateId {
    Start_q0,
    Start_q1,
    Start_q10,
    Start_q3,
    Start_q8,
    Start_q9,
};

enum class Token {
    Binary,
    Decimal,
    Eof,
    Hex,
    Octal,
};
#endif