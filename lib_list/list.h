// Copyright 2023 Dudchenko Olesya

#include <iostream>

template <class T>
class TNode {
    T data;
    TNode* next;
public:
    TNode(const TNode& node) : data(node.data), next(node.next) {}
    TNode(T _data, TNode* _next = nullptr) {
        data = _data;
        next = _next;
    }
    ~TNode() {
        delete next;
    }
    std::string toString() const noexcept;

    bool operator==(const TNode& n)
    {
        if (data == n.data) { return 1; }
        else { return 0; }
    }

    /*bool operator=() {

    }*/
    friend std::ostream& operator<<(std::ostream& ostr, const TNode& node);
};

template <class T>
class TList {
    friend class TNode;
    TNode* head;
    TNode* tail;
    int count;
public:
    TList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }
    TList(T* massData, int size) {
        for (int i = size - 1; i >= 0; i--) {
            push_front(massData[i]);
        }
    }
    ~TList() {
        delete head;
        delete tail;
    }
    void clear();
    bool isEmpty();
    void push_back(T data);
    void push_front(T data);
    void insert(TNode* p, T data);
    void replace(TNode* p, T data);
    void delete_elem(TNode* p);
};

template <class T>
void TList<T>::insert(TNode<T>* p, T data) {
    TNode* node = new;
    TNode(data, p -> new);
    p->next = node;
    count++;
    if (node->next == nullptr) {
        tail = data;
    }
}

template<class T>
void TList<T>::push_front(T data) {
    TNode* node = new TNode(data, head);
    head = node;
    count++;
    if (count == 1) { tail = node; }
}

template<class T>
void TList<T>::push_back(T data) {
    insert(tail, data);
}

template <class T>
void TList<T>::delete_elem(TNode<T>* p) {
    if (p == head) {
        if (head == nullptr) {
            tail = nllptr;
        }
        head = p->next;
        delete p;
        return 0;
    }
    TNode* cur = head;
    while (cur->next != p && cur->next != nullptr) {
        cur = cur->next;
        cur->next = cur->next->next;
        delete p;
    }
    if (cur->next == nullptr) {
        tail = cur;
    }
}

template<class T>
bool TList<T>::isEmpty() {
    if (count == 0) { return 1; }
    else { return 0; }
}

template<class T>
void TList<T>::clear() {
    while (count != 0) {
        delete_elem(head);
    }
}

template<class T>
void TList<T>::replace(TNode<T>* p, T data) {
    p = p->data;
}

template <class T>
std::string TNode<T>::toString() const noexcept {
    std::string str = "";
    for (int i = 0; i < size; i++) {
        str += std::to_string(data[i]) + "->";
    }
    return str;
}