#include <vector>
#include "expr_parser.h"

struct Rule {
    Symbol lhs;
    std::vector<Symbol> rhs;
    bool isEmpty() const { return rhs.empty(); }
};

Rule rule0{Symbol::SPrime, {Symbol::S}};
Rule rule1{Symbol::S, {Symbol::OpenBrace, Symbol::L, Symbol::CloseBrace}};
Rule rule2{Symbol::L, {Symbol::L, Symbol::Comma, Symbol::Id}};
Rule rule3{Symbol::L, {Symbol::Id}};
Rule none;

enum ActionType { Accept, Shift, Reduce, Empty };
struct Action {
    Action(): 
        type(ActionType::Empty),
        state(-1),
        rule(none) {}

    Action(ActionType type):
        type(type),
        state(-1),
        rule(none) {}
    
    Action(unsigned state):
        type(ActionType::Shift),
        state(state),
        rule(none) {}
    
    Action(Rule& rule):
        type(ActionType::Reduce),
        state(-1),
        rule(rule) {}

    ActionType type;
    int state;
    Rule& rule;
};

Action empty;
Action s1(1);
Action s3(3);
Action s5(5);
Action s6(6);
Action s7(7);
Action r0(rule0); // Reduce rule 0: S' -> S
Action r1(rule1); // Reduce rule 1: S -> { L }
Action r2(rule2); // Reduce rule 2: L -> L , id
Action r3(rule3); // Reduce rule 3: L -> id
Action accept(ActionType::Accept);

/* { } , Id $ */
std::vector<std::vector<Action>> lr0_action = {
    /* State 0 */{ s1, empty, empty, empty, empty },
    /* State 1 */{ empty, empty, empty, s3, empty },
    /* State 2 */{ empty, empty, empty, empty, accept },
    /* State 3 */{ r3, r3, r3, r3, r3 },
    /* State 4 */{ empty, s6, s5, empty, empty },
    /* State 5 */{ empty, empty, empty, s7, empty },
    /* State 6 */{ r1, r1, r1, r1, r1 },
    /* State 7 */{ r2, r2, r2, r2, r2 }
};

/* SPrime S L */
std::vector<std::vector<int>> lr0_goto = {
    /* State 0 */{ -1, 2, -1 }, 
    /* State 1 */{ -1, -1, 4 },
    /* State 2 */{ -1, -1, -1 },
    /* State 3 */{ -1, -1, -1 },
    /* State 4 */{ -1, -1, -1 },
    /* State 5 */{ -1, -1, -1 },
    /* State 6 */{ -1, -1, -1 },
    /* State 7 */{ -1, -1, -1 }
};

struct lr0_data
{
    Symbol simbol;
    int state;

    lr0_data(Symbol s) : simbol(s), state(-1) { }
    lr0_data(int i) : state (i) { }

    bool isSymbol() { return state == -1; }
};


int Parser::parse(int count[4]) {

    std::list<lr0_data> stack;
    Symbol tk = lexer.getNextToken();

    lr0_data primerNum(0);
    lr0_data primerSim(Symbol::S);

    stack.push_front(primerNum);
    stack.push_front(primerSim);
    
    while (true) {
        lr0_data actual = stack.front();

        if (actual.isSymbol()) {
            int temp = indexOf(actual.simbol);
            lr0_data nuevo(lr0_goto[1][temp]);
            stack.push_front(nuevo);
        } else if (actual.state != -1) {
            Action temp = lr0_action[actual.state][indexOf(tk)];
            if (temp.type == ActionType::Shift) {
                lr0_data nuevo(tk);
                stack.push_front(nuevo);
                lr0_data nuevo1(temp.state);
                stack.push_front(nuevo1);
                tk = lexer.getNextToken();
            } else if (temp.type == ActionType::Reduce) {
                int cant = temp.rule.rhs.size();
                for (int i=0; i < cant; i++)
                    stack.pop_front();
                lr0_data nuevo(temp.rule.lhs);
                stack.push_front(nuevo);
                lr0_data nuevo1(temp.state);
                stack.push_front(nuevo1);
                if (temp.rule.lhs == rule0.lhs)
                    count[0]++;
                else if (temp.rule.lhs == rule1.lhs)
                    count[1]++;
                else if (temp.rule.lhs == rule2.lhs)
                    count[2]++;
                else
                    count[3]++;
            } else if (temp.type == ActionType::Accept) {
                break;
            } else if (temp.type == ActionType::Empty)
                throw "error";
        } else
            throw "error";
        
    }

    return 0;
}
