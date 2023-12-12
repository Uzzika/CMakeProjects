// Copyright 2023 (c) Dudchenko Olesya Victorovna

#include <iostream>
#include "../lib_dsu/dsu.h"
#include <time.h>

#define ISLAND_

#ifdef MAZE_
void main() {
    srand(time(NULL));
    unionmaze maze(10, 10);
    maze.maze_generator();
    maze.printmaze();
    std::cout << std::endl;
    maze.printmaze(true);
}
#endif // !

#ifdef ISLAND_
void main() {
    int test_arr1[3][4] = { {1,1,0,0},
                            {1,0,0,0},
                            {0,0,1,0} };

    int test_arr2[5][5] = { {0,0,0,0,0},
                            {0,0,0,0,0},
                            {0,0,0,0,0},
                            {0,0,0,0,0},
                            {0,0,0,0,0} };

    int test_arr3[5][6] = { {1,1,1,1,1,1},
                            {1,1,1,1,1,1},
                            {1,1,1,1,1,1},
                            {1,1,1,1,1,1},
                            {1,1,1,1,1,1} };
    int test_arr4[5][5] = { {1,1,0,0,0},
                            {1,0,0,1,1},
                            {0,0,1,1,0},
                            {0,1,0,0,0},
                            {1,1,0,0,1} };

    int test_arr5[5][5] = { {1,1,1,1,1},
                            {1,1,1,1,1},
                            {1,1,1,1,1},
                            {1,1,1,1,1},
                            {1,1,1,1,1} };

    ///
    islands test1(3, 4, reinterpret_cast<int*>(test_arr1));
    islands test2(5, 5, reinterpret_cast<int*>(test_arr2));
    islands test3(5, 6, reinterpret_cast<int*>(test_arr3));
    islands test4(5, 5, reinterpret_cast<int*>(test_arr3));
    islands test5(5, 5, reinterpret_cast<int*>(test_arr3));

    test1.constructIslands();
    test1.tozeroset();
    test1.cntislands();
    std::cout << "test 1: " << test1.getcnt() << std::endl;
    test2.constructIslands();
    test2.tozeroset();
    test2.cntislands();
    std::cout << "test 2: " << test2.getcnt() << std::endl;
    test3.constructIslands();
    test3.tozeroset();
    test3.cntislands();
    std::cout << "test 3: " << test3.getcnt() << std::endl;
    test4.constructIslands();
    test4.tozeroset();
    test4.cntislands();
    std::cout << "test 4: " << test4.getcnt() << std::endl;
    test5.constructIslands();
    test5.tozeroset();
    test5.cntislands();
    std::cout << "test 5: " << test5.getcnt() << std::endl;

    system("pause");
}
#endif // !