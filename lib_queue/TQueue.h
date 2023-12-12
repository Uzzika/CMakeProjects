// Copyright (c) 2023 Dudchenko Olesya Victorovna

#ifndef TQUEUE_TQUEUE_H_
#define TQUEUE_TQUEUE_H_

#include <iostream>
#include "../lib_list/list.h"

template <class T>
class TQueue {
    size_t size;
    size_t actsize;
    TNode<T>* beg;
    TNode<T>* end;

public:
    explicit TQueue(size_t size_) :
        size(size_), actsize(0), beg(nullptr), end(nullptr) { }
    bool isEmpty() {
        return beg == nullptr;
    }
    bool isFull() {
        return actsize == size;
    }
    void push(T val) {
        if (!isFull()) {
            TNode<T>* p = new TNode<T>(val);
            if (beg == nullptr) {
                beg = p;
                end = p;
            }
            else {
                end->next = p;
                end = p;
            }
            actsize++;
        }
    }
    T pop() {
        if (!isEmpty()) {
            T ret = beg->data;
            TNode<T>* p = beg;
            beg = beg->next;
            delete p;
            actsize--;
            return ret;
        }
    }
    void clear() {
        while (!isEmpty())
            pop();
    }
    size_t size() {
        return actsize;
    }
    void print() {
        TNode<T>* p = beg;
        while (p) {
            std::cout << p->data << " " << std::endl;
            p = p->next;
        }
    }
};

template <class T>
class PQueue {

};

#endif // TQUEUE_TQUEUE_H_