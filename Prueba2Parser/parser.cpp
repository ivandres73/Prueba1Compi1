#include "parser.h"
#include "error.h"

Parser::Parser(Lexer& lex, std::ostringstream& oss) : lex(lex), out(oss)
{ 

}

void Parser::parse() {
    input();
    //out.write(";", 1);
    if (tokenIs(Token::Eof)) {
        cerr << "error at parsing";
    }
    
}

void Parser::input() {
    currToken = lex.getNextToken();
    stmt_list();
    out.write(";", 1);
    opt_eol();
    
}

void Parser::opt_eol() {
    if (tokenIs(Token::Eol)) {
        currToken = lex.getNextToken();
    }
    else { /*eps*/ }
}

void Parser::stmt_list() {
    stmt();
    stmt_list_p();
}

void Parser::stmt_list_p() {
    if (tokenIs(Token::Eol)) {
        currToken = lex.getNextToken();
        stmt();
        stmt_list_p();
    }
    else { /* eps*/ }
}

void Parser::stmt() {
    if (tokenIs(Token::Ident)) {
        currToken = lex.getNextToken();
        out.write("identifier", 10);
        if (tokenIs(Token::OpAssign)) {
            out.write("=", 1);
            currToken = lex.getNextToken();
            expr();
        }
        else {
            cerr << "assign expected";
        }
    } else if (tokenIs(Token::KwPrint)) {
        out.write("print", 5);
        out.write("(", 1);
        currToken = lex.getNextToken();
        expr();
        out.write(")", 1);
    }
}

void Parser::expr() {
    term();
    expr_p();
}

void Parser::expr_p() {
    if (tokenIs(Token::OpAdd)) {
        out.write("+", 1);
        currToken = lex.getNextToken();
        term();
        expr_p();
    } else if (tokenIs(Token::OpSub)) {
        out.write("-", 1);
        currToken = lex.getNextToken();
        term();
        expr_p();
    } else { /*eps*/ }
}

void Parser::term() {
    factor();
    term_p();
}

void Parser::term_p() {
    if (tokenIs(Token::OpMul)) {
        out.write("*", 1);
        currToken = lex.getNextToken();
        factor();
        term_p();
    } else if (tokenIs(Token::OpDiv)) {
        out.write("/", 1);
        currToken = lex.getNextToken();
        factor();
        term_p();
    } else { /*eps*/ }
}

void Parser::factor() {
    if (tokenIs(Token::Ident)) {
        out.write("identifier", 10);
        currToken = lex.getNextToken();
    } else if (tokenIs(Token::Number)) {
        out.write("number", 6);
        currToken = lex.getNextToken();
    } else if (tokenIs(Token::OpenPar)) {
        out.write("(", 1);
        currToken = lex.getNextToken();
        expr();
        if (tokenIs(Token::ClosePar)) {
            out.write(")", 1);
            currToken = lex.getNextToken();
        }
        else {
            cerr << "close parens expected";
        }
    } else {
        cerr << "expected an identifier or a number";
    }

}