// Copyright 2023 Dudchenko Olesya

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
