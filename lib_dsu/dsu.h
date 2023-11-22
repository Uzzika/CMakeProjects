// Copyright (c) Dudchenko Olesya Victorovna

#ifndef INCLUDE_DSU_H_
#define INCLUDE_DSU_H_
using namespace std;

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

        //дописать
    }
};

#endif  // INCLUDE_DSU_H_