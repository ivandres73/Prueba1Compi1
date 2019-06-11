#ifndef _AST_H
#define _AST_H

#include <unordered_map>
#include <memory>
#include <string>

using std::unordered_map;
using std::move;
using std::string;

class Expr;
using ExprUPtr = std::unique_ptr<Expr>;

#define BIN_OP(name, oper) \
class name##Expr : public BinaryExpr { \
public: \
    name##Expr(ExprUPtr e1, ExprUPtr e2) : BinaryExpr(move(e1), move(e2)) {} \
    \
    int eval (unordered_map<std::string, int> map) { \
        return expr1->eval(map) oper expr2->eval(map); \
    } \
private: \
    unordered_map<std::string, int> map; \
};

class ASTNode {
public:
    
};

class Expr : public ASTNode {
public:
    virtual int eval(unordered_map<std::string, int> map) = 0;
};

class BinaryExpr : public Expr {
public:
    BinaryExpr(ExprUPtr e1, ExprUPtr e2) : expr1(move(e1)), expr2(move(e2)) { }
    ExprUPtr expr1;
    ExprUPtr expr2;
};

class AddExpr : public BinaryExpr {
public:
    AddExpr(ExprUPtr e1, ExprUPtr e2) : BinaryExpr(move(e1), move(e2)) {}

    int eval (unordered_map<std::string, int> map) {
        return expr1->eval(map) + expr2->eval(map);
    }
private:
    unordered_map<std::string, int> map;
};

BIN_OP(Sub, -);
BIN_OP(Mul, *);
BIN_OP(Div, /);
BIN_OP(Mod, %);

class NumExpr : public Expr
{
public:
    NumExpr(int num) : valor(num) {}

    int eval(unordered_map<std::string, int> map) {
        return valor;
    }

private:
    int valor;
};

class IdExpr : public Expr
{
public:
    IdExpr(string var) : iden(var) {}

    int eval(unordered_map<std::string, int> map) {
        return map[iden];
    }

private:
    string iden;
};

#endif
