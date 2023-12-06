// Copyright (c) Dudchenko Olesya Victorovna
#include "../lib_dsu/dsu.h"

void Island(DSU sets, int** arr, int M, int N) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (j != N - 1) {
                if (arr[i][j] == 1 && arr[i][j + 1] == 1) { sets.union_dsu((j + i * N) + 1, ((j + 1) + i * N) + 1); }
            }
            if (i != M - 1)
                if (arr[i][j] == 1 && arr[i + 1][j] == 1)
                    sets.union_dsu((j + i * N) + 1, (j + (i + 1) * N) + 1);
        }
    }
}

int CountOfIslands(DSU sets, int** arr, int M, int N) {
    int n = 0;
    for (int i = 1; i <= M * N; i++) {
        if (sets.getParent(i) == i) { n++; }
    }
    return n;
}


int main() {
    DSU sets1(12);
    int data1[3][4]{
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 1}
    };

    //
    DSU sets2(15);
    int data2[5][3]{
        {1, 0, 1},
        {1, 1, 0},
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 1}
    };
    Island(sets1, reinterpret_cast<int**>(data1), 3, 4);
    CountOfIslands(sets1, reinterpret_cast<int**>(data1), 3, 4);

    Island(sets2, reinterpret_cast<int**>(data2), 5, 3);
    CountOfIslands(sets2, reinterpret_cast<int**>(data2), 5, 3);
}