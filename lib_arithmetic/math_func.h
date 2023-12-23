// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef MATHFUNC_MATHFUNC_H_
#define MATHFUNC_MATHFUNC_H_

#define MATH_PI 3.1415

#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include "../lib_stack/stack.h"
using namespace std;

int factorial(double x) {
    int res = 1;
    for (int i = 1; i <= x; i++) { res *= i; }
    return res;
}

double m_sin(double x) {
    double result = x;
    for (int n = 1; n <= 10; n++) {
        double term = (double)pow(x, 1 + 2 * n) / factorial(1 + 2 * n);
        if (n % 2 == 1) {
            result -= term;
        }
        else {
            result += term;
        }
    }
    return result;
}

double m_cos(double x) {
    double res = x;
    for (int n = 1; n <= 10; n++) {
        double tmp = (double)pow(x, 2 * n - 1) / factorial(2 * n - 1);
        if (n % 2 == 1) {
            res += tmp;
        }
        else {
            res -= tmp;
        }
    }
    return res;
}

double m_tg(double x) {
    if (abs(x) >= (MATH_PI / 2)) {
        throw invalid_argument("The value is invalid");
    }
    if (m_cos(x) == 0) {
        throw invalid_argument("Division by zero.");
    }
    return (m_sin(x) / m_cos(x));
}

double m_ctg(double x) {
    if (abs(x) >= MATH_PI) {
        throw invalid_argument("The value is invalid");
    }
    if (m_sin(x) == 0) {
        throw invalid_argument("Division by zero.");
    }
    return (m_cos(x) / m_sin(x));
}

double m_exp(double x) {
    double res = 0;
    for (int n = 0; n <= 10; n++) {
        res += pow(x, n) / factorial(n);
    }
    return res;
}

double m_ln(double x) {
    double res = 0;
    for (int n = 0; n <= 10; n++) {
        res += (pow(-1, n) * pow(x - 1, n + 1)) / (n + 1);
    }
    return res;
}

class TArithmeticExpression {
    string infix;
    string postfix;
    vector<char> lexems;
    map<char, double> operands;
    map<char, int> priority;
public:
    TArithmeticExpression(string infx) : infix(infx)
    {
        priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
        ToPostfix();
    }
    void Parse() {
        for (char c : infix)
            lexems.push_back(c);
    }
    vector<char> GetOperands() const {
        vector<char> op;
        for (const auto& item : operands)
            op.push_back(item.first);
        return op;
    }
    void ToPostfix() {
        Parse();
        TDynamicStack<char> st;
        char stackItem;
        for (char item : lexems) {
            switch (item) {
            case '(':
                st.Push(item);
                break;
            case ')':
                stackItem = st.Pop();
                while (stackItem != '(') {
                    postfix += stackItem;
                    stackItem = st.Pop();
                }
                break;
            case '+': case '-': case '*': case '/':
                while (!st.IsEmpty()) {
                    stackItem = st.Pop();
                    if (priority[item] <= priority[stackItem])
                        postfix += stackItem;
                    else {
                        st.Push(stackItem);
                        break;
                    }
                }
                st.Push(item);
                break;
            default:
                operands.insert({ item, 0.0 });
                postfix += item;
            } // switch
        } // for
        while (!st.IsEmpty()) {
            stackItem = st.Pop();
            postfix += stackItem;
        }
    }
    double Calculate(const map<char, double>& values) {
        for (auto& val : values) { 
            try {
                operands.at(val.first) = val.second;
            }
            catch (out_of_range& e) {}
        }
        TDynamicStack<double> st;
        double leftOperand, rightOperand;
        for (char lexem : postfix)
        {
            switch (lexem)
            {
            case '+':
                rightOperand = st.Pop();
                leftOperand = st.Pop();
                st.Push(leftOperand + rightOperand);
                break;
            case '-':
                rightOperand = st.Pop();
                leftOperand = st.Pop();
                st.Push(leftOperand - rightOperand);
                break;
            case '*':
                rightOperand = st.Pop();
                leftOperand = st.Pop();
                st.Push(leftOperand * rightOperand);
                break;
            case '/':
                rightOperand = st.Pop();
                leftOperand = st.Pop();
                st.Push(leftOperand / rightOperand);
                break;
            default:
                st.Push(operands[lexem]);
            }
        }
        return st.Pop();
    }
};

#endif MATHFUNC_NATHFUNC_H_