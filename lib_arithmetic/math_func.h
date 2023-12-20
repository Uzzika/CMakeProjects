// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef MATHFUNC_NATHFUNC_H_
#define MATHFUNC_MATHFUNC_H_

#define MATH_PI 3.1415

#include <iostream>

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
        throw std::invalid_argument("The value is invalid");
    }
    if (m_cos(x) == 0) {
        throw std::invalid_argument("Division by zero.");
    }
    return (m_sin(x) / m_cos(x));
}

double m_ctg(double x) {
    if (abs(x) >= MATH_PI) {
        throw std::invalid_argument("The value is invalid");
    }
    if (m_sin(x) == 0) {
        throw std::invalid_argument("Division by zero.");
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
int priority(char q){
    int p;
    switch (q) 
    {
    case '(':
        p = 0;
    case ')':
        p = 1;
    case '+':
    case '-':
        p = 5;
        break;
    case '*':
    case '/':
        p = 4;
        break;
    case '^':
        p = 2;
        break;
    default:
        break;
    }
    return p;
}

int poland(std::string expr) {
    Stack<std::string> stk(expr.size());
    std::string res, tmp;
    for (int i = 0; i < expr.length(); i++) {
        if (!isdigit(expr[i])) {
            if (stk.isEmpty()) {
                stk.push(expr[i]);
            }
        }
        else if ((priority(expr[i]) >= priority(stk.getTop()))) {
            if (expr[i] == ')') {
                while (stk.pop() != '(') {
                    res += stk.pop();
                }
                stk.pop();
            }
            else {
                while (!stk.isEmpty()) {
                    res += stk.pop();
                }
                stk.push(expr[i]);
            }
        }
        else {
            res += expr[i];
        }
    }
    while (!stk.isEmpty()) {
        res += stk.pop();
    }
    return 0;
}

#endif MATHFUNC_NATHFUNC_H_