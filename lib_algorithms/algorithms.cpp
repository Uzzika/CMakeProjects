// Copyright 2023 Dudchenko Olesya

#include <iostream>
#include <Windows.h>

#include "../lib_algorithms/algorithms.h"


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Parser exp;
    std::cin >> exp;
    system("cls");
    exp.DeleteSpaces();
    std::cout << exp;
    if (exp.CheckBracket() == 1) {
        std::cout << "The sequence of brackets is correct\n";
    }
    else {
        std::cout << "The sequence of brackets is incorrect\n";
    }
    system("pause");
    return 0;
}