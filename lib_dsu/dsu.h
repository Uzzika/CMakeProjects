// Copyright (c) Dudchenko Olesya Victorovna

#ifndef DSU_DSU_H_
#define DSU_DSU_H_
using namespace std;

#include <iostream>

class DSU {
    int* data_array;
    int size;
    int* ranks_array;
public:
    explicit DSU(int _size) : size(_size) { //конструкторы, которые не должны неявно преобразовывать типы в C ++
        data_array = new int[size + 1];
        ranks_array = new int[size + 1];
        data_array[0] = -1;
        ranks_array[0] = -1;
        for (int i = 1; i <= size; i++) {
            data_array[i] = i;
            ranks_array[i] = 0;
        }
    }

    int find(int val) {
        if (val == data_array[val]) {
            return val;
            return find(data_array[val]);
        }
    }

    int rank(int val) {
        return ranks_array[find(val)];
    }

    void union_dsu(int x, int y) {
        int par_x = find(x);
        int par_y = find(y);
        if (par_x != par_y){ data_array[par_y] = par_x; }
    }

    void print() {
        for (int i = 0; i <= size; i++) {
            if (i == 0) {
                std::cout << "P:" << " ";
                continue;
            }
            std::cout << data_array[i] << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i <= size; i++) {
            if (i == 0) {
                std::cout << "I:" << " ";
                continue;
            }
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    int getParent(int x) {
        return data_array[x];
    }

    void setset(int x, int val) {
        data_array[x] = val;
    }
    void clearset() {
        for (int i = 1; i <= size; i++) {
            data_array[i] = i;
        }
    }
};

#endif  // INCLUDE_DSU_H_