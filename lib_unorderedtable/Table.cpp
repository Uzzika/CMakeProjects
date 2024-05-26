// Copyright 2024 Dudchenko Olesya

#include <iostream>
#include <string>
#include "../lib_unorderedtable/Table.h"
using namespace std;

int main() {
    UnorderedTable<int, string> unorderedTableArray;
    UnorderedTableOnList<int, string> unorderedTableList;
    OrderedTable<int, string> orderedTableArray;

    unorderedTableArray.insert(1, "One");
    unorderedTableArray.insert(2, "Two");
    unorderedTableArray.insert(3, "Three");

    unorderedTableList.insert(1, "One");
    unorderedTableList.insert(2, "Two");
    unorderedTableList.insert(3, "Three");

    orderedTableArray.insert(1, "One");
    orderedTableArray.insert(2, "Two");
    orderedTableArray.insert(3, "Three");

    string* val;
    val = unorderedTableArray.find(1);
    if (val) {
        cout << "UnorderedTableArray find 1: " << *val << "\n" << endl;
    }
    else {
        cout << "UnorderedTableArray find 1: Not found\n" << endl;
    }

    val = unorderedTableList.find(2);
    if (val) {
        cout << "UnorderedTableList find 2: " << *val << "\n" << endl;
    }
    else {
        cout << "UnorderedTableList find 2: Not found\n" << endl;
    }

    val = orderedTableArray.find(3);
    if (val) {
        cout << "OrderedTableArray find 3: " << *val << "\n" << endl;
    }
    else {
        cout << "OrderedTableArray find 3: Not found\n" << endl;
    }


    unorderedTableArray.replace(2, "Two updated");
    unorderedTableList.replace(3, "Three updated");
    orderedTableArray.replace(1, "One updated");

    val = unorderedTableArray.find(2);
    if (val) {
        cout << "UnorderedTableArray find 2 after replace: " << *val << "\n" << endl;
    }

    val = unorderedTableList.find(2);
    if (val) {
        cout << "UnorderedTableList find 2 after replace: " << *val << "\n" << endl;
    }

    val = orderedTableArray.find(1);
    if (val) {
        cout << "OrderedTableArray find 1 after replace: " << *val << "\n" << endl;
    }

    unorderedTableArray.remove(1);
    unorderedTableList.remove(2);
    orderedTableArray.remove(2);

    val = unorderedTableArray.find(1);
    if (val) {
        cout << "UnorderedTableArray find 1 after remove: " << *val << "\n" << endl;
    }
    else {
        cout << "UnorderedTableArray find 1 after remove: Not found\n" << endl;
    }

    val = unorderedTableList.find(2);
    if (val) {
        cout << "UnorderedTableList find 2 after remove: " << *val << "\n" << endl;
    }
    else {
        cout << "UnorderedTableList find 2 after remove: Not found\n" << endl;
    }

    val = orderedTableArray.find(2);
    if (val) {
        cout << "OrderedTableArray find 2 after remove: " << *val << "\n" << endl;
    }
    else {
        cout << "OrderedTableArray find 2 after remove: Not found\n" << endl;
    }

    system("pause");
    return 0;
}