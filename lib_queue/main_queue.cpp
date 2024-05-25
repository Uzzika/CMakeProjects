// Copyright 2024 Dudchenko Olesya

#include <iostream>
#include "../lib_queue/TQueue.h"

int main() {
    TQueue<int> q(5);

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    while (!q.isEmpty()) {
        std::cout << q.pop() << " ";
    }

    std::cout << std::endl;

    return 0;
}
