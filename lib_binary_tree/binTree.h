// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef BINTREE_BINTREE_H_
#define BINTREE_BINTREE_H_

#include <iostream>
#include "../lib_queue/TQueue.h"
#include "../lib_stack/stack.h"
#include <vector>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    //�����������, ������� �������������� ���� �������� ��������� � ������������� �������� ���� � nullptr
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

//������� ��� �������� ���� � ���������� ��������� � ��������� ������
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

        TQueue <Node*> q;//�������� ������� q, ���������� ��������� �� ���� ������
        q.push(root);

        while (!q.isEmpty()) {
            Node* current = q.front();
            q.pop();

            //�����������, ���� �� � �������� ���� ����� �������. ���� ���, 
            //����� ���� ���������� ��� ����� ��������, � ������� �����������
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

        Node* curParent = nullptr;
        Node* cur = root;

        // ������� �������� ���� ��� ��������
        while (cur != nullptr && cur != node) {
            curParent = cur;
            if (node->data < cur->data)
                cur = cur->left;
            else
                cur = cur->right;
        }

        if (cur == nullptr) return; // ���� ��� �������� �� ������

        // ���� � ���� ��� �������� ���� ��� �������� ����
        if (cur->left != nullptr && cur->right != nullptr) {
            Node* parent = cur;
            Node* swap_tmp = cur->right; // ���� ����� ����� ���� � ������ ���������
            while (swap_tmp->left != nullptr) {
                parent = swap_tmp;
                swap_tmp = swap_tmp->left;
            }

            // �������� ������ �� swap_tmp � cur
            cur->data = swap_tmp->data;
            cur = swap_tmp;
            curParent = parent;
        }

        // � ���� ��� �������� ���� ������ ���� ��� �� ������ ��������� ����
        Node* child = (cur->left != nullptr) ? cur->left : cur->right;

        // ���� � ���� ��� �������� ���� ������ ���� �������� ���� ��� � ���� ��� ������ ���
        if (curParent == nullptr) {
            root = child;
        }
        else if (curParent->left == cur) {
            curParent->left = child;
        }
        else {
            curParent->right = child;
        }

        delete cur;
    }

    Node* getRoot() const {
        return root;
    }

    void printTreeByLevels(Node* root) {
        if (!root) return;

        TQueue<Node*> q;
        q.push(root);

        while (!q.isEmpty()) {
            int levelSize = q.getSize(); // ���������� ����� �� ������� ������
            std::vector<int> levelNodes;

            // ��������� ���� ����� �������� ������
            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = q.front();
                q.pop();
                levelNodes.push_back(currentNode->data);

                // ���������� �������� ����� � �������
                if (currentNode->left) {
                    q.push(currentNode->left);
                }
                if (currentNode->right) {
                    q.push(currentNode->right);
                }
            }

            // ������ ����� �������� ������
            for (int val : levelNodes) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

public:
    void BFS(void(*func) (Node*)) { // ��������� �� ������� O(n), ��������� �� ������ O(2^n)
        if (root == nullptr) return;
        TQueue <Node*> q;
        q.push(root); //������ �������
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

    int height() {
        return heightRec(root);
    }
    
    int getLevel(Node* node) {
        return getLevelRec(root, node, 1);
    }

    int size() {
        return sizeRec(root);
    }

private:
    // ����������� ������� ��� ������� DFS
    void dfsInOrderRec(Node* node, void(*func)(Node*)) { // ��������� �� ������� O(n), ��������� �� ������ O(h) - ����� ������
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

    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int getLevelRec(Node* current, Node* target, int level) {
        if (current == nullptr) {
            return 0;
        }
        if (current == target) {
            return level;
        }
        int downLevel = getLevelRec(current->left, target, level + 1);
        if (downLevel != 0) {
            return downLevel;
        }
        return getLevelRec(current->right, target, level + 1);
    }

    int sizeRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return sizeRec(node->left) + 1 + sizeRec(node->right);
    }
};

void printNode(Node* node) {
    if (node) {
        std::cout << node->data << " ";
    }
}

#endif // BINTREE_BINTREE_H_