// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef BINTREE_BINTREE_H_
#define BINTREE_BINTREE_H_

#include <iostream>
#include "../lib_queue/TQueue.h"
#include "../lib_stack/stack.h"

struct Node {
    int data;
    Node *left, *right;
    //конструктор, который инициализирует узел заданным значением и устанавливает дочерние узлы в nullptr
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

//функция для создания узла с указанными значением и дочерними узлами
Node* create(int value, Node* l = nullptr, Node* r = nullptr) {
    Node* node = new Node(value);
    node->left = l;
    node->right = r;
    return node;
}

class BinaryTree {
    Node* root;

 public:
    BinaryTree() : root(nullptr) {}

    void insert(int value){
        Node* newNode = new Node(value);
        if (!root) {
            root = newNode;
            return;
        }

        TQueue <Node*> q;//создаётся очередь q, содержащая указатели на узлы дерева
        q.push(root);

        while (!q.isEmpty()) {
            Node* current = q.front();
            q.pop();

            //Проверяется, есть ли у текущего узла левый потомок. Если нет, 
            //новый узел становится его левым потомком, и функция завершается
            if (!current->left) {
                current->left = newNode;
                return;
            }
            else {
                q.push(current->left);
            }

            if (!current->right) {
                current->right = newNode;
                return;
            }
            else {
                q.push(current->right);
            }
        }
    };

    Node* find(int value) {
        TQueue<Node*> q;
        q.push(root);

        while (!q.isEmpty()) {
            Node* current = q.pop();
            if (current->data == value) return current;
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        return nullptr;
    }

    void remove(Node* node) {
        if (root == nullptr || node == nullptr) return;

        if (root == node && root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
            return;
        }

        Node* deepest = nullptr;
        Node* parentOfDeepest = nullptr;
        Node* target = nullptr;
        Node* parentOfTarget = nullptr;

        TQueue<Node*> q;
        q.push(root);

        while (!q.isEmpty()) {
            Node* temp = q.front();
            q.pop();

            if (temp == node) {
                target = temp;
            }

            if (temp->left) {
                parentOfDeepest = temp;
                q.push(temp->left);
            }

            if (temp->right) {
                parentOfDeepest = temp;
                q.push(temp->right);
            }

            if (!q.isEmpty()) {
                deepest = temp;
            }
        }

        if (target) {
            target->data = deepest->data;

            if (parentOfDeepest->left == deepest) {
                parentOfDeepest->left = nullptr;
            }
            else {
                parentOfDeepest->right = nullptr;
            }

            delete deepest;
        }
    }

public:
    void BFS(void(*func) (Node*)) { // сложность по времени O(n), сложность по памяти O(2^n)
        if (root == nullptr) return;
        TQueue <Node*> q;
        q.push(root); //первый элемент
        while (!q.isEmpty()) {
            Node* cur = q.front();
            q.pop();
            if (cur) {
                if (cur->left != nullptr) { q.push(cur->left); }
                if (cur->right != nullptr) { q.push(cur->right); }
                func(cur);
            }
        }
    }

    void dfsInOrder(void(*func)(Node*)) {
        dfsInOrderRec(root, func);
    }

    void dfsPreOrder(void(*func)(Node*)) {
        dfsPreOrderRec(root, func);
    }

    void dfsPostOrder(void(*func)(Node*)) {
        dfsPostOrderRec(root, func);
    }

private:
    Node* removeNode(Node* root, Node* node) {
        if (root == nullptr) return root;

        if (node->data < root->data) {
            root->left = removeNode(root->left, node);
        }
        else if (node->data > root->data) {
            root->right = removeNode(root->right, node);
        }
        else {
            // Узел найден
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = removeNode(root->right, temp);
        }
        return root;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    // Рекурсивные функции для обходов DFS
    void dfsInOrderRec(Node* node, void(*func)(Node*)) { // сложность по времени O(n), сложность по памяти O(h) - длина дерева
        if (node == nullptr) return;
        dfsInOrderRec(node->left, func);
        func(node);
        dfsInOrderRec(node->right, func);
    }

    void dfsPreOrderRec(Node* node, void(*func)(Node*)) {
        if (node == nullptr) return;
        func(node);
        dfsPreOrderRec(node->left, func);
        dfsPreOrderRec(node->right, func);
    }

    void dfsPostOrderRec(Node* node, void(*func)(Node*)) {
        if (node == nullptr) return;
        dfsPostOrderRec(node->left, func);
        dfsPostOrderRec(node->right, func);
        func(node);
    }
};

void printNode(Node* node) {
    if (node) {
        std::cout << node->data << " ";
    }
}

#endif // BINTREE_BINTREE_H_