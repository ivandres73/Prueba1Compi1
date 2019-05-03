#ifndef _EXPR_PARSER_H
#define _EXPR_PARSER_H

#include "lexer.h"

using namespace std;


class Parser {
public:
	void parse();
    Parser(Lexer&, std::ostringstream&);
    std::ostringstream& out;

private:
    template<typename T>
    bool tokenIs(T tk) {
        return (currToken == tk);
    }

    template<typename T, typename... TArgs>
    bool tokenIs(T firstTk, TArgs... moreTk) {
        return (currToken == firstTk) || tokenIs(moreTk...);
    }

    Token currToken;
    Lexer& lex;
    
    void input();
    void opt_eol();
    void stmt_list();
    void stmt_list_p();
    void stmt();
    void expr();
    void expr_p();
    void term();
    void term_p();
    void factor();
};

#endif
