// Copyright 2024 Dudchenko Olesya

#include <iostream>

//  аждый узел либо красный, либо черный.
//  орень дерева всегда черный.
// ¬се листь€(nullptr) считаютс€ черными.
// Ќе может быть двух красных подр€д.
// ƒл€ любого узла, все пути от этого узла до листьев
// содержат одинаковое количество черных узлов.

enum Color { Red, Black, BlackBlack };

template <typename TValue>
struct TNode {
    TValue data;
    TNode* left, * right, * parent;
    Color color;

    TNode(TValue value) : data(value), left(nullptr), right(nullptr), parent(nullptr), color(Red) {}
};

template <typename TValue>
class RBTree {
    TNode<TValue>* root;
public:
    RBTree() : root(nullptr) {}

    bool empty() { return root == nullptr; }

    TNode<TValue>* find(TValue value);
    void insert(TValue value);
    void remove(TValue value);

private:
    TNode<TValue>* BST_insert(TNode<TValue>* node);
    TNode<TValue>* BST_remove(TNode<TValue>* node);

    void right_rotate(TNode<TValue>* X);
    void left_rotate(TNode<TValue>* X);

    void swap_colors(TNode<TValue>* X1, TNode<TValue>* X2);

    void LL(TNode<TValue>* X);
    void RR(TNode<TValue>* X);
    void RL(TNode<TValue>* X);
    void LR(TNode<TValue>* X);

    void fix_insertion(TNode<TValue>* X);
    void fix_deletion(TNode<TValue>* X);
    TNode<TValue>* min_value_node(TNode<TValue>* node);
    TNode<TValue>* replace_node(TNode<TValue>* node);
};

template <typename TValue>
TNode<TValue>* RBTree<TValue>::find(TValue value) {
    TNode<TValue>* current = root;
    while (current != nullptr) {
        if (value == current->data) {
            return current;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

template <typename TValue>
void RBTree<TValue>::right_rotate(TNode<TValue>* X) {
    TNode<TValue>* G = X->parent;
    TNode<TValue>* C = X->left;
    TNode<TValue>* T4 = C->right;

    if (G) {
        if (G->left == X) {
            G->left = C;
        }
        else {
            G->right = C;
        }
    }
    else {
        root = C;
    }
    C->parent = G;
    C->right = X;
    X->parent = C;
    X->left = T4;
    if (T4) {
        T4->parent = X;
    }
}

template <typename TValue>
void RBTree<TValue>::left_rotate(TNode<TValue>* X) {
    TNode<TValue>* G = X->parent;
    TNode<TValue>* C = X->right;
    TNode<TValue>* T2 = C->left;

    if (G) {
        if (G->left == X) {
            G->left = C;
        }
        else {
            G->right = C;
        }
    }
    else {
        root = C;
    }
    C->parent = G;
    C->left = X;
    X->parent = C;
    X->right = T2;
    if (T2) {
        T2->parent = X;
    }
}

template <typename TValue>
void RBTree<TValue>::swap_colors(TNode<TValue>* X1, TNode<TValue>* X2) {
    Color tmp = X1->color;
    X1->color = X2->color;
    X2->color = tmp;
}

template <typename TValue>
void RBTree<TValue>::LL(TNode<TValue>* X) {
    right_rotate(X->parent->parent);
}

template <typename TValue>
void RBTree<TValue>::RR(TNode<TValue>* X) {
    left_rotate(X->parent->parent);
}

template <typename TValue>
void RBTree<TValue>::LR(TNode<TValue>* X) {
    left_rotate(X->parent);
    right_rotate(X->parent);
}

template <typename TValue>
void RBTree<TValue>::RL(TNode<TValue>* X) {
    right_rotate(X->parent);
    left_rotate(X->parent);
}

template <typename TValue>
TNode<TValue>* RBTree<TValue>::BST_insert(TNode<TValue>* node) {
    TNode<TValue>* parent = nullptr;
    TNode<TValue>* current = root;

    while (current != nullptr) {
        parent = current;
        if (node->data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    node->parent = parent;

    if (parent == nullptr) {
        root = node;
    }
    else if (node->data < parent->data) {
        parent->left = node;
    }
    else {
        parent->right = node;
    }

    return node;
}

template <typename TValue>
void RBTree<TValue>::insert(TValue value) {
    TNode<TValue>* node = new TNode<TValue>(value);
    TNode<TValue>* X = BST_insert(node);
    fix_insertion(X);
}

template <typename TValue>
void RBTree<TValue>::fix_insertion(TNode<TValue>* X) {
    while (X != root && X->parent->color == Red) {
        TNode<TValue>* P = X->parent;
        TNode<TValue>* G = P->parent;

        if (P == G->left) {
            TNode<TValue>* U = G->right;
            if (U && U->color == Red) {
                U->color = Black;
                P->color = Black;
                G->color = Red;
                X = G;
            }
            else {
                if (X == P->right) {
                    left_rotate(P);
                    X = P;
                    P = X->parent;
                }
                right_rotate(G);
                swap_colors(P, G);
                X = P;
            }
        }
        else {
            TNode<TValue>* U = G->left;
            if (U && U->color == Red) {
                U->color = Black;
                P->color = Black;
                G->color = Red;
                X = G;
            }
            else {
                if (X == P->left) {
                    right_rotate(P);
                    X = P;
                    P = X->parent;
                }
                left_rotate(G);
                swap_colors(P, G);
                X = P;
            }
        }
    }
    root->color = Black;
}

template <typename TValue>
void RBTree<TValue>::remove(TValue value) {
    TNode<TValue>* node = find(value);
    if (!node) return;
    BST_remove(node);
}

template <typename TValue>
TNode<TValue>* RBTree<TValue>::min_value_node(TNode<TValue>* node) {
    TNode<TValue>* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template <typename TValue>
TNode<TValue>* RBTree<TValue>::replace_node(TNode<TValue>* node) {
    if (node->left && node->right) return min_value_node(node->right);
    if (!node->left && !node->right) return nullptr;
    if (node->left) return node->left;
    else return node->right;
}

template <typename TValue>
TNode<TValue>* RBTree<TValue>::BST_remove(TNode<TValue>* node) {
    TNode<TValue>* replacement = replace_node(node);
    TNode<TValue>* parent = node->parent;
    bool both_black = ((replacement == nullptr || replacement->color == Black) && node->color == Black);

    if (replacement == nullptr) {
        if (node == root) {
            root = nullptr;
        }
        else {
            if (both_black) {
                fix_deletion(node);
            }
            else {
                if (sibling(node)) {
                    sibling(node)->color = Red;
                }
            }
            if (parent->left == node) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        delete node;
        return nullptr;
    }

    if (node->left == nullptr || node->right == nullptr) {
        if (node == root) {
            node->data = replacement->data;
            node->left = node->right = nullptr;
            delete replacement;
        }
        else {
            if (parent->left == node) {
                parent->left = replacement;
            }
            else {
                parent->right = replacement;
            }
            delete node;
            replacement->parent = parent;
            if (both_black) {
                fix_deletion(replacement);
            }
            else {
                replacement->color = Black;
            }
        }
        return replacement;
    }

    std::swap(node->data, replacement->data);
    return BST_remove(replacement);
}

template <typename TValue>
void RBTree<TValue>::fix_deletion(TNode<TValue>* X) {
    if (X == root) return;

    TNode<TValue>* S = sibling(X);
    TNode<TValue>* P = X->parent;

    if (S == nullptr) {
        fix_deletion(P);
    }
    else {
        if (S->color == Red) {
            P->color = Red;
            S->color = Black;
            if (S == P->left) {
                right_rotate(P);
            }
            else {
                left_rotate(P);
            }
            fix_deletion(X);
        }
        else {
            if ((S->left != nullptr && S->left->color == Red) || (S->right != nullptr && S->right->color == Red)) {
                if (S->left != nullptr && S->left->color == Red) {
                    if (S == P->left) {
                        S->left->color = S->color;
                        S->color = P->color;
                        right_rotate(P);
                    }
                    else {
                        S->left->color = P->color;
                        right_rotate(S);
                        left_rotate(P);
                    }
                }
                else {
                    if (S == P->left) {
                        S->right->color = P->color;
                        left_rotate(S);
                        right_rotate(P);
                    }
                    else {
                        S->right->color = S->color;
                        S->color = P->color;
                        left_rotate(P);
                    }
                }
                P->color = Black;
            }
            else {
                S->color = Red;
                if (P->color == Black) {
                    fix_deletion(P);
                }
                else {
                    P->color = Black;
                }
            }
        }
    }
}

template <typename TValue>
TNode<TValue>* sibling(TNode<TValue>* node) {
    if (node->parent == nullptr) return nullptr;
    if (node == node->parent->left) return node->parent->right;
    return node->parent->left;
}
