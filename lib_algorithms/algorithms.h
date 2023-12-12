// Copyright 2023 Dudchenko Olesya

#ifndef ALGORIHMSH_ALGORIHMSH_H_
#define ALGORIHMSH_ALGORIHMSH_H_

#include <algorithm>
#include <exception>
#include <cstdlib>
#include <string>
#include <iostream>
#include <Windows.h>
#include "../lib_stack/stack.h"


void print_menu() {
    //std::cout << "Ваше выражение: " << expr << std::endl;
    std::cout << "Меню:" << std::endl;
    std::cout << "  1. Задать значение переменной." << std::endl;
    std::cout << "  2. Увидеть обратную польскую запись." << std::endl;
    std::cout << "  3. Вычислить значение функции." << std::endl;
    std::cout << "  4. Вернуться к заданию выражения." << std::endl;
    std::cout << "  5. Выход." << std::endl;
    std::cout << "Выбор: ";
}

class Parser {
    friend class Stack<std::string>;
    std::string expr;
public:
    Parser() {
        expr = "none";
    }
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
            if (expr[i] != '{' || expr[i] != '}' || expr[i] != '(' || 
                expr[i] != ')' || expr[i] != '[' || expr[i] != ']') {
                throw std::logic_error("The entered element is not a bracket!");
            }

        }
        if (stack.isEmpty() == true) {
            return 1;
        }
        else {
            if (stack.getTop() == std::to_string('[') || stack.getTop() == std::to_string('{') || 
            stack.getTop() == std::to_string('(') || stack.getTop() == std::to_string('}') || 
            stack.getTop() == std::to_string('}') || stack.getTop() == std::to_string(']')) {
                throw std::logic_error("Stack is not empty!");
                return 0;
            }
        }
    }

};

std::istream& operator>>(std::istream& input, Parser& p) {
    std::cout << "Enter the expression: ";
    getline(input, p.expr);
    return input;
}

std::ostream& operator<<(std::ostream& out, Parser& p) {
    out << "Your expression without spases: " << p.get_expr() << std::endl;
    return out;
}


#endif ALGORIHMSH_ALGORIHMSH_H_