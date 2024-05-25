// Copyright 2024 Dudchenko Olesya

#include "../lib_trees/rbtree.h"

int main() {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    TNode<int>* node = tree.find(20);
    if (node != nullptr) {
        std::cout << "Found: " << node->data << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    tree.remove(20);
    node = tree.find(20);
    if (node != nullptr) {
        std::cout << "Found: " << node->data << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }

    // Additional testing and tree traversal code can be added here

    return 0;
}