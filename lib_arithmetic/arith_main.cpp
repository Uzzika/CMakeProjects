// Copyright (c) 2023 Dudchenko Olesya Victorovna 

#include <iostream>
#include <Windows.h>

#include "../lib_arithmetic/arithmetic.h"
#include "../lib_arithmetic/math_func.h"
#include "../lib_algorithms/algorithms.h"


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int x = 0;

    Parser p;
    std::cin >> p;
    p.DeleteSpaces();
    p.CheckSyntax();
    p.CheckFunc();

    if (p.CheckSyntax() == 0) {
        std::cout << "Syntax is right\n" << std::endl;
    }
    if (p.CheckFunc() == 0) {
        std::cout << "Func is right\n" << std::endl;
    }
    system("pause");
    return 0;
}



