#include <iostream>
#include <deque>
using namespace std;

char getChar();
bool getExp();
bool getVal();

bool getResult(deque<bool>& symbols, deque<char>& operators) {
    while (!operators.empty()) {
        bool sym2 = symbols.front();
        symbols.pop_front();
        bool sym1 = symbols.front();
        symbols.pop_front();
        switch (operators.front()) {
            case '|':
                symbols.push_front(sym1 || sym2);
                break;
            case '&':
                symbols.push_front(sym1 && sym2);
                break;
            default:
                clog << "error in getResult" << endl;
                break;
        }
        operators.pop_front();
    }
    return symbols.front();
}

char getChar() {
    if (!cin)
        return EOF;
    char result;
    while ((result = cin.get()) == ' ');
    return result;
}

bool getExp() {
    deque<bool> symbols;
    deque<char> operators;
    while (true) {
        symbols.push_back(getVal());
        char opr = getChar();
        switch (opr) {
            case '|':
            case '&':
                operators.push_back(opr);
                break;
            case ')':
            case '\n':
            case EOF:
                return getResult(symbols, operators);
            default:
                clog << "error in getExp()" << endl;
        }
    }
    return true;
}

bool getVal() {
    char c = getChar();
    switch (c) {
        case 'V':
        case 'F':
            return c == 'V';
        case '!':
            return !getVal();
        case '(':
            return getExp();
        default:
            clog << "error in getVal" << endl;
    }
    return true;
}

int main() {
    for (int expNum = 1; cin.peek() != EOF; expNum++) {
        printf("Expression %d: %c\n", expNum, getExp()?'V':'F');
    }
    return 0;
}