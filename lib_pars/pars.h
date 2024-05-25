#pragma once
#include <string>
#include <map>
#include <math.h>
#include "../lib_list/list.h"
#include "../lib_stack/stack.h"
#include "../lib_queue/TQueue.h"
using namespace std;

enum LexemTypes {
    Operator, Number, OpenBracket, CloseBracket, Factorial, Func, Varieble
};

bool isLetter(char elem) {
    return elem <= 'Z' && elem >= 'A' ||
        elem <= 'z' && elem >= 'a';
}

bool isNumber(char elem) {
    return elem <= '9' &&
        elem >= '0';
}

bool isOpenBracket(char elem) {
    return elem == '{' || elem == '(' || elem == '[';
}

bool isCloseBracket(char elem) {
    return elem == '}' || elem == ')' || elem == ']';
}

bool CorrectBrackets(string input) {
    StackOnList<char> st;
    for (auto elem : input) {
        if (!isOpenBracket(elem) && !isCloseBracket(elem))
        if (isOpenBracket(elem)) {
            st.push(elem);
        }
        else if (!st.empty() && ((elem == ')' && st.top() == '(') || (elem == '}' && st.top() == '{')
            || (elem == ']' && st.top() == '['))) {
            st.pop();
        }
        else {
            return false;
        }
    }
    return st.empty();
}

void deletespace(string& st) {
    while (st.find(' ') != string::npos) {
        st.erase(st.find(' '), 1);
    }
}

void toUnarMinus(string& st) {
    if (st[0] == '-') { st[0] = '~'; }
    while (st.find("(-") != string::npos){
        st[st.find("(-") + 1] = '~';
    }
    while (st.find("^-") != string::npos) {
        st[st.find("^-") + 1] = '~';
    }
}

float getNumberFloat(string& st, int& pos) {
    string tmp;
    while (pos < st.length() && (isNumber(st[pos]) ||
        (st[pos] == '.' && tmp.find('.') == string::npos))) {
        tmp += st[pos];
        pos++;
    }
    if (pos + 1 < st.length() && st[pos + 1] == '.') { throw logic_error("wrong number"); }
    pos--;
    return stof(tmp);
}

string getNumberString(string& st, int& pos) {
    string tmp;
    while (pos < st.length() &&
        (isNumber(st[pos]) ||
            (st[pos] == '.' &&
                tmp.find('.') == string::npos))) {
        tmp += st[pos];
        pos++;
    }
    if (pos < st.length() && st[pos] == '.') { throw logic_error("wrong error"); }
    pos--;
    return tmp;
}

void replaceConstant(string& input) {
    while (input.find('e') != string::npos) {
        input.replace(input.find('e'), 1, "2.718");
    }
    while (input.find("pi") != string::npos) {
        input.replace(input.find("pi"), 2, "3.142");
    }
}

class Lexem {
    LexemTypes _type;
    float _value;
    string _name;
public:
    Lexem() : _type(Number), _value(0), _name("0") {};
    Lexem(string& input, int& pos) {
        if (pos >= input.length()) { throw logic_error("wrong start"); }
        if (isNumber(input[pos])) {
        _type = Number;
        int tmppos = pos;
        _value = getNumberFloat(input, tmppos);
        _name = getNumberString(input, pos);
        return;
        }
        else if (isOpenBracket(input[pos])) {
            _type = OpenBracket;
            _value = 0;
            _name = input[pos];
            return;
        }
        else if (isCloseBracket(input[pos])) {
            _type = CloseBracket;
            _value = 0;
            _name = input[pos];
            return;
        }
        else if (input[pos] == '+' || input[pos] == '-') {
            _type = Operator;
            _name = input[pos];
            _value = 1;
            return;
        }
        else if (input[pos] == '*' || input[pos] == '/') {
            _type = Operator;
            _name = input[pos];
            _value = 2;
            return;
        }
        else if (input[pos] == '^') {
            _type = Operator;
            _name = input[pos];
            _value = 3;
            return;
        }
        else if (input[pos] == '~') {
            _type = Operator;
            _name = input[pos];
            _value = 4;
            return;
        }
        else if (input[pos] == '!') {
            _type = Factorial;
            _name = input[pos];
            _value = 4;
            if (input.substr(pos, 2) == "!!") {
                _name = "!!";
            }
            return;
        }
        string tmpstr = input.substr(pos, 2);
        if (tmpstr == "tg" || tmpstr == "ln" || tmpstr == "sh" || tmpstr == "ch" || tmpstr == "th") {
            _type = Func;
            _name = tmpstr;
            _value = 4;
            pos++;
            return;
        }
        else {
            tmpstr = input.substr(pos, 3);
        }
        if (tmpstr == "cos" || tmpstr == "sin" || tmpstr == "sqr" || tmpstr == "ctg" || tmpstr == "cth") {
            _type = Func;
            _name = tmpstr;
            _value = 4;
            pos += 2;
            return;
        }
        else {
            tmpstr = input.substr(pos, 4);
        }
        if(tmpstr == "sqrt") {
            _type = Func;
            _name = tmpstr;
            _value = 4;
            pos += 3;
            return;
        }
        else {
            tmpstr = input.substr(pos, 5);
        }
        if (tmpstr == "arctg" || tmpstr == "arcth" || tmpstr == "arcsh" || tmpstr == "arcsh") {
            _type = Func;
            _name = tmpstr;
            _value = 4;
            pos += 4;
            return;
        }
        else {
            tmpstr = input.substr(pos, 6);
        }
        if (tmpstr == "arccos" || tmpstr == "arcsin" || tmpstr == "arcctg" || tmpstr == "arccth") {
            _type = Func;
            _name = tmpstr;
            _value = 4;
            pos += 5;
            return;
        }
        else if (isLetter(input[pos])) {
            _type = Varieble;
            _name = input[pos];
            _value = 0;
            pos++;
            if (pos < input.length() || isNumber(input[pos])) {
                _name = _name + getNumberString(input, pos);
            }
            return;
        }
        throw logic_error("not lexem");
    }
    Lexem(float x) {
        _type = Number;
        _name = x;
        _value = x;
    }
    Lexem(const Lexem& lex) {
        _type = lex._type;
        _value = lex._value;
        _name = lex._name;
    };
    Lexem& operator=(const Lexem& l) {
        _type = l._type;
        _value = l._value;
        _name = l._name;
        return *this;
    }
    bool operator==(const Lexem l) const {
        return _type == l._type && _value == l._value && _name == l._name;
    }
    bool operator!=(const Lexem l) const {
        return !(*this == l);
    }
    LexemTypes type() { return _type; }
    std::string name() { return _name; }
    void val(float x) { _value = x; }
    float val() { return _value; }
};

TList<Lexem> GetLexems(std::string& input) {
    if (!CorrectBrackets(input)) { throw std::logic_error("wrong brackets"); }
    deletespace(input);
    toUnarMinus(input);
    replaceConstant(input);
    TList<Lexem> res;
    for (int i = 0; i < input.length(); i++) {
        res.push_back(Lexem(input, i));
    }
    return res;
}