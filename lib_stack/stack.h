// Copyright 2023 Dudchenko Olesya

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include <iostream>

template <typename T>
class Stack {
    int size;
    T* data;
    int top;
public:
    Stack(int size_) {
        size = size_;
        top = -1;
        data = new T[size];
    }
    Stack(const Stack& st) {
        size = st.size;
        top = st.top;
        data = new T [size];
        for (int i = 0; i < size; i += 1) {
            data[i] = st.data[i];
        }
    }
    ~Stack() {
        delete []data;
        data = nullptr;
    }
    bool isEmpty();
    bool isFull();
    T& getTop();
    void pop();
    void push(T elem);

    void print();
};
template <typename T>
bool Stack<T>::isEmpty() {
    return top == -1;
}
template <typename T>
bool Stack<T>::isFull() {
    return size == top + 1;
}
template <typename T>
T& Stack<T>::getTop() {
    return data[top];
}
template <typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::logic_error("Stack is empty!");
    }
    top--;
}
template <typename T>
void Stack<T>::push(T elem) {
    if (isFull()) {
        throw std::logic_error("Stack is full!");
    }
    top++;
    data[top] = elem;
}
template <typename T>
void Stack<T>::print() {
    Stack copy(*this);
    while (!copy.isEmpty()) {
        std::cout << copy.getTop() <<'\n';
        copy.pop();
    }
}

template<typename T>
class TDynamicStack
{
    int top;
    size_t memSize;
    T* pMem;

public:
    TDynamicStack() : top(-1), memSize(1),
        pMem(new T[memSize]) { }
    ~TDynamicStack() { delete[] pMem; }
    size_t size() const { return top + 1; }
    bool IsEmpty() const { return top == -1; }
    T Pop() { return pMem[top--]; }
    void Push(const T& val) {
        if (top == memSize - 1) {
            T* tmpMem = new T[memSize * 2];
            std::copy(pMem, pMem + memSize, tmpMem);
            delete[] pMem;
            pMem = tmpMem;
            memSize *= 2;
        }
        pMem[++top] = val;
    }
};

template<typename T>
class TVectorStack {
    int top;
    std::vector<T> mem;
public:
    TVectorStack() : top(-1) { }
    size_t size() const { return top + 1; }
    bool IsEmpty() const { return top == -1; }
    void Push(const T& val) {
        mem.push_back(val); top++;
    }
    T Pop() {
        T val = mem.pop_back(); top--; return val;
    }
};

#endif  // LIB_STACK_STACK_H_