Token ConstLexer::getNextToken() {
    StateId state = StateId::Start_q0;
    int ch = getNextChar();

    while (true) {
        switch (state) {
            // Start
            case StateId::Start_q0:
                if (ch == '\n') {
                    state = StateId::Start_q0;
                    ch = getNextChar();
                } else if (ch == ' ') {
                    state = StateId::Start_q0;
                    ch = getNextChar();
                } else if (ch == '\t') {
                    state = StateId::Start_q0;
                    ch = getNextChar();
                } else {
                    state = StateId::Start_q1;
                }
                break;
            case StateId::Start_q1:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = StateId::Start_q9;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = StateId::Start_q8;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '7')) {
                    text += ch;
                    state = StateId::Start_q10;
                    ch = getNextChar();
                } else if (isdigit(ch)) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else if (ch == EOF) {
                    return Token::Eof;
                } else if ((ch >= 'a') && (ch <= 'f')) {
                    text += ch;
                    state = StateId::Start_q9;
                    ch = getNextChar();
                } else {
                    reportError(ch);
                    ch = getNextChar();
                    state = StateId::Start_q0;
                }
                break;
            case StateId::Start_q10:
                if ((ch >= '0') && (ch <= '7')) {
                    text += ch;
                    state = StateId::Start_q10;
                    ch = getNextChar();
                } else if ((ch >= '8') && (ch <= '9')) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Octal;
                }
                break;
            case StateId::Start_q3:
                if (isdigit(ch)) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Decimal;
                }
                break;
            case StateId::Start_q8:
                if ((ch >= '2') && (ch <= '9')) {
                    text += ch;
                    state = StateId::Start_q3;
                    ch = getNextChar();
                } else if ((ch >= '0') && (ch <= '1')) {
                    text += ch;
                    state = StateId::Start_q8;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Binary;
                }
                break;
            case StateId::Start_q9:
                if ((ch >= '0') && (ch <= '9')) {
                    text += ch;
                    state = StateId::Start_q9;
                    ch = getNextChar();
                } else if ((ch >= 'a') && (ch <= 'f')) {
                    text += ch;
                    state = StateId::Start_q9;
                    ch = getNextChar();
                } else {
                    ungetChar(ch);
                    return Token::Hex;
                }
                break;
        }
    }
}
const char* ConstLexer::toString(Token tk) {
    switch (tk) {
        case Token::Binary: return "Binary";
        case Token::Decimal: return "Decimal";
        case Token::Eof: return "Eof";
        case Token::Hex: return "Hex";
        case Token::Octal: return "Octal";
        default: return "Unknown";
    }
}