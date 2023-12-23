// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef LIB_ALGORIHMSH_ALGORIHMSH_H_
#define LIB_ALGORIHMSH_ALGORIHMSH_H_

#include <algorithm>
#include <exception>
#include <cstdlib>
#include <string>
#include <iostream>
#include <Windows.h>
#include "../lib_stack/stack.h"
#include "../lib_list/list.h"


void print_menu() {
    std::cout << "Меню:" << std::endl;
    std::cout << "\t1. Задать значение переменной." << std::endl;
    std::cout << "\t2. Увидеть обратную польскую запись." << std::endl;
    std::cout << "\t3. Вычислить значение функции." << std::endl;
    std::cout << "\t4. Вернуться к заданию выражения." << std::endl;
    std::cout << "\t5. Выход." << std::endl;
    std::cout << "Выбор: ";
}

struct variable {
    std::string name;
    double value;
};

class Parser {
    friend class Stack<std::string>;
    std::string expr;

public:
    Parser() { expr = "none"; }
    Parser(std::string _expr) : expr(_expr) {}
    Parser(const Parser& p) :expr(p.expr) {}

    std::string get_expr() const {
        return expr;
    }

    friend std::ostream& operator << (std::ostream& out, const Parser& p);
    friend std::istream& operator>>(std::istream& input, Parser& p);

    void DeleteSpaces() {
        expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    }

    bool CheckBracket() {
        Stack<std::string> stack(15);
        if (expr.size() == 0) {
            throw std::logic_error("String is empty!");
        }
        for (int i = 0; i < expr.size(); i++) {
            if (expr[i] == '(') {
                stack.push(std::to_string(expr[i]));
            }
            if (expr[i] == '{') {
                stack.push(std::to_string(expr[i]));
            }
            if (expr[i] == '[') {
                stack.push(std::to_string(expr[i]));
            }
            if (expr[i] == ')') {
                if (stack.getTop() == std::to_string('(')) {
                    stack.pop();
                }
                else {
                    return 0;
                }
            }
            if (expr[i] == ']') {
                if (stack.getTop() == std::to_string('[')) {
                    stack.pop();
                }
                else {
                    return 0;
                }
            }
            if (expr[i] == '}') {
                if (stack.getTop() == std::to_string('{')) {
                    stack.pop();
                }
                else {
                    return 0;
                }
            }
        }
        if ((stack.isEmpty() == true)) {
            return 1;
        }
        else {
            return 0;
        }
    }
    int CheckSyntax() {
        std::string nums = "0123456789";
        std::string lett = "qwertyuiopasdfghjklzxcvbnm";
        std::string lettnum = nums + lett;
        std::string arith = "+-/*^";
        std::string brackets = "()[]{}";
        std::string state2 = lettnum + brackets;
        int state = 0;
        int k = 0;
        char s;
        int i = 0;
        for (int i = 0; i < expr.length(); i++) {
            s = expr[i];
            switch (state) {
            case 0:
                if (i == expr.length() - 1) {
                    state = 2;
                }
                else if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
                    k = k + 1;
                    continue;
                }
                else if (lettnum.find(s) != std::string::npos) {
                    state = 1;
                    //while (lettnum.find(expr[i]) != std::string::npos) {
                    //    continue;
                    //}
                    continue;
                }
                else {
                    throw;
                }
            case 1:
                if (i == expr.length() - 1) {
                    state = 2;
                }
                else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
                    k = k - 1;
                    if (k >= 0) {
                        state = 1;
                        continue;
                    }
                    else {
                        throw;
                    }
                }
                else if (arith.find(expr[i]) != std::string::npos) {
                    state = 0;
                    continue;
                }
                else {
                    throw;
                }
            case 2:
                if (state2.find(expr[i]) != std::string::npos) {
                    if (k == 1) {
                        return 0;
                    }
                    else {
                        throw;
                    }
                }
                else {
                    throw;
                }
            }

        }
    }

    int CheckFunc() {
        std::string lett = "qwertyuiopasdfghjklzxcvbnm";
        std::string nums = "1234567890";
        std::string tmp = "";
        int num = 0;
        for (int i = 0; i < expr.length(); i++) {
            if (i == expr.length() && num > 1) {
                throw;
            }
            if (lett.find(expr[i]) != std::string::npos) {
                num++;
                tmp += expr[i];
            }
            else {
                if (num == 0) { continue; }
                if (num == 2) {
                    if (tmp != "ln" && tmp != "tg") {
                        throw;
                    }
                }
                if (num == 3) {
                    if (tmp != "sin" && tmp != "cos" && tmp != "ctg" && tmp != "exp") {
                        throw;
                    }
                }
                if (num > 3) {
                    throw;
                }
                num = 0;
                tmp = "";
            }
        }
        return 0;
    }
};

std::istream& operator>>(std::istream& input, Parser& p) {
    std::cout << "Enter the expression: ";
    getline(input, p.expr);
    return input;
}

std::ostream& operator<<(std::ostream& out, Parser& p) {
    out << "Your expression: " << p.get_expr() << std::endl;
    return out;
}

class Expression {
    friend class Parcer;
    std::string expression;
    std::string poland;
    variable vars[26];
    size_t count;
public:
    explicit Expression(Parser& p) {
        expression = p.get_expr();
        poland = "";
        count = 0;
        for (int i = 0; i < 26; i++) {
            vars[i].name = "x";
            vars[i].value = 0;
        }
    }

    void FindVars() {
        std::string letts = "qwertyuiopasdfghjklzxcvbnm";
        char c;
        int count = 0;
        variable var;
    }

};

#endif LIB_ALGORIHMSH_ALGORIHMSH_H_