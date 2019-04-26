#include "lexer.h"
#include <iostream>
#include <string.h>
#include <sstream>

using std::istringstream;
using std::string;
using std::cout;
using std::endl;

class ConstLexer {

    private:
        istringstream& in;
        int line;
        string text;
        char getNextChar() {
            char c = static_cast<char>(in.get());

            if (c == '/n') line++;

            return c;
        }

        void ungetChar(char ch) {
            if (ch == '/n') line--;
            in.unget();
        }
    public:
        ConstLexer(istringstream& in) : in(in), line(1) { }
        /*ConstLexer(istringstream& iss) { 
           // this->in = iss;
            in.str(iss)
        }*/
        const char* toString(Token tk);
        Token getNextToken();
        string getText() { return text; }
        void reportError(char ch) {
            cout << "error at line " << line << " with " << ch << endl;
        }
};

